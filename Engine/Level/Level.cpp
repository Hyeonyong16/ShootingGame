#include "Level.h"
#include "Actor/Actor.h"
#include "Utils/Utils.h"

#include <iostream>

Level::Level()
{ }


Level::~Level()
{ 
	for (Actor* actor : actors)
	{
		SafeDelete(actor);
	}

	actors.clear();
}

// ������ ���͸� �߰��� �� ���
void Level::AddActor(Actor* _newActor)
{
	// ����ó��(�ߺ� ���� Ȯ��) �ʿ�
	
	// ��� �迭�� �߰�
	addRequestedActors.emplace_back(_newActor);

	// ���ʽ� ����
	//_newActor->SetOwner(this);
}

void Level::DestroyActor(Actor* _destroyedActor)
{
	// ��� �迭�� �߰�
	destroyRequestedActors.emplace_back(_destroyedActor);
}

// ���� �̺�Ʈ �Լ�
void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
		// ���� ó�� ���� Ȯ��
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		// �̹� ȣ��� ��ü�� �ǳʶٱ�
		if (actor->HasBeganPlay())
		{
			continue;
		}

		actor->BeginPlay();
	}
}

void Level::Tick(float _deltaTime)
{
	for (Actor* const actor : actors)
	{
		// ���� ó�� ���� Ȯ��
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Tick(_deltaTime);
	}
}

void Level::Render()
{ 
	// ������ ���� ���� ���� �������� ���ġ
	SortActorsBySortingOrder();

	// Render Pass
	for (Actor* const actor : actors)
	{
		// �˻� ( ���� ��ġ�� ���� ������ ���� ���Ͱ� �ִ��� Ȯ��)
		Actor* searchedActor = nullptr;
		for (Actor* const otherActor : actors)
		{
			// ���� ó�� ���� Ȯ��
			if (!actor->isActive || actor->isExpired)
			{
				continue;
			}

			// ���� ���͸� ����
			if (actor == otherActor) continue;

			// ��ġ�� ���� ���� Ȯ��
			if (actor->GetPosition() == otherActor->GetPosition())
			{
				// ���� ���� �� �� ���� ����
				if (actor->sortingOrder < otherActor->sortingOrder)
				{
					// ���� �� ���� ����
					searchedActor = otherActor;
					break;
				}
			}
		}
		
		// � ���Ϳ� ���� ��ġ�� ���� ������ �� ���� ���Ͱ� ������ �׸��� �ʰ� �ǳʶٱ�
		if (nullptr != searchedActor)
		{
			continue;
		}

		// ��ο� ��
		actor->Render();
	}
}

void Level::ProcessAddAndDestroyActors()
{
	// actors �迭���� ���� ó��
	for (auto iterator = actors.begin(); iterator != actors.end();)
	{
		// ���� ��û�� �������� Ȯ�� �� �迭���� ����
		if ((*iterator)->isExpired)
		{
			// erase �Լ��� ����ϸ� iterator �� ��ȿȭ�Ǳ� ������
			// ��ȯ�Ǵ� ���� �����ؾ���
			iterator = actors.erase(iterator);
			continue;
		}

		++iterator;
	}

	// destroyedRequestedActors �迭�� ��ȸ�ϸ鼭 Actor�� delete
	for (auto* actor : destroyRequestedActors)
	{
		// ���Ͱ� �׷ȴ� �� �����
		Utils::SetConsolePosition(actor->position);

		// �ֿܼ� ���� ����ؼ� �����
		for (int i = 0; i < actor->width; ++i)
		{
			std::cout << " ";
		}

		// ���ҽ� ����
		SafeDelete(actor);
	}

	// �迭 �ʱ�ȭ
	destroyRequestedActors.clear();

	// addRequestedActors �迭�� ��ȸ�ϸ鼭 ���ο� Actor �߰�
	for (auto* const actor : addRequestedActors)
	{
		actors.emplace_back(actor);
		actor->SetOwner(this);
	}

	// �迭 �ʱ�ȭ
	addRequestedActors.clear();
}

// SortingOrder �� ���� Actor ����
void Level::SortActorsBySortingOrder()
{
	// ���� ����
	for (int i = 0; i < (int)actors.size(); ++i)
	{
		for (int j = 0; j < (int)actors.size() - 1; ++j)
		{
			// sortingOrder ���� Ŭ���� �� �ʿ� ��ġ
			if (actors[j]->sortingOrder > actors[j + 1]->sortingOrder)
			{
				// �� ���� ��ġ ��ȯ
				std::swap(actors[j], actors[j + 1]);
			}
		}
	}
	
}
