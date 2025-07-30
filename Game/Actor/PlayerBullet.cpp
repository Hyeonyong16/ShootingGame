#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const Vector2& _position)
	: Actor("#", Color::Green, _position), yPosition((float)_position.y)
{

}

void PlayerBullet::Tick(float _deltaTime)
{
	super::Tick(_deltaTime);

	// �̵� ó��
	yPosition -= moveSpeed * _deltaTime;

	Vector2 position = GetPosition();
	position.y = (int)yPosition;

	// ��� ���� ȭ�� ���� ����� ź�� ����
	if (yPosition < 0.0f)
	{
		Destroy();
		return;
	}

	SetPosition(position);
}
