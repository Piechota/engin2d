#include "Headers.h"
#include "Terrain.h"
#include "ResourceFactory.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Window window;

Terrain* terrain;
float moveSpeed = 1.0f;

MySprite* hero;
mx_vector2 heroPosition;
float angle;

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
	terrain = new Terrain(ResourceFactory::resource + "map.txt");
	terrain->SetViewSize(mx_vector2(window.getSize().x, window.getSize().y), mx_vector2(8, 8));

	hero = new MySprite(ResourceFactory::GetInstance().load(ResourceFactory::resource + "hero.png"), 3, 10.0f);
	hero->play();
	heroPosition = terrain->GetStartPoint();
}

void TerrainDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	terrain->update();

	hero->update(); 
	hero->draw(terrain->GetCenter(), angle);


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
		
		hero->pause();
		mx_vector2 direction;
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
		{
			direction += mx_vector2(0, moveSpeed * Timer::getDeltaTime()); 
			hero->resume();
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			direction += mx_vector2(0, -moveSpeed * Timer::getDeltaTime());
			hero->resume();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			direction += mx_vector2(-moveSpeed * Timer::getDeltaTime(), 0);
			hero->resume();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		{
			direction += mx_vector2(moveSpeed * Timer::getDeltaTime(), 0);
			hero->resume();
		}

		Vector2i mp = Mouse::getPosition();
		mx_vector2 mouseVector;
		mouseVector[0] = mp.x;
		mouseVector[1] = mp.y;

		mx_vector2 center;
		center[0] = window.getSize().x / 2;
		center[1] = window.getSize().y / 2;

		mouseVector -= center;
		mouseVector.normalize();

		angle = acos(dot2(mouseVector, mx_vector2(0, 1))) * 57.2957795f;
		cout << angle << endl;

		terrain->MoveByVector(direction);

		TerrainDisplay();
		window.display();
	}
	window.close();

	delete terrain;
	delete hero;

	return 0;
}