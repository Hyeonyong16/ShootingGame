#pragma once

#include "Core.h"
#include "Input.h"
#include <Windows.h>

// ���� ���� ����ü
struct EngineSettings
{
	int	width = 0;				// �ܼ� ȭ�� ���� ũ��
	int	height = 0;				// �ܼ� ȭ�� ���� ũ��
	float framerate	= 0.0f;		// Ÿ�� ������ �ӵ�
};

class Level;
class Engine_API Engine
{
public:
	Engine();

	virtual ~Engine();

	// ���� ���� �Լ�
	void Run();

	// ���� �߰� �Լ�
	void AddLevel(Level* _newLevel);

	// �޸� ���� �Լ�
	virtual void CleanUp();

	// ���� �Լ�
	void Quit();

	// �̱��� ���� �Լ�
	static Engine& Get();

	// ȭ�� ����/���� ũ�� ��ȯ �Լ�
	int GetWidth() const;
	int GetHeight() const;

private:	
	void BeginPlay();
	void Tick(float _deltaTime = 0.0f);
	void Render();

	// ���� ���� �ε� �Լ�
	void LoadEngineSettings();

protected:
	// ���� ���� �÷���
	bool isQuit = false;

	// ���� ����
	Level* mainLevel = nullptr;

	// �Է� ������
	Input input;

	// ���� ����
	EngineSettings settings;

	// �̱��� ����
	static Engine* instance;
};