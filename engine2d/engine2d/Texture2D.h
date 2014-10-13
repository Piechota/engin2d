#ifndef _TEXTURE_2D_
#define _TEXTURE_2D_

#include "Headers.h"

class Texture2D
{
private:
	string _fileName;
	GLuint _textureID;

public:
	string GetFileName();
	GLuint GetTextureID();

	Texture2D(string);
	void bind();
};
#endif