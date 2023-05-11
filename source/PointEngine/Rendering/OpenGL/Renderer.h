#pragma once

#include <string>

#include "Utils/Utils.h"
#include "Texture.h"
#include "Vector.h"

#include <glad/glad.h>

#define SHADER_VERTEX GL_VERTEX_SHADER
#define SHADER_FRAGMENT GL_FRAGMENT_SHADER

namespace PE
{
	namespace Rendering
	{
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

			void Clear(Utils::Color color);

			void DrawQuad(Vector pos, Vector size, Utils::Color color);
			void DrawQuadTextured(Vector pos, Vector size, Texture* tex, Utils::Color color);
		};
	}
}