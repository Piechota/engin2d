#include "Sprite.h"

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

	"in vec2 TexCoord;							\n"

	"uniform sampler2D tex;						\n"

	"out vec4 Color;							\n"

	"void main()								\n"
	"{											\n"
	"	Color = texture(tex, TexCoord);			\n"
	"}											\n"
};

GLfloat tile[] =
{
	-.5f, .5f, -5.0f,
	-.5f, -.5f,-5.0f,
	.5f, -.5f, -5.0f,
	.5f, .5f,  -5.0f
};

GLuint MySprite::program;

mx_matrix4 MySprite::pMatrix;

MySprite::MySprite(Texture2D* texture, int frameCount, float framesPerSecond)
{
	_texture = texture;
	_frameCount = frameCount;
	_framesPerSecond = framesPerSecond;

	tile_coord[0] = 0.0f;				tile_coord[1] = 0.0f;
	tile_coord[2] = 1.0f / _frameCount; tile_coord[3] = 0.0f;
	tile_coord[4] = 1.0f / _frameCount; tile_coord[5] = -1.0f;
	tile_coord[6] = 0.0f;				tile_coord[7] = -1.0f;

	_state = ANIMATELESS;

	glGenBuffers(2, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tile), tile, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tile_coord), tile_coord, GL_DYNAMIC_DRAW);

	if (!glIsProgram(program))
	{
		ShaderVertexFragmentLink(program, vs, fs);
		glUseProgram(program);
	}

	
}

void MySprite::update()
{
	if (_state == ANIMATELESS)
	{
		return;
	}
	_currentFrame += Timer::getDeltaTime() * _framesPerSecond;

	float changeToFrame;

	if (_state != SMOOTH)
		changeToFrame = (int)_currentFrame;
	else
		changeToFrame = _currentFrame;

	if (changeToFrame >= _frameCount )
	{
		changeToFrame = 0;
		_currentFrame = 0;
	}
	tile_coord[0] = (float)changeToFrame / _frameCount;
	tile_coord[2] = (float)(changeToFrame + 1) / _frameCount;
	tile_coord[4] = (float)(changeToFrame + 1) / _frameCount;
	tile_coord[6] = (float)changeToFrame / _frameCount;

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tile_coord), tile_coord, GL_DYNAMIC_DRAW);
}

void MySprite::draw(mx_vector2 position, float deegre)
{
	mx_matrix4 mvMatrix;
	mvMatrix.LoadIdentity();
	mvMatrix.translate(position[0], position[1], 0.f);
	mvMatrix.rotate(0.f, 0.f, -1.f, deegre);

	mvMatrix = pMatrix * mvMatrix;
	glUseProgram(program);

	_texture->bind();
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glUniformMatrix4fv(glGetUniformLocation(program, "mvpMatrix"), 1, GL_TRUE, mvMatrix.data);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void MySprite::draw(mx_vector2 position, float deegre, float axis)
{
	mx_matrix4 mvMatrix;
	mvMatrix.LoadIdentity();
	mvMatrix.translate(position[0], position[1], 0.f);
	mvMatrix.rotate(0.f, 0.f, axis, deegre);

	mvMatrix = pMatrix * mvMatrix;
	glUseProgram(program);

	_texture->bind();
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glUniformMatrix4fv(glGetUniformLocation(program, "mvpMatrix"), 1, GL_TRUE, mvMatrix.data);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void MySprite::play()
{
	_state = ANIMATE;
	_currentFrame = 0.f;
}

void MySprite::resume()
{
	_state = ANIMATE;
}

void MySprite::pause()
{
	_state = ANIMATELESS;
}

void MySprite::smoothSwitch()
{
	_state = SMOOTH;
}