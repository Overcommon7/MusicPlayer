#include "pch.h"
#include "Clicker.h"
#include "Defines.h"

void Clicker::UpdatePostition(float x, float y)
{
	collider.x = x;
	collider.y = y;
}

void Clicker::Update()
{
	UpdatePostition((float)GetMouseX(), (float)GetMouseY());
	leftClicked = LeftClicked();
	leftDown = LeftDowned();
	mouseWheel = GetMouseWheelMoveV().y * scrollMultiplier;
	leftUp = IsMouseButtonUp(MOUSE_BUTTON_LEFT);
	if (IsKeyDown(KEY_LEFT_CONTROL))
	{
		if (mouseWheel > 1.f)
			scrollMultiplier -= 20 * DT;
		else if (mouseWheel < -1.f)
			scrollMultiplier += 20 * DT;
	}
	if (scrollMultiplier < 7.f)
		scrollMultiplier = 7.f;
		
}

void Clicker::Initialize()
{
	collider = { (float)GetMouseX(), (float)GetMouseY(), 3.f, 3.f };
}

