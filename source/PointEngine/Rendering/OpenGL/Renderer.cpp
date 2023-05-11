#include "Renderer.h"

#include <gl/glew.h>

#include <iostream>
#include <fstream>
#include <string>

#include "Error.h"

unsigned int GLRenderer::CompileShader(std::string path, unsigned int shaderType)
{
	std::ifstream file_stream(path);

	std::string line;
	std::string shader_contents;
	
	while (std::getline(file_stream, line))
	{
		std::cout << line << std::endl;
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

GLRenderer::GLRenderer(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

double GLRenderer::ScreenCordsToGLCords(double pos, int size)
{
	//std::cout << pos << " | " << size << " - " << (pos / size) * 2 - 1 << std::endl;

	return ((pos / size) * 2) - 1;
}

void GLRenderer::Clear(Color color)
{
	glClearColor(float(color.r) / 255, float(color.g) / 255, float(color.b) / 255, float(color.a / 255));
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLRenderer::DrawQuad(double posX, double posY, double sizeX, double sizeY, Color color)
{
	glUniform1i(glGetUniformLocation(currentShader, "u_textured"), 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// create vertecies
	float vertecies[] =
	{
		ScreenCordsToGLCords(posX, screenWidth), -ScreenCordsToGLCords(posY, screenHeight),
		ScreenCordsToGLCords(posX + sizeX, screenWidth), -ScreenCordsToGLCords(posY, screenHeight),
		ScreenCordsToGLCords(posX + sizeX, screenWidth), -ScreenCordsToGLCords(posY + sizeY, screenHeight),
		ScreenCordsToGLCords(posX, screenWidth), -ScreenCordsToGLCords(posY + sizeY, screenHeight),
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

void GLRenderer::DrawQuadTextured(double posX, double posY, Texture* tex, Color color, double scaleX, double scaleY)
{
	glUniform1i(glGetUniformLocation(currentShader, "u_textured"), 1);

	tex->Bind(1);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	double sizeX = tex->GetWidth() * scaleX;
	double sizeY = tex->GetHeight() * scaleY;

	// create vertecies
	float vertecies[] =
	{
		ScreenCordsToGLCords(posX, screenWidth), -ScreenCordsToGLCords(posY, screenHeight), 0.0, 0.0,
		ScreenCordsToGLCords(posX + sizeX, screenWidth), -ScreenCordsToGLCords(posY, screenHeight), 1.0, 0.0,
		ScreenCordsToGLCords(posX + sizeX, screenWidth), -ScreenCordsToGLCords(posY + sizeY, screenHeight), 1.0, 1.0,
		ScreenCordsToGLCords(posX, screenWidth), -ScreenCordsToGLCords(posY + sizeY, screenHeight), 0.0, 1.0
	};

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), &vertecies, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) ( 2 * sizeof(float)) );
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

	/*
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "[OPENGL ERROR] " << error << std::endl;
	}
	*/
}