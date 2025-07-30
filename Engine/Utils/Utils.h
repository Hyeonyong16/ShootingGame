#pragma once

#include <Windows.h>

// ������Ʈ���� �پ��ϰ� ����� ��ƿ��Ƽ �Լ� ����
namespace Utils
{
	// �� ���� ���� �ٲ� �� ����ϴ� �Լ�
	template<typename T>
	void Swap(T& _a, T& _b)
	{
		T temp = _a;
		_a = _b;
		_b = temp;
	}

	// �ܼ� ��� �ڵ� �������� �Լ�
	inline HANDLE GetConsoleHandle()
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}

	// �ܼ� Ŀ�� ��ġ �̵� �Լ�
	inline void SetConsolePosition(COORD _coord)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleCursorPosition(handle, _coord);
	}

	// �ܼ� �ؽ�Ʈ ���� ���� �Լ�
	inline void SetConsoleTextColor(WORD _color)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleTextAttribute(handle, _color);
	}



}

