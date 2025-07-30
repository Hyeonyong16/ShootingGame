#pragma once
#include "Level/Level.h"

/*
	���� ������ å��
	- �� ����: �ణ�� �������� �����ؼ� ���� �ð����� �� ����
	- �浹 ó��: �÷��̾� - �� ź�� ������ �浹/ �� - �÷��̾� ź���� �浹 ó�� (AABB)
	- ���� ����: �÷��̾ ���� ������ 1���� ȹ��
	- ���� ����: �÷��̾ ������ ���� ����
*/

class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();

	// ���� �̺�Ʈ �Լ�
	virtual void BeginPlay() override;
	virtual void Tick(float _deltaTime) override;
	virtual void Render() override;

private:

};