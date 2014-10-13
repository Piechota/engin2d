#ifndef _RESOURCE_FACTORY_
#define _RESOURCE_FACTORY_

#include "Headers.h"
#include "Texture2D.h"

typedef map<string, Texture2D*> texturesMap;
class ResourceFactory
{
private:
	ResourceFactory(){}
	~ResourceFactory();

	texturesMap _textures;

public:
	Texture2D* load(string);

	static ResourceFactory& GetInstance()
	{
		static ResourceFactory instance;
		return instance;
	}
};

#endif