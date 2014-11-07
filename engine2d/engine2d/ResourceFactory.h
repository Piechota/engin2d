#ifndef _RESOURCE_FACTORY_
#define _RESOURCE_FACTORY_

#include "Headers.h"
#include "Texture2D.h"
#include "Pawn.h"

typedef map<string, Texture2D*> texturesMap;
class ResourceFactory
{
private:
	ResourceFactory(){}
	~ResourceFactory();

	texturesMap _textures;

public:
	static const string resource;
	vector<Pawn*> pawns;
	Texture2D* load(string);
	void AddPawn(Pawn* pawn);

	static ResourceFactory& GetInstance()
	{
		static ResourceFactory instance;
		return instance;
	}
};

#endif