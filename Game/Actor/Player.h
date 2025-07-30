#pragma once
#include "Actor/Actor.h"


/*
*	���
*	- �¿� �̵� (Ű�Է� ���)
*	- ź�� �߻� (���� ����) (Ű�Է� ���)
*		- �ܹ� Fire()
*		- ���� FireInterval(float _deltaTime)
*/

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)
	
public:
	Player();

	virtual void Tick(float _deltaTime) override;

private:
	void Fire();							// �ܹ�
	void FireInterval(float _deltaTime);	// ����

private:
	// ���� ���� (����: ��)
	float fireInterval = 0.15f;


};