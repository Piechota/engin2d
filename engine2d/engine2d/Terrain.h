#ifndef _TERRAIN_
#define _TERRAIN_

#include "Headers.h"
#include "Sprite.h"

class Terrain
{
private:
	MySprite ***_tiles;
	string _fileName;
	int _width;
	int _height;

	mx_vector2 _size;
	mx_vector2 _currentPosition;


public:
	Terrain(string file);
	void SetViewSize(mx_vector2);
	void SetViewPos(mx_vector2);

	void update();
	~Terrain();
};

#endif