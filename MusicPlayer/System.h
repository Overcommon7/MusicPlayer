#pragma once

class System
{
private:
	static void Initialize();
	static int ShutDown();
	static void Application();
	static void SystemLogic();
	static void SystemDraw();
	static void Resize();

	inline static GameScreen currentScreen = GameScreen::Gameplay;
	inline static Color BGColor = RAYWHITE;
	inline static int targetFPS = 0;

	System() = delete;
	System operator= (const System& s) = delete;
	System(const System& s) = delete;

public:

	static int Run();
};

