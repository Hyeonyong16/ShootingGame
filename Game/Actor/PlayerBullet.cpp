#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const Vector2& _position)
	: Actor("#", Color::Green, _position), yPosition((float)_position.y)
{

}

void PlayerBullet::Tick(float _deltaTime)
{
	super::Tick(_deltaTime);

	// 이동 처리
	yPosition -= moveSpeed * _deltaTime;

	Vector2 position = GetPosition();
	position.y = (int)yPosition;

	// 계산 값이 화면 위를 벗어나면 탄약 제거
	if (yPosition < 0.0f)
	{
		Destroy();
		return;
	}

	SetPosition(position);
}
