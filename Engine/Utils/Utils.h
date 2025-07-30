#pragma once

#include <Windows.h>
#include "Math/Vector2.h"
#include "Math/Color.h"

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

	inline void SetConsolePosition(const Vector2& _position)
	{
		SetConsolePosition(static_cast<COORD>(_position));
	}

	// �ܼ� �ؽ�Ʈ ���� ���� �Լ�
	inline void SetConsoleTextColor(WORD _color)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleTextAttribute(handle, _color);
	}

	inline void SetConsoleTextColor(Color _color)
	{
		SetConsoleTextColor(static_cast<WORD>(_color));
	}



}

