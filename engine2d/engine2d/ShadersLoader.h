#ifndef _SHADERS_LOADER_
#define _SHADERS_LOADER_

#include "Headers.h"

void ShaderVertexCreate(GLuint &program, const char** shader)
{
	if (glIsProgram(program) == GL_FALSE)
		program = glCreateProgram();

	GLuint vs_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs_shader, 1, shader, NULL);

	glCompileShader(vs_shader);
	glAttachShader(program, vs_shader);
}
void ShaderFragmentCreate(GLuint &program, const char** shader)
{
	if (glIsProgram(program) == GL_FALSE)
		program = glCreateProgram();

	GLuint fs_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs_shader, 1, shader, NULL);

	glCompileShader(fs_shader);
	glAttachShader(program, fs_shader);
}
void ShaderVertexFragmentLink(GLuint &program, const char** vertex_shader, const char** fragment_shader)
{
	ShaderVertexCreate(program, vertex_shader);
	ShaderFragmentCreate(program, fragment_shader);

	glLinkProgram(program);
}


#endif