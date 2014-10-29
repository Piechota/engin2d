#ifndef _TIMER_
#define _TIMER_

#include "Headers.h"

class Timer
{
private:
	static Time deltaTime;
	static Clock clock;

public:
	static void update();
	static float getDeltaTime();
};

#endif