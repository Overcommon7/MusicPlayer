#include "pch.h"
#include "SymbolDefines.h"

extern unordered_map<string, Texture2D> textures = {};
extern unordered_map<string, Font> fonts = {};
extern float DeltaTime{};
extern float SCREEN_WIDTH = 550, SCREEN_HEIGHT = 350;
extern const float MAX_WIDTH = SCREEN_WIDTH, MAX_HEIGHT = SCREEN_HEIGHT;
extern Rectangle UIBOX = { 0, 0, SCREEN_WIDTH, 75 };
extern const Rectangle SLIDER_BAR = { 50, 55, SCREEN_WIDTH - 100, 5.f };
extern float WINDOW_SCALE = 1;
#ifndef NDEBUG
extern const bool ReleaseMode = false;
#else
extern const bool ReleaseMode = true;
#endif 



