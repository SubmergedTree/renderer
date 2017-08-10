#pragma once

#include "ModelLoader.h"
#include "TextureBase.h"

namespace gE
{


	class TexturedModel
	{
	public:
		TexturedModel(Model * model, TextureBase * texture);
		TexturedModel(Model * model, TextureBase * texture, TextureBase* specular);

		~TexturedModel();

		Model* getModel();
		TextureBase* getTexture();
		TextureBase* getSpecular();

	private:
		Model * model;
		TextureBase* texture;
		TextureBase* specular;
	};

}