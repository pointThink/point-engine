#pragma once

#include <string>

class Texture
{
private:
	unsigned int textureMap;

	std::string filePath;

	unsigned char* buffer;
	int width, height, bitsPerPixel;

public:
	Texture(std::string path);
	~Texture();

	void Bind(unsigned int slot = 0);
	void Unbind();

	inline int GetWidth() { return width; };
	inline int GetHeight() { return height; };
};