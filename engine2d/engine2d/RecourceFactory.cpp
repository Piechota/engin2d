#include "ResourceFactory.h"

const string ResourceFactory::resource = "../Resource/";

Texture2D* ResourceFactory::load(string file)
{
	if (!_textures.empty())
	{
		texturesMap::iterator i = _textures.find(file);
		if (i != _textures.end())
			return i->second;
	}

	_textures[file] = new Texture2D(resource + file);
	return _textures[file];
}

void ResourceFactory::AddPawn(Pawn* pawn)
{
	pawns.push_back(pawn);
}

ResourceFactory::~ResourceFactory()
{
	for (texturesMap::iterator i = _textures.begin(); i != _textures.end(); i++)
		delete i->second;

	for_each(pawns.begin(), pawns.end(), [](Pawn* pawn){delete pawn; });
}