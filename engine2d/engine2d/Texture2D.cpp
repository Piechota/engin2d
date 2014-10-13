#include <iostream>

#include "Texture2D.h"

string Texture2D::GetFileName()
{
	return _fileName;
}
GLuint Texture2D::GetTextureID()
{
	return _textureID;
}

Texture2D::Texture2D(string file)
{
	SDL_Surface* texture = IMG_Load(file.c_str());
	if (!texture)
	{
		cout << "Brak tektury" << endl;
		return;
	}

	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels);

	SDL_FreeSurface(texture);
}

void Texture2D::bind()
{
	glBindTexture(GL_TEXTURE_2D, _textureID);
}