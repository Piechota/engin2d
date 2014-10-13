#ifndef _TIMER_
#define _TIMER_

#include "Headers.h"

class Timer
{
private:
	static float deltaTime;
	static float lastCall;

public:
	static void update()
	{
		if (lastCall = 0.f)
		{
			lastCall = SDL_GetTicks();
		}
		deltaTime = SDL_GetTicks() - lastCall;
		lastCall = SDL_GetTicks();
	}
	static float getDeltaTime() { return deltaTime; }
};

#endif