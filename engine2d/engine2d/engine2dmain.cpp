#include <GL/glew.h>
#include <SDL.h>

#include "matrix.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

GLfloat left = -0.5f;
GLfloat right = 0.5f;
GLfloat bottom = -0.5f;
GLfloat top = 0.5f;
GLfloat close = 1.0f;
GLfloat wide = 10.0f;

GLuint vbo[2];

SDL_Window *mainwindow;

mx_matrix4 pMatrix;

GLfloat tile[] =
{
	-1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f
};

GLfloat tile_coord[] =
{
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, -1.0f,
	0.0f, -1.0f
};

void ShaderVertexCreate(GLuint program, const char** shader)
{
	if (glIsProgram(program) == GL_FALSE)
		program = glCreateProgram();

	GLuint vs_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs_shader, 1, shader, NULL);

	glCompileShader(vs_shader);
	glAttachShader(program, vs_shader);
}
void ShaderFragmentCreate(GLuint program, const char** shader)
{
	if (glIsProgram(program) == GL_FALSE)
		program = glCreateProgram();

	GLuint fs_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs_shader, 1, shader, NULL);

	glCompileShader(fs_shader);
	glAttachShader(program, fs_shader);
}
void ShaderVertexFragmentLink(GLuint program, const char** vertex_shader, const char** fragment_shader)
{
	ShaderVertexCreate(program, vertex_shader);
	ShaderFragmentCreate(program, fragment_shader);

	glLinkProgram(program);
}

void Reshape()
{
	int w, h;

	SDL_GetWindowSize(mainwindow, &w, &h);

	glViewport(0, 0, w, h);
	pMatrix.LoadIdentity();

	if (w < h && w > 0)
		pMatrix.Ortho(left, right, bottom*h / w, top*h / w, close, wide);
	else if (w > h && h > 0)
		pMatrix.Ortho(left*w / h, right*w / h, bottom, top, close, wide);
	else
		pMatrix.Ortho(left, right, bottom, top, close, wide);
}

void InitScene()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//TO POWINNO BYC W SPRITE

	glGenBuffers(2, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tile), tile, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tile_coord), tile_coord, GL_STATIC_DRAW);

	//TO POWINNO BYC W SPRITE

}

int main(int argc, char *argv[])
{
	SDL_GLContext maincontext;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	mainwindow = SDL_CreateWindow("Engine2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	maincontext = SDL_GL_CreateContext(mainwindow);
	SDL_GL_SetSwapInterval(1);

	GLenum error = glewInit();

	InitScene();

	Reshape();

	bool run = true;
	while (run)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				run = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					run = false;
					break;
				}
				break;
			}
		}

		SDL_GL_SwapWindow(mainwindow);
	}
	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();

	return 0;
}