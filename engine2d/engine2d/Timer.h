#ifndef _TIMER_
#define _TIMER_

#include "Headers.h"

class Timer
{
private:
	static float deltaTime;
	static float lastCall;

public:
	static void update();
	static float getDeltaTime();
};

#endif