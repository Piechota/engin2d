#ifndef _SIMPLE_HERO_
#define _SIMPLE_HERO_

#include "Pawn.h"
class SimpleHero :
	public Pawn
{
private:
	float moveSpeed;
public:
	SimpleHero(MySprite* sprite, mx_vector2 position, float speed, float angle = 0.f);

	virtual void Update(mx_vector2 worldOffset);
	mx_vector2 GetPosition();
};

#endif