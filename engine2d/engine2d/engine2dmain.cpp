#include "Headers.h"
#include "Texture2D.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

GLfloat leftV = -0.5f;
GLfloat rightV = 0.5f;
GLfloat bottomV = -0.5f;
GLfloat topV = 0.5f;
GLfloat closeV = 1.0f;
GLfloat wideV = 10.0f;

GLuint vbo[2];

SDL_GLContext maincontext;
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
		pMatrix.Ortho(leftV, rightV, bottomV*h / w, topV*h / w, closeV, wideV);
	else if (w > h && h > 0)
		pMatrix.Ortho(leftV*w / h, rightV*w / h, bottomV, topV, closeV, wideV);
	else
		pMatrix.Ortho(leftV, rightV, bottomV, topV, closeV, wideV);
}

void InitScene()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	mainwindow = SDL_CreateWindow("Engine2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	maincontext = SDL_GL_CreateContext(mainwindow);
	SDL_GL_SetSwapInterval(1);

	IMG_Init(IMG_INIT_PNG);

	GLenum error = glewInit();

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