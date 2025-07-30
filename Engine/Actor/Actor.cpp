#include "Actor.h"
#include "Utils/Utils.h"
#include "Engine.h"
#include "Level/level.h"

#include <iostream>
#include <Windows.h>



Actor::Actor(const char* _image, Color _color, const Vector2& _position)
	: color(_color), position(_position)
{
	// ���ڿ� ����
	width = (int)strlen(_image);

	// �޸� �Ҵ�
	image = new char[width + 1];

	// ���ڿ� ����
	strcpy_s(image, width + 1, _image);
}

Actor::~Actor()
{ 
	// �޸� ����
	SafeDeleteArray(image);
}

// �̺�Ʈ �Լ�
// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��(�ʱ�ȭ ����)
void Actor::BeginPlay()
{ 
	hasBeganPlay = true;
}

// �����Ӹ��� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�)
void Actor::Tick(float _deltaTime)
{ }

// �׸��� �Լ�
void Actor::Render()
{	
	// Ŀ�� �̵�
	Utils::SetConsolePosition(position);
	
	// ���� ����
	Utils::SetConsoleTextColor(color);

	// �׸���
	std::cout << image;
}

void Actor::SetPosition(const Vector2 & _newPosition)
{
	// ����ó�� (ȭ�� ������� Ȯ��)
	if (_newPosition.x < 0) return;										// ȭ�� ����
	if (_newPosition.x + width - 1 > Engine::Get().GetWidth()) return;	// ȭ�� ������
	if (_newPosition.y < 0) return;										// ȭ�� ����
	if (_newPosition.y - 1 > Engine::Get().GetHeight()) return;			// ȭ�� �Ʒ���

	if (position == _newPosition) return;								// ������ ������Ʈ ����

	// ���� ��ġ Ȯ��
	Vector2 direction = _newPosition - position;
	position.x = direction.x >= 0 ? position.x : position.x + width - 1;
		
	// Ŀ�� �̵�
	Utils::SetConsolePosition(position);

	// ���ڿ� ���� ����ؼ� ���� ��ġ Ȯ���ؾ� ��
	std::cout << ' ';

	position = _newPosition;
}

Vector2 Actor::GetPosition() const
{
	return position;
}

void Actor::SetSortingOrder(unsigned int _sortingOrder)
{
	sortingOrder = _sortingOrder;
}

void Actor::SetOwner(Level* _newOwner)
{
	owner = _newOwner;
}

Level* Actor::GetOwner()
{
	return owner;
}

void Actor::Destroy()
{
	// ���� ��û�Ǿ��ٰ� ����
	isExpired = true;

	// ������ ���� ��û
	owner->DestroyActor(this);
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}
