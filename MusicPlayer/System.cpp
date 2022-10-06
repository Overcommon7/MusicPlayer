#include "pch.h"
#include "System.h"
#include "Game.h"
#include "Defines.h"
#include "User.h"

extern unordered_map<string, Font> fonts;

void System::Initialize()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Music Player");
	InitAudioDevice();
	SetExitKey(KEY_NULL);
	targetFPS = GetMonitorRefreshRate(GetCurrentMonitor());
	SetTargetFPS(targetFPS);
	Clicker::Initialize();
	Game::Initialize();
}

int System::ShutDown()
{
	SystemLogic();
	Game::DeInitialize();
	CloseAudioDevice();
	CloseWindow();
	return 0;
}

void System::Application()
{
	while (!WindowShouldClose())
	{
		SystemLogic();

		switch (currentScreen)
		{
		case GameScreen::TilteScreen:
			Game::TitleScreenLogic(currentScreen);
			break;
		case GameScreen::Gameplay:
			Game::GameplayLogic(currentScreen);
			break;		
		case GameScreen::Loading:
			Game::LoadingLogic(currentScreen);
			break;
		}

		BeginDrawing();
		ClearBackground(BGColor);

		switch (currentScreen)
		{
		case GameScreen::TilteScreen:
			Game::TitleScreenDraw();
			break;
		case GameScreen::Gameplay:
			Game::GameplayDraw();
			break;		
		case GameScreen::Loading:
			Game::LoadingDraw();
			break;
		}

		SystemDraw();
		EndDrawing();
	}
}

void System::SystemLogic()
{
	DT = GetFrameTime();
	Clicker::Update();
	User::Update();
		
}

void System::SystemDraw()
{
#ifndef NDEBUG
	int fps = GetFPS();
	Color color = GREEN;
	if (fps < targetFPS * 0.5) color = YELLOW;
	if (fps < targetFPS * 0.25) color = RED;
	DrawTextEx(fonts.at(K_FONT_DEFAULT), ("FPS " + to_string(fps)).c_str(), {5.f, 5.f}, 15.f, 1.f, color);
#endif
}

void System::Resize()
{
	SCREEN_WIDTH = GetScreenWidth();
	SCREEN_HEIGHT = GetScreenHeight();
	WINDOW_SCALE = SCREEN_WIDTH / MAX_WIDTH;
}

int System::Run()
{
	Initialize();
	Application();
	return ShutDown();
}
