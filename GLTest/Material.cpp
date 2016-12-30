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






bool Material::loadSources(const GLchar** vertexSource, const GLchar** fragSource) {
	this->program = glCreateProgram();

	//	Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	

	glShaderSource(vertexShader, 1, vertexSource, NULL);
	glCompileShader(vertexShader);
	GLint shaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE)
	{
		printf("Unable to compile vertex shader %d!\n", vertexShader);
		printShaderLog(vertexShader);
		return false;
	}



	//	Fragment Shader
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	

	glShaderSource(fragShader, 1, fragSource, NULL);
	glCompileShader(fragShader);

	shaderCompiled = GL_FALSE;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE) {
		printf("Unable to compile fragment shader %d!\n", fragShader);
		printShaderLog(fragShader);
		return false;
	}





	//	Link Program
	glAttachShader(this->program, vertexShader);
	glAttachShader(this->program, fragShader);

	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_LINK_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE)
	{
		printf("Error linking program %d!\n", this->program);
		printProgramLog(this->program);
		return false;
	}

	glUseProgram(this->program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	return true;
}





bool Material::loadDefault() {
	const GLchar* vertexSource[] =	
	{
		"#version 330\nin vec4 vPosition; void main() { gl_Position = vPosition; }"
	};

	const GLchar* fragSource[] =
	{
		"#version 330\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 0.5, 0.2, 1.0 ); }"
	};

	bool success = loadSources(vertexSource, fragSource);
	if (success) {
		printf("Successfully loaded default shaders\n");
		return true;
	}
	else {
		printf("Error: Failed to load default shaders\n");
		return false;
	}
}





bool Material::loadProgram(const char * vertexFilepath, const char * fragFilepath)
{
	bool success = false;

	//	TODO: Load from text files
	
	if (success) {
		printf("Successfully loaded %s, %s\n", vertexFilepath, fragFilepath);
		return true;
	}
	else {
		printf("Error: Failed to load %s or %s\n", vertexFilepath, fragFilepath);
		return false;
	}
}










