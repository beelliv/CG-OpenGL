#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

//metadado associado aos atributos dos vértices (coordendas que definem a posicao dos vértices, coordenadas de textura, cor de cada vértice, etc)
//Para configurar os atributos dos vértices, cada variável de entrada no vertexshader está associada ao metadado "location"
#define VERTEX_ATTRIB_POS 0 //no vertexshader, a variável de entrada que define a posição do vértice possui "layout (location=0)" 
#define VERTEX_ATTRIB_COLOR 1 //no vertexshader, layout (location=1)" 
#include <vector>
using namespace std;

#include <Eigen/Dense>
using namespace Eigen;

#include <GL/glew.h> //GLEW

class Object
{
public:
    
    //---------ATRIBUTOS---------
    GLuint VAO;
	GLuint VBO_POS;
	size_t nVertices;
    GLuint VBO_COLOR;


    //---------METODOS---------
	Object()  //construtor,  inicializa os atributos da classe
	{
		VAO = 0;
		VBO_POS = 0;
		nVertices = 0;

        VBO_COLOR = 0; 
	}

    //cria um objeto -> criar VAO e VBOs, carrega os dados dos atributos dos vértices na GPU
    void create(vector<Vector3f> vertexPos, vector<Vector3f> vertexColor)
    {
        
        nVertices = vertexPos.size();

        //Cria o Vertex Array Object (VAO). ELe vai armazenar as informações dos atributos dos vértices
        glGenVertexArrays(1, &VAO); //cria um ponteiro para o VAO
        glBindVertexArray(VAO); //bind

        //-----------------
        //Para CADA atributo -> (1) criar um buffer (VBO) e carregar os dados do atributo para a memória da GPU. 
        //Em seguida, (2) definir como estes dados serão acessados no vertex shader, associando o buffer criado ao metadado "location" do vertex shader!
        //-----------------

        //-----------------
        //Atributo -> Posição do vértice
        //cria o buffer para armazenar a posição dos vértices 
        glGenBuffers(1, &VBO_POS); //cria um ponteiro para o buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO_POS); //bind 
        glBufferData(GL_ARRAY_BUFFER, vertexPos.size() * sizeof(Vector3f), &vertexPos[0], GL_STATIC_DRAW); // carra os dados para a GPU
        
        //Associa o location=0 para o atributo posição do vértice.
        glEnableVertexAttribArray(VERTEX_ATTRIB_POS);  
        glVertexAttribPointer(VERTEX_ATTRIB_POS, 3,	GL_FLOAT, GL_FALSE,	0, (void*)0);
        //-----------------

        //-----------------
        //Atributo -> Cor do vértice
        glGenBuffers(1, &VBO_COLOR); //cria um ponteiro para o buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO_COLOR); //bind 
        glBufferData(GL_ARRAY_BUFFER, vertexColor.size() * sizeof(Vector3f), &vertexColor[0], GL_STATIC_DRAW); // carra os dados para a GPU
        glEnableVertexAttribArray(VERTEX_ATTRIB_COLOR);  
        glVertexAttribPointer(VERTEX_ATTRIB_COLOR, 3,	GL_FLOAT, GL_FALSE,	0, (void*)0);
        //-----------------



        //unbind all !!
        glBindVertexArray(0); 
        glDisableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    } //fim createObject


    //renderiza um objeto
    void render()
    {
        if(!VAO || nVertices<=0)
            return;

        //Ativa o VAO e os atributos dos vértices associados a este VAO
        glBindVertexArray(VAO);

        //renderizar os triangulos
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei) nVertices);

        //desativa o VAO
        glBindVertexArray(0);

    }


    void destroy()
    {
    
		//remove buffer
        if(VBO_POS)
		    glDeleteBuffers(1, &VBO_POS);

		//remove o VAO
        if(VAO)
		    glDeleteVertexArrays(1, &VAO);

        if(VBO_COLOR)
		    glDeleteBuffers(1, &VBO_COLOR);

        VAO = 0;
		VBO_POS = 0;
		nVertices = 0;
        VBO_COLOR = 0;
	
    }
   

};

#endif