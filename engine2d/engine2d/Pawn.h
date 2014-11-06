#ifndef _PAWN_
#define _PAWN_

#include "Headers.h"
#include "Sprite.h"

class Pawn
{
private:
	MySprite* sprite;

public:
	mx_vector2 position;
	float angle;

	Pawn(MySprite* sprite, mx_vector2 position, float angle = 0.f);
	virtual void Update();
};

#endif