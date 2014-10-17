#ifndef _SPRITE_
#define _SPRITE_

#include "Headers.h"
#include "Texture2D.h"
#include "Timer.h"

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
		ANIMATELESS
	} _state;
	float _framesPerSecond;
	Texture2D* _texture;

	static GLuint program;

	GLfloat tile_coord[8];

public:
	static mx_matrix4 pMatrix;

	Sprite(Texture2D*, int = 1, float = 0.0f);
	void update();
	void draw(mx_vector2, float);
	void play();
	void resume();
	void pause();
};

#endif