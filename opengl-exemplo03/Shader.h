#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include <string>

class Shader
{
public:
	Shader();
    static bool deleteProgram(GLuint ID);

	static GLuint createProgram(std::string arqVertexShader, std::string arqFragShader);

	static bool createShader(int type, std::string path, unsigned int* ID);

	static std::string shaderProcessorVersion(int glslMajorVersion, int glslMinorVersion);


private:
	static bool checkErrors();

	static void printProgramInfoLog(unsigned int progama);

	static void printShaderInfoLog(unsigned int shaderRef);

};

#endif
