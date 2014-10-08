#ifndef _GRAPHICS_CLASS_H_
#define _GRAPHICS_CLASS_H_

#include <Windows.h>

const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass{  
private:
	bool Render();

public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
};

#endif