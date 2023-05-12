#include "Renderer.h"

#include "GLFW/glfw3.h"
#include "Utils/Utils.h"
#include "Error/Error.h"
#include "Game.h"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

namespace PE
{
	namespace Rendering
	{
		unsigned int GLRenderer::CompileShader(std::string path, unsigned int shaderType)
		{
			std::ifstream file_stream(path);

			std::string line;
			std::string shader_contents;

			while (std::getline(file_stream, line))
			{
				shader_contents = shader_contents + line + '\n';
			}


			unsigned int shader_id = glCreateShader(shaderType);

			const char* source = shader_contents.c_str();
			glShaderSource(shader_id, 1, &source, nullptr);
			glCompileShader(shader_id);

			int comp_result;

			glGetShaderiv(shader_id, GL_COMPILE_STATUS, &comp_result);

			if (comp_result == GL_FALSE)
			{
				int length;
				glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);

				char* message = new char[length];
				glGetShaderInfoLog(shader_id, length * sizeof(char), &length, message);

				std::cout << message << std::endl;

				delete[] message;
				return 0;
			}

			return shader_id;
		}

		unsigned int GLRenderer::CreateShaderProgram()
		{
			return glCreateProgram();
		}

		void GLRenderer::LinkShaderToProgram(unsigned int programId, unsigned int shaderId)
		{
			glAttachShader(programId, shaderId);
		}

		void GLRenderer::UseShaderProgram(unsigned int programId)
		{
			glValidateProgram(programId);
			glLinkProgram(programId);
			glUseProgram(programId);

			currentShader = programId;
		}

		GLRenderer::GLRenderer(Window* window)
		{
			gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

			glGenBuffers(1, &vertexBuffer);
			glGenBuffers(1, &indexBuffer);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);

			// load in the default shaders
			unsigned int program = CreateShaderProgram();

			unsigned int vertexShader = CompileShader("engineRes/shaders/vertex.glsl", SHADER_VERTEX);
			unsigned int fragmentShader = CompileShader("engineRes/shaders/fragment.glsl", SHADER_FRAGMENT);

			LinkShaderToProgram(program, vertexShader);
			LinkShaderToProgram(program, fragmentShader);

			UseShaderProgram(program);

			this->window = window;
		}

		double GLRenderer::ScreenCordsToGLCords(double pos, int size)
		{
			//std::cout << pos << " | " << size << " - " << (pos / size) * 2 - 1 << std::endl;

			return ((pos / size) * 2) - 1;
		}

		void GLRenderer::Clear(Utils::Color color)
		{
			glClearColor(float(color.r) / 255, float(color.g) / 255, float(color.b) / 255, float(color.a / 255));
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void GLRenderer::PresentRenderer()
		{
			//glfwSwapBuffers(window->GetGLFWWindow());
		}

		void GLRenderer::DrawQuad(Vector pos, Vector size, Utils::Color color)
		{
			int screenWidth = window->GetWidth();
			int screenHeight = window->GetHeight();

			glUniform1i(glGetUniformLocation(currentShader, "u_textured"), 0);

			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

			pos.x = pos.x + PE_GAME->window->camera_offset.x;
			pos.y = pos.y + PE_GAME->window->camera_offset.y;

			// create vertecies
			float vertecies[] =
			{
				ScreenCordsToGLCords(pos.x, screenWidth), -ScreenCordsToGLCords(pos.y, screenHeight),
				ScreenCordsToGLCords(pos.x + size.x, screenWidth), -ScreenCordsToGLCords(pos.y, screenHeight),
				ScreenCordsToGLCords(pos.x + size.x, screenWidth), -ScreenCordsToGLCords(pos.y + size.y, screenHeight),
				ScreenCordsToGLCords(pos.x, screenWidth), -ScreenCordsToGLCords(pos.y + size.y, screenHeight),
			};

			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), &vertecies, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
			glEnableVertexAttribArray(0);

			unsigned int indicies[] =
			{
				2, 3, 0,
				0, 1, 2
			};

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_DYNAMIC_DRAW);

			glUniform4f(glGetUniformLocation(currentShader, "u_color"), float(color.r) / 255, float(color.g) / 255, float(color.b) / 255, float(color.a) / 255);

			glDrawElements(
				GL_TRIANGLES,      // mode
				6,    // count
				GL_UNSIGNED_INT,   // type
				nullptr           // element array buffer offset
			);
		}

		void GLRenderer::DrawQuadTextured(Vector pos, Vector size, Texture* tex, Utils::Color color)
		{
			int screenWidth = window->GetWidth();
			int screenHeight = window->GetHeight();

			glUniform1i(glGetUniformLocation(currentShader, "u_textured"), 1);

			tex->Bind(1);

			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

			pos.x = pos.x + PE_GAME->window->camera_offset.x;
			pos.y = pos.y + PE_GAME->window->camera_offset.y;

			// create vertecies
			float vertecies[] =
			{
				ScreenCordsToGLCords(pos.x, screenWidth), -ScreenCordsToGLCords(pos.y, screenHeight), 0.0, 0.0,
				ScreenCordsToGLCords(pos.x + size.x, screenWidth), -ScreenCordsToGLCords(pos.y, screenHeight), 1.0, 0.0,
				ScreenCordsToGLCords(pos.x + size.y, screenWidth), -ScreenCordsToGLCords(pos.y + size.y, screenHeight), 1.0, 1.0,
				ScreenCordsToGLCords(pos.x, screenWidth), -ScreenCordsToGLCords(pos.y + size.y, screenHeight), 0.0, 1.0
			};

			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), &vertecies, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
			glEnableVertexAttribArray(1);

			unsigned int indicies[] =
			{
				2, 3, 0,
				0, 1, 2
			};

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_DYNAMIC_DRAW);

			glUniform4f(glGetUniformLocation(currentShader, "u_color"), float(color.r) / 255, float(color.g) / 255, float(color.b) / 255, float(color.a) / 255);
			glUniform1i(glGetUniformLocation(currentShader, "u_texture"), 1);

			glDrawElements(
				GL_TRIANGLES,      // mode
				6,    // count
				GL_UNSIGNED_INT,   // type
				nullptr           // element array buffer offset
			);

			tex->Unbind();
		}
	}
}
