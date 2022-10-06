#include "pch.h"
#include "System.h"

//------------------------------------------------------------------------------------------
// Main entry point
//------------------------------------------------------------------------------------------
#ifndef NDEBUG
int main(void)
#else
int wWinMain(void)
#endif
{
    return System::Run();
}
