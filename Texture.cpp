#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libraries/stb_image.h"

Texture::Texture(const char* image)
{

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, channels;
	stbi_set_flip_vertically_on_load(GL_TRUE);
	unsigned char* loaded_image = stbi_load(image, &width, &height, &channels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, loaded_image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(loaded_image);
}