#include "Bitmap.h"/*
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include "Bitmap.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Libraries/stb_image.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	// Assigns the type of the texture ot the texture object
	type = texType;

	// Stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, STBI_rgb_alpha);

	if (!bytes) {
		std::cout << "Error loading image: " << stbi_failure_reason() << std::endl;
		return;
	}

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	if (!ID) {
		std::cout << "Error generating texture object." << std::endl;
		return;
	}
	// Assigns the texture to a Texture Unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);

	GLenum err1 = glGetError();
	if (err1 != GL_NO_ERROR) {
		std::cout << "OpenGL error after glTexImage2D: " << err1 << std::endl;
		return;
	}

	// Generates MipMaps
	glGenerateMipmap(texType);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << "OpenGL error after glGenerateMipmap: " << err << std::endl;
	}

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(texType, 0);
}*/