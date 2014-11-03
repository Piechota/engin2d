#include "Terrain.h"
#include "ResourceFactory.h"


GLfloat rightG = 2.0f;
GLfloat topG = 2.0f;
GLfloat closeG = 1.0f;
GLfloat wideG = 10.0f;

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
	mapFile.open(ResourceFactory::resource + file);

	if (!mapFile.is_open())
	{
		cout << "nie mozna otworzyc mapy" << endl;
		return;
	}

	string buffer;
	char mapTile;

	getline(mapFile, buffer);
	_width = stoi(buffer);

	getline(mapFile, buffer);
	_height = stoi(buffer);

	_tiles = new MySprite**[_width];
	for (int i = 0; i < _width; i++)
	{
		_tiles[i] = new MySprite*[_height];
	}
	for (int i = 0; i < _width * _height; i++)
	{
		int x, y;
		x = i%_width;
		y = (_height - 1) - ((i - x) / _width);

		mapFile >> mapTile;

		if (mapTile == 's')
		{
			SetViewPos(mx_vector2(x, y));
			_startGrid = mx_vector2(x, y);
		}
		_tiles[x][y] = new MySprite(ResourceFactory::GetInstance().load(string() + mapTile + ".png"));
	}

	mapFile.close();
}

void Terrain::SetViewSize(mx_vector2 winSize, mx_vector2 size)
{
	int w = winSize[0], h = winSize[1];

	rightG = size[0];
	topG = size[1];

	glViewport(0, 0, w, h);
	MySprite::pMatrix.LoadIdentity();

	if (w < h && w > 0)
		topG = topG*h / w;
	else if (w > h && h > 0)
		rightG = rightG*w / h;


		MySprite::pMatrix.Ortho(0.0f, rightG, 0.0f, topG, closeG, wideG);
}

void Terrain::SetViewPos(mx_vector2 position)
{
	_currentPosition = position;
}

void Terrain::update()
{
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			_tiles[x][y]->update();
			_tiles[x][y]->draw(mx_vector2(x, y) - _currentPosition + mx_vector2(rightG / 2.f, topG / 2.f), 0);
		}
	}
}

void Terrain::MoveByVector(mx_vector2 delta)
{
	_currentPosition += delta;
}

mx_vector2 Terrain::GetStartPoint()
{
	return _startGrid;
}