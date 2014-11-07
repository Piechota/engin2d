#ifndef _TERRAIN_
#define _TERRAIN_

#include "Headers.h"
#include "Sprite.h"
#include "SimpleHero.h"

class Terrain
{
private:
	MySprite ***_tiles;
	string _fileName;
	int _width;
	int _height;

	mx_vector2 _size;
	mx_vector2 _currentPosition;
	mx_vector2 _startGrid;


public:
	Terrain(string file, mx_vector2, mx_vector2);
	void SetViewSize(mx_vector2, mx_vector2);
	void SetViewPos(mx_vector2);
	void MoveByVector(mx_vector2);

	mx_vector2 GetStartPoint();
	mx_vector2 GetGridInWorldPosition(mx_vector2 grid);
	mx_vector2 GetCurrentPosition();

	void update();
	~Terrain();
};

#endif