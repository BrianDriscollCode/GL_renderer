#ifndef TEXTURE_H
#define TEXTURE_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "debugOutput.h"

class Texture {

public:
public:
	unsigned int texture;

	Texture(const char* texturePath)
	{
		DebugOutput debugOutput(true);

		// load texture
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// set filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

		if (data)
		{
			debugOutput.outputGreenText("**SUCCESS**::TEXTURE::FILE_LOADED::", texturePath, "::[tools/texture.h]");
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			debugOutput.outputRedText("ERROR::TEXTURE::FAILED_TO_LOAD::[tools/texture.h]");
		}

		stbi_image_free(data);

	}

	void use()
	{
		glBindTexture(GL_TEXTURE_2D, texture);
	}

};

#endif