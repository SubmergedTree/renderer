#pragma once

#include <GL/glew.h>

class TextureBase
{
public:
	TextureBase(GLuint textureID);
	~TextureBase();

	GLuint getTextureID();

private:
	GLuint textureID;
};

