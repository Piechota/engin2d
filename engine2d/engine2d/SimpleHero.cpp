#include "SimpleHero.h"

SimpleHero::SimpleHero(MySprite* sprite, mx_vector2 position, float speed, float angle) :	Pawn(sprite, position, angle),	
																							moveSpeed(speed)
{
}

void SimpleHero::Update(mx_vector2 worldOffset)
{
	mx_vector2 direction;
	sprite->pause();
	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
	{
		direction += mx_vector2(0, 1);
		sprite->resume();
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
	{
		direction += mx_vector2(0, -1);
		sprite->resume();
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
	{
		direction += mx_vector2(-1, 0);
		sprite->resume();
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
	{
		direction += mx_vector2(1, 0);
		sprite->resume();
	}
	position += direction.normalize() * moveSpeed * Timer::getDeltaTime();

	Vector2i mousePosition = Mouse::getPosition();
	mx_vector3 mouse;
	mouse.data[0] = mousePosition.x;
	mouse.data[1] = mousePosition.y;
	mouse.data[2] = 0.f;

	mx_vector3 screenCenter;
	screenCenter.data[0] = window.getSize().x * 1.f / 2.f;
	screenCenter.data[1] = window.getSize().y * 1.f / 2.f;
	screenCenter.data[2] = 0.f;

	mouse -= screenCenter;

	mouse.normalize();

	angle = -acos(dot3(mx_vector3(1.0f, 0.f, 0.f), mouse)) * 57.2957795f;

	mx_vector3 up = mx_vector3(1.0f, 0.f, 0.f) * mouse;
	up.normalize();

	sprite->update();
	sprite->draw(position + worldOffset, angle, up[2]);
}

mx_vector2 SimpleHero::GetPosition()
{
	return position;
}