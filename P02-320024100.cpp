//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders_editado/shader.vert";
static const char* fShader = "shaders_editado/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	// Son 12 vértices
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	// Son 24 vértices
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letraJ[] = {
		//X			Y			Z			R		G		B
		//Parte inferior
		-0.75f,		-0.9f,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.69f,		-0.9f,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.75f,		-0.84f,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.69f,		-0.9f,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.69f,		-0.84f,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.75f,		-0.84f,		-1.0f,		0.0f,	0.0f,	1.0f,
		//Curva
		-0.69f,		-0.9f,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.67f,		-0.9f,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.69f,		-0.84f,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.69f,		-0.84f,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.67f,		-0.9f,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.66f,		-0.825f,	-1.0f,		0.0f,	0.0f,	1.0f,
		-0.67f,		-0.9f,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.66f,		-0.825f,	-1.0f,		0.0f,	0.0f,	1.0f,
		-0.61875f,	-0.8781f,	-1.0f,		0.0f,	0.0f,	1.0f,
		-0.66f,		-0.825f,	-1.0f,		0.0f,	0.0f,	1.0f,
		-0.61875f,	-0.8781f,	-1.0f,		0.0f,	0.0f,	1.0f,
		-0.63f,		-0.8f,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.61875f,	-0.8781f,	-1.0f,		0.0f,	0.0f,	1.0f,
		-0.63f,		-0.8f,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.567f,	-0.8125f,	-1.0f,		0.0f,	0.0f,	1.0f,
		-0.63f,		-0.8f,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.567f,	-0.8125f,	-1.0f,		0.0f,	0.0f,	1.0f,
		-0.62,		-0.75,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.567f,	-0.8125f,	-1.0f,		0.0f,	0.0f,	1.0f,
		-0.62,		-0.75,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.55,		-0.75,		-1.0f,		0.0f,	0.0f,	1.0f,
		//Parte superior
		-0.62,		-0.75,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.55,		-0.75,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.62,		-0.35,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.55,		-0.75,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.55,		-0.35,		-1.0f,		0.0f,	0.0f,	1.0f,
		-0.62,		-0.35,		-1.0f,		0.0f,	0.0f,	1.0f,
	};
	MeshColor* letraJ = new MeshColor();
	letraJ->CreateMeshColor(vertices_letraJ, 198);
	meshColorList.push_back(letraJ);


	GLfloat vertices_letraA[] = {
		//X			Y			Z			R		G		B
		//Pata izquierda
		-0.24f,		-0.275f,	-1.0f,		1.0f,	0.0f,	1.0f,
		-0.165f,	-0.275f,	-1.0f,		1.0f,	0.0f,	1.0f,
		-0.04f,		0.275f,		-1.0f,		1.0f,	0.0f,	1.0f,
		-0.165f,	-0.275f,	-1.0f,		1.0f,	0.0f,	1.0f,
		0.04f,		0.275f,		-1.0f,		1.0f,	0.0f,	1.0f,
		-0.04f,		0.275f,		-1.0f,		1.0f,	0.0f,	1.0f,
		//Pata derecha
		0.24f,		-0.275f,	-1.0f,		1.0f,	0.0f,	1.0f,
		0.165f,		-0.275f,	-1.0f,		1.0f,	0.0f,	1.0f,
		0.04f,		0.275f,		-1.0f,		1.0f,	0.0f,	1.0f,
		0.165f,		-0.275f,	-1.0f,		1.0f,	0.0f,	1.0f,
		-0.04f,		0.275f,		-1.0f,		1.0f,	0.0f,	1.0f,
		0.04f,		0.275f,		-1.0f,		1.0f,	0.0f,	1.0f,
		//Palo central
		-0.115f,	-0.125f,	-1.0f,		1.0f,	0.0f,	1.0f,
		-0.095f,	-0.06f,		-1.0f,		1.0f,	0.0f,	1.0f,
		0.095f,		-0.06f,		-1.0f,		1.0f,	0.0f,	1.0f,
		0.115f,		-0.125f,	-1.0f,		1.0f,	0.0f,	1.0f,
		0.095f,		-0.06f,		-1.0f,		1.0f,	0.0f,	1.0f,
		-0.115f,	-0.125f,	-1.0f,		1.0f,	0.0f,	1.0f,
	};
	MeshColor* letraA = new MeshColor();
	letraA->CreateMeshColor(vertices_letraA, 108);
	meshColorList.push_back(letraA);


	GLfloat vertices_letraR[] = {
		//X			Y			Z			R		G		B
		0.5f,		0.9f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.5f,		0.37f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.57f,		0.9f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.5f,		0.37f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.57f,		0.37f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.57f,		0.9f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.57f,		0.9f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.75f,		0.9f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.57f,		0.84f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.75f,		0.84f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.75f,		0.9f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.57f,		0.84f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.57f,		0.595f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.57f,		0.65f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.72f,		0.595f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.57f,		0.65f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.72f,		0.595f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.72f,		0.65f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.9f,		0.37f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.83f,		0.37f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.85f,		0.57f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.78f,		0.57f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.85f,		0.57f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.83f,		0.37f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.81f,		0.6225f,	-1.0f,		0.0f,	1.0f,	1.0f,
		0.72f,		0.595f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.72f,		0.65f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.81f,		0.6225f,	-1.0f,		0.0f,	1.0f,	1.0f,
		0.72f,		0.595f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.78f,		0.57f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.81f,		0.6225f,	-1.0f,		0.0f,	1.0f,	1.0f,
		0.85f,		0.57f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.78f,		0.57f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.75f,		0.9f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.75f,		0.84f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.8f,		0.745f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.86f,		0.745f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.8f,		0.745f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.75f,		0.9f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.86f,		0.745f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.8f,		0.745f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.72f,		0.65f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.78f,		0.57f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.72f,		0.65f,		-1.0f,		0.0f,	1.0f,	1.0f,
		0.86f,		0.745f,		-1.0f,		0.0f,	1.0f,	1.0f,
	};
	MeshColor* letraR = new MeshColor();
	letraR->CreateMeshColor(vertices_letraR, 270);
	meshColorList.push_back(letraR);
}

void CreateShaders()
{
	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);
}
//===============================================================================================================
//											Ejercicio 1
//===============================================================================================================
/*
int main()
{
	mainWindow = Window(800, 800);
	mainWindow.Initialise();
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

	// Inicializamos una matriz identidad
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.08f, 0.0f)); //Se moverán todas las letras un poco hacia arriba
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();
		meshColorList[1]->RenderMeshColor();
		meshColorList[2]->RenderMeshColor();

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
*/
//===============================================================================================================
//											Ejercicio 2
//===============================================================================================================

//*
int main()
{
	mainWindow = Window(800, 800);
	mainWindow.Initialise();
	// El orden importa
	CreaPiramide(); // Tejado azul
	CreaPiramide(); // Hojas verdes de los árboles
	CreaPiramide(); // Hojas verdes de los árboles
	CrearCubo();	// Casa roja
	CrearCubo();	// Puerta verde
	CrearCubo();	// Ventana verde
	CrearCubo();	// Ventana verde
	CrearCubo();	// Tronco café
	CrearCubo();	// Tronco café
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

	// Inicializamos una matriz identidad
	glm::mat4 model(1.0);
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();


		// Obtenemos el ID del programa de shader que "useShader()" acaba de activar
		GLint currentProgram;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
		// Buscamos la ubicación de nuestro nuevo uniform "objectColor"
		GLuint uniformColor = glGetUniformLocation(currentProgram, "objectColor");

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		// Tejado azul
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.2f, 0.6f, 1.2f));
		model = glm::translate(model, glm::vec3(0.0f, 1.166f, -5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(uniformColor, 0.0f, 0.0f, 1.0f); // Enviar color al shader antes de dibujar
		meshList[0]->RenderMesh();

		// Hojas verdes de los árboles
		glUniform3f(uniformColor, 0.0f, 0.5f, 0.0f); // Enviar color al shader antes de dibujar
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.4f, 0.5f, 0.4f));
		model = glm::translate(model, glm::vec3(-2.0f, -0.3f, -12.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.4f, 0.5f, 0.4f));
		model = glm::translate(model, glm::vec3(2.0f, -0.3f, -12.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[2]->RenderMesh();

		// Casa roja
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.1f, -6.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(uniformColor, 1.0f, 0.0f, 0.0f); // Enviar color al shader antes de dibujar
		meshList[3]->RenderMesh();

		// Puerta y ventanas verdes
		glUniform3f(uniformColor, 0.0f,	1.0f,	0.0f); // Enviar color al shader antes de dibujar
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, -18.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[4]->RenderMesh();
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(-0.75f, 0.5f, -18.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[5]->RenderMesh();
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(0.75f, 0.5f, -18.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[6]->RenderMesh();

		// Troncos cafés
		glUniform3f(uniformColor, 0.478f, 0.255f, 0.067f); // Enviar color al shader antes de dibujar
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(4.0f, -2.5f, -17.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[7]->RenderMesh();
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(-4.0f, -2.5f, -17.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[8]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}
//*/