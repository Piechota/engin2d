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
	Image texture;
	//texture.createMaskFromColor(Color(255, 255, 255), 255);

	if (!texture.loadFromFile(file))
	{
		cout << "Brak tektury" << endl;
		return;
	}

	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.getSize().x, texture.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr());

	_fileName = file;
}

void Texture2D::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureID);
}