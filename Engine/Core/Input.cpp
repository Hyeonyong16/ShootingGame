#include "Input.h"

#include <Windows.h>

// static ���� ����
Input* Input::instance = nullptr;

Input::Input()
{
	// �̱��� ������ ���� instance ���� ����
	instance = this;
}

void Input::ProcessInput()
{
	// Ű �Է� Ȯ��
	for (int i = 0; i < 255; ++i)
	{
		keyStates[i].isKeyDown = GetAsyncKeyState(i) & 0x8000;
	}
}

void Input::SavePreviousKeyStates()
{
	// ���� �������� �Է��� ���
	for (int i = 0; i < 255; ++i)
	{
		keyStates[i].previousKeyDown = keyStates[i].isKeyDown;
	}
}

bool Input::GetKey(int _keyCode)
{
	return keyStates[_keyCode].isKeyDown;
}

bool Input::GetKeyDown(int _keyCode)
{
	return keyStates[_keyCode].isKeyDown && !keyStates[_keyCode].previousKeyDown;
}

bool Input::GetKeyUp(int _keyCode)
{
	return !keyStates[_keyCode].isKeyDown && keyStates[_keyCode].previousKeyDown;
}

Input& Input::Get()
{
	return *instance;
}