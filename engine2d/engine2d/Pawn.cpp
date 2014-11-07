#include "Pawn.h"
#include "ResourceFactory.h"

Pawn::~Pawn()
{
	delete sprite;
}
Pawn::Pawn(MySprite* sprite, mx_vector2 position, float angle)
{
	this->sprite = sprite;
	this->position = position;
	this->angle = angle;
	ResourceFactory::GetInstance().AddPawn(this);
}

void Pawn::Update(mx_vector2 worldOffset)
{
	
}