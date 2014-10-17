#include "Sprite.h"

void ShaderVertexCreate(GLuint &program, const char** shader)
{
	GLint Result = GL_FALSE;
	int logLength;
	char* info;

	if (glIsProgram(program) == GL_FALSE)
		program = glCreateProgram();

	GLuint vs_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs_shader, 1, shader, NULL);

	glCompileShader(vs_shader);

	glGetShaderiv(vs_shader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vs_shader, GL_INFO_LOG_LENGTH, &logLength);

	info = new char[logLength];
	glGetShaderInfoLog(vs_shader, logLength, NULL, info);
	cout << info;
	delete[] info;

	glAttachShader(program, vs_shader);
}
void ShaderFragmentCreate(GLuint &program, const char** shader)
{
	GLint Result = GL_FALSE;
	int logLength;
	char* info;

	if (glIsProgram(program) == GL_FALSE)
		program = glCreateProgram();

	GLuint fs_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs_shader, 1, shader, NULL);

	glCompileShader(fs_shader);

	glGetShaderiv(fs_shader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fs_shader, GL_INFO_LOG_LENGTH, &logLength);

	info = new char[logLength];
	glGetShaderInfoLog(fs_shader, logLength, NULL, info);
	cout << info;
	delete[] info;

	glAttachShader(program, fs_shader);
}
void ShaderVertexFragmentLink(GLuint &program, const char** vertex_shader, const char** fragment_shader)
{
	ShaderVertexCreate(program, vertex_shader);
	ShaderFragmentCreate(program, fragment_shader);

	glLinkProgram(program);

	GLint Result = GL_FALSE;
	int logLength;
	char* info;

	glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

	info = new char[logLength];
	glGetProgramInfoLog(program, logLength, NULL, info);
	cout << info;
	delete[] info;
}

const char* vs[] =
{
	"#version 330								\n"

	"layout(location=0) in vec4 inPosition;		\n"
	"layout(location=1) in vec2 inTexCoord;		\n"

	"uniform mat4 mvpMatrix;					\n"

	"out vec2 TexCoord;							\n"

	"void main()								\n"
	"{											\n"
	"	gl_Position = inPosition;	\n"
	//"	gl_Position = mvpMatrix * inPosition;	\n"
	"	TexCoord = inTexCoord;					\n"
	"}											\n"
};
const char* fs[] =
{
	"#version 330								\n"

	"in vec2 inTexCoord;						\n"

	"uniform sampler2D tex;						\n"

	"out vec4 Color;							\n"

	"void main()								\n"
	"{											\n"
	"	Color = vec4(0, 0, 1, 1);		\n"
	//"	Color = texture(tex, inTexCoord);		\n"
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

GLuint Sprite::program;

mx_matrix4 Sprite::pMatrix;

Sprite::Sprite(Texture2D* texture, int frameCount, float framesPerSecond)
{
	_texture = texture;
	_frameCount = frameCount;
	_framesPerSecond = framesPerSecond;

	tile_coord[0] = 0.0f;				tile_coord[1] = 0.0f;
	tile_coord[2] = 1.0f / _frameCount; tile_coord[3] = 0.0f;
	tile_coord[4] = 1.0f / _frameCount; tile_coord[5] = -1.0f;
	tile_coord[6] = 0.0f;				tile_coord[7] = -1.0f;

	if (!glIsProgram(program))
	{
		glGenBuffers(2, vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tile), tile, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tile_coord), tile_coord, GL_DYNAMIC_DRAW);

		ShaderVertexFragmentLink(program, vs, fs);

		glUseProgram(program);
	}
}

void Sprite::update()
{
	if (_state == ANIMATELESS)
		return;

	_currentFrame += Timer::getDeltaTime() * _framesPerSecond;

	int changeToFrame = (int)_currentFrame;
	if (changeToFrame >= _frameCount)
		changeToFrame = 0;

	tile_coord[0] = (float)changeToFrame / _frameCount;
	tile_coord[2] = (float)(changeToFrame + 1) / _frameCount;
	tile_coord[4] = (float)(changeToFrame + 1) / _frameCount;
	tile_coord[6] = (float)changeToFrame / _frameCount;

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tile_coord), tile_coord, GL_DYNAMIC_DRAW);
}

void Sprite::draw(mx_vector2 position, float deegre)
{
	mx_matrix4 mvMatrix;
	mvMatrix.LoadIdentity();
	//mvMatrix.translate(position[0], position[1], -5.f);
	//mvMatrix.rotate(0.f, 0.f, -1.f, deegre);

	mvMatrix = pMatrix * mvMatrix;

	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	_texture->bind();
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glUniformMatrix4fv(glGetUniformLocation(program, "mvpMatrix"), 1, GL_TRUE, mvMatrix.data);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	glUseProgram(0);
}

void Sprite::play()
{
	_state = ANIMATE;
	_currentFrame = 0.f;
}

void Sprite::resume()
{
	_state = ANIMATE;
}

void Sprite::pause()
{
	_state = ANIMATELESS;
}