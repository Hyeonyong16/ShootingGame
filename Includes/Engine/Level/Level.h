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

	// ���� �̺�Ʈ �Լ�
	virtual void BeginPlay();
	virtual void Tick(float _deltaTime);
	virtual void Render();

private:
	// SortingOrder �� Actors ����
	void SortActorsBySortingOrder();

protected:
	std::vector<Actor*> actors; //������ ��ġ�� ��� ���͸� �����ϴ� �迭

};

