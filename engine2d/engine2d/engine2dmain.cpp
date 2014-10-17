#include "Headers.h"
#include "Terrain.h"
#include "ResourceFactory.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

GLfloat leftV = -0.5f;
GLfloat rightV = 0.5f;
GLfloat bottomV = -0.5f;
GLfloat topV = 0.5f;
GLfloat closeV = 1.0f;
GLfloat wideV = 10.0f;

SDL_GLContext maincontext;
SDL_Window *mainwindow;

Terrain* terrain;

void Reshape()
{
	int w, h;

	SDL_GetWindowSize(mainwindow, &w, &h);

	glViewport(0, 0, w, h);
	Sprite::pMatrix.LoadIdentity();

	if (w < h && w > 0)
		Sprite::pMatrix.Ortho(leftV, rightV, bottomV*h / w, topV*h / w, closeV, wideV);
	else if (w > h && h > 0)
		Sprite::pMatrix.Ortho(leftV*w / h, rightV*w / h, bottomV, topV, closeV, wideV);
	else
		Sprite::pMatrix.Ortho(leftV, rightV, bottomV, topV, closeV, wideV);
}

void InitScene()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	mainwindow = SDL_CreateWindow("Engine2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	maincontext = SDL_GL_CreateContext(mainwindow);
	SDL_GL_SetSwapInterval(1);

	IMG_Init(IMG_INIT_PNG);

	GLenum error = glewInit();

	glClearColor(0.5f, 0.f, 0.f, 1.f);

	terrain = new Terrain(ResourceFactory::resource + "map.txt");
	terrain->SetViewSize(mx_vector2(2, 2));
	terrain->SetViewPos(mx_vector2(1, 1));
}

void TerrainDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	terrain->update();

	glFlush();
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

		TerrainDisplay();
		SDL_GL_SwapWindow(mainwindow);
	}
	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();

	delete terrain;

	return 0;
}