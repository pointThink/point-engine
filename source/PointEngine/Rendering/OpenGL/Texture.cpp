#include "Texture.h"

#include "Renderer.h"

#include <iostream>
#include "stb_image.h"

namespace PE
{
	namespace Rendering
	{
		Texture::Texture(std::string path)
		{
			glGenTextures(1, &textureMap);
			glBindTexture(GL_TEXTURE_2D, textureMap);

			stbi_set_flip_vertically_on_load(false);

			width = 0;
			height = 0;

			buffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, STBI_rgb_alpha);

			std::cout << bitsPerPixel << std::endl;

			if (!buffer)
			{
				std::cout << stbi_failure_reason() << std::endl;
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

			glBindTexture(GL_TEXTURE_2D, 0);


			// Check for errors
			/*
			while (GLenum error = glGetError())
			{
				std::cout << "[OPENGL ERROR] " << error << std::endl;
			}
			*/
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &textureMap);
		}

		void Texture::Bind(unsigned int slot)
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, textureMap);
		}

		void Texture::Unbind()
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}