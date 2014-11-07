#include "Headers.h"
#include "Terrain.h"
#include "ResourceFactory.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Window window;

Terrain* terrain;

void InitScene()
{
	window.create(VideoMode(), "Engine2D", Style::Fullscreen);

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		cout << "glew faild" << endl;
	}

	glClearColor(0.0f, 0.f, 0.f, 1.f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	terrain = new Terrain("map.txt", mx_vector2(window.getSize().x, window.getSize().y), 
							mx_vector2(6, 6));
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

	bool run = true;
	while (run)
	{
		Timer::update();
		Event event;		//SFML
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				run = false;
				break;
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
					run = false;
				break;
			}
		}

		TerrainDisplay();
		window.display();
	}
	window.close();

	delete terrain;

	return 0;
}