#pragma once

#include "Actor/Actor.h"

/*
	�÷��̾ �߻��ϴ� ź��
	- ȭ�� ���� �̵�
		- �ӷ�(������, �� ����), �� ����
*/

class PlayerBullet : public Actor
{
	RTTI_DECLARATIONS(PlayerBullet, Actor)

public:
	PlayerBullet(const Vector2& _position);

	virtual void Tick(float _deltaTime) override;


private:
	// �ʴ� �̵� �Ÿ� (ĭ)
	float moveSpeed = 20.0f;

	// ��ǥ�� �����̱� ������ ���� �� ����� ���� float ���� ����
	float yPosition = 0.0f;
};