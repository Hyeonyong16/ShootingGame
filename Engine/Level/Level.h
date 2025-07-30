#pragma once

#include "Core.h"
#include <vector>
#include <RTTI.h>

class Actor;

class Engine_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	// ������ ���͸� �߰��� �� ���
	void AddActor(Actor* _newActor);

	// ���� ���� �Լ�
	void DestroyActor(Actor* _destroyedActor);

	// ���� �̺�Ʈ �Լ�
	virtual void BeginPlay();
	virtual void Tick(float _deltaTime);
	virtual void Render();

	// �߰� �� ���� ��û�� ���͸� ó���ϴ� �Լ�
	void ProcessAddAndDestroyActors();

private:
	// SortingOrder �� Actors ����
	void SortActorsBySortingOrder();

protected:
	// ������ ��ġ�� ��� ���͸� �����ϴ� �迭
	std::vector<Actor*> actors;

	// �߰� ��û�� ���͸� �����ϴ� �迭
	std::vector<Actor*> addRequestedActors;

	// ���� ��û�� ���͸� �����ϴ� �迭
	std::vector<Actor*> destroyRequestedActors;
};

