#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <vector>
using namespace std;

//#include <Eigen/Dense>
//using namespace Eigen;

#include <GL/glew.h> //GLEW

#include "Shader.h"
#include "Object.h"

class Scene
{
public:
    
    //---------ATRIBUTOS---------  
	vector<GLuint> programs;  //uma cena pode ter mais de um programa (shaders), por isso um vetor

    //vetor de objetos
	vector<Object> objects;

    //---------METODOS---------
    Scene() //construtor,  inicializa os atributos da classe
    {
    };

    void destroy()
    {

        for(Object o: objects)
            o.destroy();
        
        //remove os shaders
        for(GLuint p: programs)
            glDeleteProgram(p);
        
        programs.clear();
        objects.clear();
    }

    void addObject(Object o)
    {
        objects.push_back(o);   
    }
    
    void addProgram(GLuint prog)
    {
        programs.push_back(prog);
    }

};

#endif