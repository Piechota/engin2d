#ifndef _PAWN_
#define _PAWN_

#include "Headers.h"
#include "Sprite.h"

class Pawn
{
protected:
	MySprite* sprite;
	mx_vector2 position;
	float angle;

public:
	Pawn(MySprite* sprite, mx_vector2 position, float angle = 0.f);
	~Pawn();
	virtual void Update(mx_vector2 worldOffset);
};

#endif