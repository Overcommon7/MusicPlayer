#include "pch.h"
#include "User.h"
#include "Clicker.h"
#include "Defines.h"

void User::Update()
{
	withinUIBounds = CheckCollisionRecs(Clicker::GetPointer(), UIBOX);
	if (next) next = false;
	if (prev) prev = false;
	keyPressed = (KeyboardKey)GetKeyPressed();
}
