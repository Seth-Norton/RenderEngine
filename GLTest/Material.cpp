#include "Material.h"



Material::Material()
{
}


Material::~Material()
{
}

void Material::printProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
	}
}

void Material::printShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a shader\n", shader);
	}
}

bool Material::loadProgram(const char * vertexFilepath, const char * fragFilepath)
{
	bool success = true;

	GLuint program = glCreateProgram();



	//	Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* shaderSource[] =	//	TODO: Load from text file
	{
		"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
	};

	glShaderSource(vertexShader, 1, shaderSource, NULL);
	glCompileShader(vertexShader);
	GLint shaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE)
	{
		printf("Unable to compile vertex shader %d!\n", vertexShader);
		printShaderLog(vertexShader);
		success = false;
		return success;
	}
	glAttachShader(program, vertexShader);


	//	Fragment Shader
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragShaderSource[] =
	{
		"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
	};

	glShaderSource(fragShader, 1, fragShaderSource, NULL);
	glCompileShader(fragShader);

	shaderCompiled = GL_FALSE;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE) {
		printf("Unable to compile fragment shader %d!\n", fragShader);
		printShaderLog(fragShader);
		success = false;
		return success;
	}
	glAttachShader(program, fragShader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE)
	{
		printf("Error linking program %d!\n", program);
		printProgramLog(program);
		success = false;
		return success;
	}


	printf("Successfully loaded %s, %s\n", vertexFilepath, fragFilepath);

	return success;
}










