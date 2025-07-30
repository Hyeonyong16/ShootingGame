#pragma once

#include "Core.h"
#include <Windows.h>

class Engine_API Vector2
{
public:
	Vector2(int _x = 0, int _y = 0);
	~Vector2();	// �⺻ �Ҹ��� ����

	Vector2 operator+(const Vector2& _other) const;
	Vector2 operator-(const Vector2& _other) const;

	bool operator==(const Vector2& _other) const;

	// ����ȯ ������ �����ε�
	operator COORD();
	operator COORD() const;

	// ���ڿ��� ���
	const char* ToString();

	static Vector2 Zero;
	static Vector2 One;
	static Vector2 Up;
	static Vector2 Right;


public:
	int x = 0;
	int y = 0;

private:
	char* value = nullptr;
};