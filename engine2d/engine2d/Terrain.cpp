#include "Terrain.h"
#include "ResourceFactory.h"

Terrain::~Terrain()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
			delete _tiles[x][y];
	}	
	for (int x = 0; x < _width; x++)
		delete[] _tiles[x];

	delete[] _tiles;
}

Terrain::Terrain(string file)
{
	ifstream mapFile;
	mapFile.open(file);

	if (!mapFile.is_open())
		return;

	string buffer;
	char mapTile;

	getline(mapFile, buffer);
	_width = stoi(buffer);

	getline(mapFile, buffer);
	_height = stoi(buffer);

	_tiles = new MySprite**[_width];
	for (int i = 0; i < _width; i++)
		_tiles[i] = new MySprite*[_height];

	for (int i = 0; i < _width * _height; i++)
	{
		int x, y;
		x = i%_height;
		y = (i - x) / _height;

		mapFile >> mapTile;
		_tiles[x][y] = new MySprite(ResourceFactory::GetInstance().load(ResourceFactory::resource + mapTile + ".jpg"));
	}

	mapFile.close();
}

void Terrain::SetViewSize(mx_vector2 size)
{
	_size = size;
}

void Terrain::SetViewPos(mx_vector2 position)
{
	_currentPosition = position;
}

void Terrain::update()
{
	int fromX = (int)(_currentPosition[0] - _size[0]);
	int toX = (int)(_currentPosition[0] + _size[0]);

	int fromY = (int)(_currentPosition[1] - _size[1]);
	int toY = (int)(_currentPosition[1] + _size[1]);

	if (fromX < 0)
	{
		fromX = 0;
		toX = 2 * _size[0];
	}
	if (toX > _width)
	{
		toX = _width - 1;
		fromX = _width - 1 - 2 * _size[0];
	}
	if (fromY < 0)
	{
		fromY = 0;
		toY = 2 * _size[1];
	}
	if (toY > _height)
	{
		toY = _height - 1;
		fromY = _height - 1 - 2 * _size[1];
	}

	//for (int x = fromX; x < toX; x++)
	//{
	//	for (int y = fromY; y < toY; y++)
	//	{
	//		_tiles[x][y]->update();
	//		_tiles[x][y]->draw(mx_vector2(x, y), 0.f);
	//	}
	//}

	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			//_tiles[x][y]->update();
			_tiles[x][y]->draw(mx_vector2(x, y), 0.f);
		}
	}
}