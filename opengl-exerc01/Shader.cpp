
#include <GL/glew.h> //GLEW
#include <fstream>
#include <iostream>
#include "Shader.h"


Shader::Shader(){
	
}

bool Shader::deleteProgram(GLuint ID){
	if(ID){
		glDeleteProgram( ID );
		return true;
	}
	else
		return false;
		
}

GLuint Shader::createProgram(std::string arqVertexShader, std::string arqFragShader) 
{

	//variaveis para armazenar os ponteiros para: vextexshader, fragmentshader e programa
	GLuint vShader=0, fShader=0, program=0;

	//cria o vertex shader
	if (!Shader::createShader(GL_VERTEX_SHADER, arqVertexShader, &vShader)) {
		std::cout << "criarPrograma: Erro ao criar o vertex shader: " << arqVertexShader << " !" << std::endl;
		return false;
	}
		

	//cria o fragment shader
	if (!Shader::createShader(GL_FRAGMENT_SHADER, arqFragShader, &fShader)) {
		std::cout << "criarPrograma: Erro ao criar o fragment shader: "  << arqFragShader << " !" << std::endl;
		return false;
	}

	//cria o programa
	program = glCreateProgram();

	//anexar os shaders ao programa
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);

	//passo final, link do programa
	glLinkProgram(program);

	//verifica erros no OpenGL
	if (Shader::checkErrors())
		return false;

	//verifica erros no link do programa
	GLint linkValido;
	glGetProgramiv(program, GL_LINK_STATUS, &linkValido);
	if (!linkValido)
	{
		
		std::cout << "Erro no glLinkProgram" << std::endl;
		
		Shader::printProgramInfoLog(program);
		return false;
	}

	//libera memoria dos shaders (eles já foram compilados e anexados ao programa)
	glDetachShader(program, vShader);
	glDetachShader(program, fShader);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	//retorna o ponteiro do programa
	return program;

}

bool Shader::createShader(int type, std::string path, unsigned int* ID) {


	//le o arquivo contendo o codigo fonte do shader
	std::ifstream f(path);

	if (!f.is_open()) {
		std::cout << "Erro ao abrir o arquivo: " << path << std::endl;

		return false;
	}
	std::string strFile((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
	const char* strCode = strFile.c_str();

	//cria o shader
	GLuint shaderRef = glCreateShader(type);

	//especifica o codigo fonte do shader
	glShaderSource(shaderRef, 1, &strCode, NULL);

	//compila o shader
	glCompileShader(shaderRef);

	//verifica erros no OpenGL
	if (Shader::checkErrors())
		return false;

	//verifica erros na compilação do shader
	GLint compilou;
	glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &compilou);
	if (!compilou)
	{
		std::cout << "Errou ao compilar o shader do tipo " << type << std::endl;
		Shader::printShaderInfoLog(shaderRef);
		return false;

	}

	//retorna a referencia do shader
	*ID = shaderRef;
	return true;
}





bool Shader::checkErrors() {
	bool er = false;
	int erros = glGetError();
	while (erros != GL_NO_ERROR) {
		std::cout << "glError: " << erros << std::endl;
		erros = glGetError();

		er = true;
	}

	return er;

}

void Shader::printProgramInfoLog(unsigned int progama) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(progama, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetProgramInfoLog(progama, len, &chWrittn, log);
		
		std::cout << "ProgramInfoLog: " << log << std::endl;
		free(log);
	}
}


void Shader::printShaderInfoLog(unsigned int shaderRef) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shaderRef, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetShaderInfoLog(shaderRef, len, &chWrittn, log);
		
		std::cout << "ShaderInfoLog: " << log << std::endl;

		free(log);
	}
}


std::string Shader::shaderProcessorVersion(int glslMajorVersion, int glslMinorVersion){
	if(glslMajorVersion==2 && glslMinorVersion==0)
		return std::string("#version 110");
	if(glslMajorVersion==2 && glslMinorVersion==1)
		return std::string("#version 120");
	if(glslMajorVersion==3 && glslMinorVersion==0)
		return std::string("#version 130");
	if(glslMajorVersion==3 && glslMinorVersion==1)
		return std::string("#version 140");
	if(glslMajorVersion==3 && glslMinorVersion==2)
		return std::string("#version 150");
	if(glslMajorVersion==3 && glslMinorVersion==3)
		return std::string("#version 330");
	if(glslMajorVersion==4 && glslMinorVersion==0)
		return std::string("#version 400");
	if(glslMajorVersion==4 && glslMinorVersion==1)
		return std::string("#version 410");
	if(glslMajorVersion==4 && glslMinorVersion==2)
		return std::string("#version 420");
	if(glslMajorVersion==4 && glslMinorVersion==3)
		return std::string("#version 430");
	if(glslMajorVersion==4 && glslMinorVersion==4)
		return std::string("#version 440");
	if(glslMajorVersion==4 && glslMinorVersion==5)
		return std::string("#version 450");
	if(glslMajorVersion==4 && glslMinorVersion==6)
		return std::string("#version 460");

	return std::string("");
}



