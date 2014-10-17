#include "Timer.h"

float Timer::deltaTime;
float Timer::lastCall;

void Timer::update()
{
	if (lastCall = 0.f)
	{
		lastCall = SDL_GetTicks();
	}
	deltaTime = SDL_GetTicks() - lastCall;
	lastCall = SDL_GetTicks();
}
float Timer::getDeltaTime() { return deltaTime; }