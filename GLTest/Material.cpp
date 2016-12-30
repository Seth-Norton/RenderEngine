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


char* Material::textFileRead(const GLchar* filePath) {
	FILE* filePointer;
	char* content = NULL;

	int count = 0;

	if (filePath != NULL) {
		filePointer = fopen(filePath, "rt");

		if (filePointer != NULL) {

			fseek(filePointer, 0, SEEK_END);
			count = ftell(filePointer);
			rewind(filePointer);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count + 1));
				count = fread(content, sizeof(char), count, filePointer);
				content[count] = '\0';
			}
			fclose(filePointer);
		}
	}
	return content;
}






bool Material::loadSources(GLchar** vertexSource, GLchar** fragSource) {
	printf("Loading %p and %p\n", *vertexSource, *fragSource);

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
	GLchar* vertexSource[] =	
	{
		"#version 330\nin vec4 vPosition; void main() { gl_Position = vPosition; }"
	};

	GLchar* fragSource[] =
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





bool Material::loadProgram(const GLchar * vertexFilepath, const GLchar * fragFilepath)
{
	GLchar* vertexSource = textFileRead(vertexFilepath);
	GLchar* fragSource = textFileRead(fragFilepath);

	bool success = loadSources(&vertexSource, &fragSource);
	if (success) {
		printf("Successfully loaded %s, %s\n", vertexFilepath, fragFilepath);
		return true;
	}
	else {
		printf("Error: Failed to load %s or %s\n", vertexFilepath, fragFilepath);
		return false;
	}
}










