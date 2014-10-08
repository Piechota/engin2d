#include "SystemClass.h"

SystemClass::SystemClass()
{
	m_Input = nullptr;
	m_Graphics = nullptr;
}

SystemClass::SystemClass(const SystemClass& other){}
SystemClass::~SystemClass(){}

bool SystemClass::Initialize()
{
	int screenWidth = 0, screenHeight = 0;

	InitializeWindows(screenWidth, screenHeight);

	if (!(m_Input = new InputClass))
		return false;

	m_Input->Initialize();

	if (!(m_Graphics = new GraphicsClass))
		return false;

	return m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
}

void SystemClass::Shutdown()
{
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
	}
	if (m_Input)
		delete m_Input;

	ShutdownWindows();
}

void SystemClass::Run()
{
	MSG msg;
	bool done = false;

	ZeroMemory(&msg, sizeof(MSG));

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT || !Frame())
			done = true;
	}
}

bool SystemClass::Frame()
{
	if (m_Input->IsKeyDown(VK_ESCAPE))
		return false;

	return m_Graphics->Frame();
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
	case WM_KEYDOWN:
		m_Input->KeyDown((unsigned int)wparam);
		return 0;
	case WM_KEYUP:
		m_Input->KeyUp((unsigned int)wparam);
		return 0;

	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSetting;
	int posX, posY;

	ApplicationHandle = this;

	m_hinstance = GetModuleHandle(NULL);

	m_applicationName = "Engine";
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (FULL_SCREEN)
	{
		memset(&dmScreenSetting, 0, sizeof(dmScreenSetting));
		dmScreenSetting.dmSize = sizeof(dmScreenSetting);
		dmScreenSetting.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSetting.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSetting.dmBitsPerPel = 32;
		dmScreenSetting.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSetting, CDS_FULLSCREEN);

		posX = posY = 0;
	}
	else
	{
		screenWidth = 800;
		screenHeight = 600;

		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, 
							posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	ShowCursor(false);
}

void SystemClass::ShutdownWindows()
{
	ShowCursor(true);

	if (FULL_SCREEN)
		ChangeDisplaySettings(NULL, 0);

	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	ApplicationHandle = NULL;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	case WM_DESTROY:
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
}