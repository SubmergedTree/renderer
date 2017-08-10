#include "TextureBase.h"



TextureBase::TextureBase(GLuint textureID) : textureID(textureID)
{
}


TextureBase::~TextureBase()
{
}

GLuint TextureBase::getTextureID()
{
	return textureID;
}
