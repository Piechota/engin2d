#ifndef _SYSTEM_CLASS_H_
#define _SYSTEM_CLASS_H_

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "InputClass.h"
#include "GraphicsClass.h"

class SystemClass{ 
private:
	LPCSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass* m_Input;
	GraphicsClass* m_Graphics;

	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Run();
	void Shutdown();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static SystemClass* ApplicationHandle = nullptr;

#endif