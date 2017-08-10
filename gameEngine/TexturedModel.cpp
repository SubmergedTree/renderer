#include "TexturedModel.h"

namespace gE
{

	TexturedModel::TexturedModel(Model * model, TextureBase * texture)
	{
		this->model = model;
		this->texture = texture;
	}

	TexturedModel::TexturedModel(Model * model, TextureBase * texture, TextureBase * specular)
	{
		this->model = model;
		this->texture = texture;
		this->specular = specular;
	}


	TexturedModel::~TexturedModel()
	{
		delete model;
		delete texture;

		model = nullptr;
		texture = nullptr;
	}

	Model * TexturedModel::getModel()
	{
		return model;
	}

	TextureBase * TexturedModel::getTexture()
	{
		return texture;
	}

	TextureBase * TexturedModel::getSpecular()
	{
		return specular;
	}


}