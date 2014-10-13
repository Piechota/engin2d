#ifndef _SPRITE_
#define _SPRITE_

#include "Headers.h"
#include "Texture2D.h"
#include "ShadersLoader.h"
#include "Timer.h"

const char* vs[] =
{
	"#version 330								\n"

	"layout(location=0) in vec4 inPosition;		\n"
	"layout(location=1) in vec2 inTexCoord;		\n"

	"uniform mat4 mvpMatrix;					\n"

	"out vec2 TexCoord;							\n"

	"void main()								\n"
	"{											\n"
	"	gl_Position = mvpMatrix * inPosition;	\n"
	"	TexCoord = inTexCoord;					\n"
	"}											\n"
};
const char* fs[] =
{
	"#version 330								\n"

	"in vec2 inTexCoord;						\n"

	"uniform sampler2D tex;						\n"

	"out vec4 Color								\n"

	"void main()								\n"
	"{											\n"
	"	Color = texture(tex, inTexCoord);		\n"
	"}											\n"
};

GLuint vbo[2];

GLfloat tile[] =
{
	-1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f
};

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
	Sprite(Texture2D*, int, float);
	void update();
	void draw(mx_vector2, float);
	void play();
	void resume();
	void pause();
};

#endif