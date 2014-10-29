#include "Timer.h"

Time Timer::deltaTime;
Clock Timer::clock;

void Timer::update()
{
	deltaTime = clock.getElapsedTime();
	clock.restart();
}
float Timer::getDeltaTime() { return deltaTime.asSeconds(); }