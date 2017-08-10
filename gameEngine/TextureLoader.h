#pragma once

#include <vector>
#include<glm\glm.hpp>
#include <GL\glew.h>
#include <string>

#include "TextureBase.h"

namespace gE
{


	class TextureLoader
	{
	public:
		TextureLoader();
		~TextureLoader();

		GLuint loadTexture(std::string path);


	};


}
