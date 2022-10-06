#pragma once
#include "pch.h"

class Clicker
{
private:
	static inline Rectangle collider = {};
	static inline bool leftClicked = false, leftDown = false, leftUp = false;
	static inline float mouseWheel = 0.f;
	static inline float scrollMultiplier = 7.f;
	Clicker& operator=(const Clicker& c) = delete;
	Clicker(const Rectangle& r) = delete;
	Clicker() = delete;

	static void UpdatePostition(float x, float y);
	static const bool LeftClicked()  { return IsMouseButtonPressed(MOUSE_BUTTON_LEFT); }
	static const bool LeftDowned()   { return IsMouseButtonDown(MOUSE_BUTTON_LEFT); }
	static const bool RightClicked() { IsMouseButtonPressed(MOUSE_BUTTON_RIGHT); }
	static const bool RightDown()    { return IsMouseButtonDown(MOUSE_BUTTON_RIGHT); }

public:
	static void Update();
	static void Initialize();
	
	static const Rectangle GetPointer() { return collider; }
	static const Vector2 GetPosition() { return Vector2(collider.x, collider.y); }	
	static const bool& LeftClick() { return leftClicked; }
	static const bool& LeftDown() { return leftDown; }
	static const bool& LeftUp() { return leftUp; }
	static const float GetMouseWheel() { return mouseWheel; }
};							 

