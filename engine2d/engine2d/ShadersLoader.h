#ifndef _SHADERS_LOADER_
#define _SHADERS_LOADER_

#include "Headers.h"

inline void ShaderVertexCreate(GLuint &program, const char** shader)
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
	std::cout << info;
	delete[] info;

	glAttachShader(program, vs_shader);
}
inline void ShaderFragmentCreate(GLuint &program, const char** shader)
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
	std::cout << info;
	delete[] info;

	glAttachShader(program, fs_shader);
}
inline void ShaderVertexFragmentLink(GLuint &program, const char** vertex_shader, const char** fragment_shader)
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
	std::cout << info;
	delete[] info;
}


#endif