#include "Engine.h"
#include <iostream>
#include <Windows.h>

#include "Level/Level.h"
#include "Utils/Utils.h"

// ���� ���� �ʱ�ȭ
Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD _CtrlType)
{
	switch (_CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		// Engine�� �޸� ����
		Engine::Get().CleanUp();
		return false;
	}

	return false;
}

Engine::Engine()
{
	// �̱����� ������ ��ü�� �ϳ��� �����ǰ� �ߺ� Ȯ���ؾ���
	// ���⼭�� ������ �ϳ��� ������ �� �˰� ������ �ϴ� ��ŵ
	instance = this;

	// �ܼ� Ŀ�� ����
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);

	// �ܼ� â �̺�Ʈ ���
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);

	// ���� ���� �ε�
	LoadEngineSettings();
}

Engine::~Engine()
{
	CleanUp();
}

void Engine::Run()
{
	// �и� ������ ������ ���� �ð��� �˷���
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// �ϵ���� �ð��� ���е�(���ļ�) ��������
	// ���߿� �ʷ� ��ȯ�ϱ� ����
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// Ÿ�� ������
	float targetFrameRate = settings.framerate == 0.0f ? 60.0f : settings.framerate;

	// Ÿ�� �� ������ �ð�
	float oneFrameTime = 1.f / targetFrameRate;

	// GameLoop
	while (true)
	{
		// ���� ���� ���� Ȯ��
		if (isQuit)
		{ 
			// ���� ����
			break; 
		}

		// ������ �ð� ���
		// (���� �ð� - ���� �ð�) / ���ļ� = �ʴ���
		QueryPerformanceCounter(&currentTime);

		// ������ �ð�
		float deltaTime = (currentTime.QuadPart - previousTime.QuadPart) / (float)frequency.QuadPart;

		// �Է��� �ִ��� ������ ó��
		input.ProcessInput();

		// ���� ������
		if(deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// ���� FPS ���
			char title[50] = { };
			sprintf_s(title, 50, "FPS: %f", (1.0f / deltaTime));
			SetConsoleTitleA(title);

			// �ð� ������Ʈ
			previousTime = currentTime;

			// ���� �������� �Է��� ���
			input.SavePreviousKeyStates();

			// ���� �����ӿ� �߰� �� ���� ��û�� ���� ó��
			if (mainLevel)
			{
				mainLevel->ProcessAddAndDestroyActors();
			}
		}
	}

	// ���� - �ؽ�Ʈ ���� ������� ��������
	Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Engine::AddLevel(Level* _newLevel)
{
	// ������ �ִ� ������ ����
	if (nullptr != mainLevel)
	{
		delete mainLevel;
	}

	mainLevel = _newLevel;
}

void Engine::CleanUp()
{
	// ���� ����
	SafeDelete(mainLevel);
}

void Engine::Quit()
{
	// ���� �÷��� ����
	isQuit = true;
}

Engine& Engine::Get()
{
	return *instance;
}

int Engine::GetWidth() const
{
	return settings.width;
}

int Engine::GetHeight() const
{
	return settings.height;
}

void Engine::BeginPlay()
{
	if (nullptr != mainLevel)
	{
		mainLevel->BeginPlay();
	}
}

void Engine::Tick(float _deltaTime)
{
	/*std::cout << "DeltaTime: " << _deltaTime
		<< ", FPS: " << (1.f / _deltaTime)
		<< "\n";*/

	// ���� ������Ʈ
	if (nullptr != mainLevel)
	{
		mainLevel->Tick(_deltaTime);
	}
}

void Engine::Render()
{
	// ������ ���� �� �ؽ�Ʈ ������ �������
	Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	if (nullptr != mainLevel)
	{
		mainLevel->Render();
	}
}

void Engine::LoadEngineSettings()
{
	FILE* file = nullptr;
	fopen_s(&file, "../Settings/EngineSettings.txt", "rt");
	if (nullptr == file)
	{
		std::cout << "Failed to load engine settings.\n";
		__debugbreak();
		return;
	}

	// �ε�

	// FP(File Position) �����͸� ���� �ڷ� �ű��
	fseek(file, 0, SEEK_END);

	// �� ��ġ ���ϱ�
	size_t fileSize = ftell(file);

	// �ٽ� ù ��ġ�� �ǵ�����
	rewind(file);

	// ���� ������ ������ ���� �Ҵ�
	char* buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);

	// ���� �б�
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	// �Ľ�(Parcing, ���� �ؼ� -> �ʿ��� ������ ��� ����)
	char* context = nullptr;
	char* token = nullptr;

	token = strtok_s(buffer, "\n", &context);

	// ���� �м�
	while (nullptr != token)
	{
		// Ű/�� �и�
		char header[10] = { };

		// �Ʒ� ������ ����� �����Ϸ��� Ű�� �� ������ ��ĭ�� �־�� ��
		sscanf_s(token, "%s", header, 10);

		// ��� ���ڿ� ��
		if (strcmp(header, "framerate") == 0)
		{
			sscanf_s(token, "framerate = %f", &settings.framerate);
		}
		else if (strcmp(header, "width") == 0)
		{
			sscanf_s(token, "width = %d", &settings.width);
		}
		else if (strcmp(header, "height") == 0)
		{
			sscanf_s(token, "height = %d", &settings.height);
		}

		// �� �ٿ��� �и�
		token = strtok_s(nullptr, "\n", &context);
	}

	// ���� ����
	SafeDeleteArray(buffer);

	// ���� �ݱ�
	fclose(file);
}
