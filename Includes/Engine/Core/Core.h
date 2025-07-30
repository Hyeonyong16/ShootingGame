#pragma once

// dll �ܺη� ���ø� ������ �� �߻��ϴ� ��� ����
#pragma warning(disable: 4251)	
// ���� ������ �ּҸ� ��ȯ�� �� �߻��ϴ� ��� ��Ȱ��ȭ
#pragma warning(disable: 4172)	


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define new new
#endif

#if BuildEngineDLL
#define Engine_API __declspec(dllexport)
#else
#define Engine_API __declspec(dllimport)
#endif

// �޸� ���� �Լ�
template<typename T>
void SafeDelete(T*& _target)
{
	if (nullptr != _target)
	{
		delete _target;
		_target = nullptr;
	}
}

template<typename T>
void SafeDeleteArray(T*& _target)
{
	if (nullptr != _target)
	{
		delete[] _target;
		_target = nullptr;
	}
}