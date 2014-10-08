#include "SystemClass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	System = new SystemClass;

	if (!System)
		return 0;

	if (System->Initialize())
		System->Run();

	System->Shutdown();
	delete System;

	return 0;
}