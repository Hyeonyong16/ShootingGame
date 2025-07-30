#pragma once

#include "Core.h"

class Engine_API Input
{
	// friend ����
	friend class Engine;

	// Ű�Է� Ȯ���� ���� ����ü
	struct KeyState
	{
		bool isKeyDown = false;			// ���� �����ӿ� Ű�� ���ȴ��� ����
		bool previousKeyDown = false;	// ���� �����ӿ� Ű�� ���ȴ��� ����
	};

public:
	Input();

	// Ű Ȯ�� �Լ�
	bool GetKey(int _keyCode);
	bool GetKeyDown(int _keyCode);
	bool GetKeyUp(int _keyCode);

	static Input& Get();

private:
	void ProcessInput();
	void SavePreviousKeyStates();

private:
	// Ű �Է� ���� ���� ����
	KeyState keyStates[255] = { };

	static Input* instance;
};

