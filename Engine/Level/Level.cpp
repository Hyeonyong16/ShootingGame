#include "Level.h"
#include "Actor/Actor.h"

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
	actors.emplace_back(_newActor);	// emplace_back �� �̵�, push_back �� ���� - �̵��� ������ ����

	// ���ʽ� ����
	_newActor->SetOwner(this);
}

// ���� �̺�Ʈ �Լ�
void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
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
