#include "GameLevel.h"
#include "Actor/Player.h"

GameLevel::GameLevel()
{
	// �÷��̾� �߰�
	AddActor(new Player());
}

GameLevel::~GameLevel()
{
}

void GameLevel::BeginPlay()
{
	super::BeginPlay();
}

void GameLevel::Tick(float _deltaTime)
{
	super::Tick(_deltaTime);
}

void GameLevel::Render()
{
	super::Render();
}
