#pragma once

#include <string>

#include "Color.h"
#include "Texture.h"

#include <gl/glew.h>

#define SHADER_VERTEX GL_VERTEX_SHADER
#define SHADER_FRAGMENT GL_FRAGMENT_SHADER

class GLRenderer
{
	unsigned int vertexBuffer;
	unsigned int indexBuffer;

	int screenWidth;
	int screenHeight;

	double ScreenCordsToGLCords(double x, int size);

public:
	unsigned int currentShader;

	GLRenderer(int screenWidth, int screenHeight);

	unsigned int CreateShaderProgram();
	void UseShaderProgram(unsigned int programId);

	void LinkShaderToProgram(unsigned int programId, unsigned int shaderId);
	unsigned int CompileShader(std::string path, unsigned int shaderType);

	void Clear(Color color);
	
	void DrawQuad(double posX, double posY, double sizeX, double sizeY, Color color);
	void DrawQuadTextured(double posX, double posY, Texture* tex, Color color, double scaleX = 1, double scaleY = 1);
};