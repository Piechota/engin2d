#ifndef _SPRITE_
#define _SPRITE_

#include "Headers.h"
#include "Texture2D.h"

class Sprite
{
private:
	int _frameCount;
	int _startFrame;
	int _endFrame;
	float _currentFrame;
	enum State
	{
		IGNOR,
		ANIMATE,
		STOP_ANIMATE
	} _state;
	float _framesPerSecond;

public:
	Sprite(Texture2D, int, float);
	void update();
	void draw(mx_vector2, float);
	void play();
	void resume();
	void pause();
};

#endif