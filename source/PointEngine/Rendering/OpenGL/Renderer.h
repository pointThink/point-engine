#pragma once

#include <string>

#include <glad/glad.h>

#include "Rendering/Window.h"
#include "Utils/Utils.h"
#include "Texture.h"
#include "Vector.h"
#include "Core.h"

#define SHADER_VERTEX GL_VERTEX_SHADER
#define SHADER_FRAGMENT GL_FRAGMENT_SHADER

namespace PE
{
	namespace Rendering
	{
class ENGINE_API GLRenderer
		{
			Window* window;

			unsigned int vertexBuffer;
			unsigned int indexBuffer;

			int screenWidth;
			int screenHeight;

			double ScreenCordsToGLCords(double x, int size);

		public:
			unsigned int currentShader;

			GLRenderer(Window* window);

			unsigned int CreateShaderProgram();
			void UseShaderProgram(unsigned int programId);

			void LinkShaderToProgram(unsigned int programId, unsigned int shaderId);
			unsigned int CompileShader(std::string path, unsigned int shaderType);

			void Clear(Utils::Color color);
			void PresentRenderer();

			void DrawQuad(Vector pos, Vector size, Utils::Color color);
			void DrawQuadTextured(Vector pos, Vector size, Texture* tex, Utils::Color color);
		};
	}
}
