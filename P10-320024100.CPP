/*
Previo10
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;


Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;


Model BigGear;
Model CentralGearBig;
Model CentralGearSmall;
Model Gear1;
Model Gear2;
Model MarcoReloj;
Model M_Minutero;
Model M_Horaria;


Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

//INPUT DE KEYFRAMES
void inputKeyframes(bool* keys);
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

// Variables para el control de archivos
float guardoArchivo = 0, reinicioGuardarArchivo = 0;
float cargoArchivo = 0, reinicioCargarArchivo = 0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";



//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};
	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};
	


	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}




///////////////////////////////KEYFRAMES/////////////////////


bool animacion = false;



//NEW// Keyframes
float giroBigGear = 0;
float giroCentralGearBig = 0;
float giroCentralGearSmall = 0;
float giroGear1 = 0;
float giroGear2 = 0;
float giroMinutero = 0;
float giroHoraria = 0;

#define MAX_FRAMES 100
int i_max_steps = 90;
int i_curr_steps = 6;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float giroBigGear;
	float giroCentralGearBig;
	float giroCentralGearSmall;
	float giroGear1;
	float giroGear2;
	float giroMinutero;
	float giroHoraria;

	float giroBigGearInc;
	float giroCentralGearBigInc;
	float giroCentralGearSmallInc;
	float giroGear1Inc;
	float giroGear2Inc;
	float giroMinuteroInc;
	float giroHorariaInc;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 6;			//introducir datos
bool play = false;
int playIndex = 0;

void resetElements(void) //Tecla 0
{
	giroBigGear = KeyFrame[0].giroBigGear;
	giroCentralGearBig = KeyFrame[0].giroCentralGearBig;
	giroCentralGearSmall = KeyFrame[0].giroCentralGearSmall;
	giroGear1 = KeyFrame[0].giroGear1;
	giroGear2 = KeyFrame[0].giroGear2;
	giroMinutero = KeyFrame[0].giroMinutero;
	giroHoraria = KeyFrame[0].giroHoraria;
}

void saveFrame(void) //tecla L
{
	printf("frameindex %d\n", FrameIndex);
	KeyFrame[FrameIndex].giroBigGear = giroBigGear;
	KeyFrame[FrameIndex].giroCentralGearBig = giroCentralGearBig;
	KeyFrame[FrameIndex].giroCentralGearSmall = giroCentralGearSmall;
	KeyFrame[FrameIndex].giroGear1 = giroGear1;
	KeyFrame[FrameIndex].giroGear2 = giroGear2;
	KeyFrame[FrameIndex].giroMinutero = giroMinutero;
	KeyFrame[FrameIndex].giroHoraria = giroHoraria;

	FrameIndex++;
}

// Función para guardar los frames actuales en un archivo de texto
void guardarKeyframesArchivo()
{
	std::ofstream archivo("keyframesReloj.txt");
	if (archivo.is_open())
	{
		// Guardamos cantidad total de frames
		archivo << FrameIndex << "\n";

		// Iteramos a lo largo de la cantidad para guardar las variables de cada frame
		for (int i = 0; i < FrameIndex; i++)
		{
			archivo << KeyFrame[i].giroBigGear << " "
				<< KeyFrame[i].giroCentralGearBig << " "
				<< KeyFrame[i].giroCentralGearSmall << " "
				<< KeyFrame[i].giroGear1 << " "
				<< KeyFrame[i].giroGear2 << " "
				<< KeyFrame[i].giroMinutero << " "
				<< KeyFrame[i].giroHoraria << "\n";
		}
		archivo.close();
		printf("=== Keyframes guardados exitosamente en 'keyframesReloj.txt' ===\n");
	}
	else
	{
		printf("Error al abrir el archivo para guardar.\n");
	}
}

// Función para leer los frames desde un archivo de texto
void cargarKeyframesArchivo()
{
	std::ifstream archivo("keyframes.txt");
	if (archivo.is_open())
	{
		// leemos la cantidad de frames guardados
		archivo >> FrameIndex;

		// llenamos el arreglo con los datos del archivo
		for (int i = 0; i < FrameIndex; i++)
		{
			archivo >> KeyFrame[i].giroBigGear
				>> KeyFrame[i].giroCentralGearBig
				>> KeyFrame[i].giroCentralGearSmall
				>> KeyFrame[i].giroGear1
				>> KeyFrame[i].giroGear2
				>> KeyFrame[i].giroMinutero
				>> KeyFrame[i].giroHoraria;
		}
		archivo.close();
		printf("=== Keyframes cargados exitosamente. Total frames: %d ===\n", FrameIndex);

		// reseteamos las posiciones a las del primer frame cargado
		resetElements();
	}
	else
	{
		printf("Error al abrir el archivo. Asegurate de haber guardado antes.\n");
	}
}

void interpolation(void)
{
	KeyFrame[playIndex].giroBigGearInc = (KeyFrame[playIndex + 1].giroBigGear - KeyFrame[playIndex].giroBigGear) / i_max_steps;
	KeyFrame[playIndex].giroCentralGearBigInc = (KeyFrame[playIndex + 1].giroCentralGearBig - KeyFrame[playIndex].giroCentralGearBig) / i_max_steps;
	KeyFrame[playIndex].giroCentralGearSmallInc = (KeyFrame[playIndex + 1].giroCentralGearSmall - KeyFrame[playIndex].giroCentralGearSmall) / i_max_steps;
	KeyFrame[playIndex].giroGear1Inc = (KeyFrame[playIndex + 1].giroGear1 - KeyFrame[playIndex].giroGear1) / i_max_steps;
	KeyFrame[playIndex].giroGear2Inc = (KeyFrame[playIndex + 1].giroGear2 - KeyFrame[playIndex].giroGear2) / i_max_steps;
	KeyFrame[playIndex].giroMinuteroInc = (KeyFrame[playIndex + 1].giroMinutero - KeyFrame[playIndex].giroMinutero) / i_max_steps;
	KeyFrame[playIndex].giroHorariaInc = (KeyFrame[playIndex + 1].giroHoraria - KeyFrame[playIndex].giroHoraria) / i_max_steps;
}


void animate(void)
{
	//Movimiento del objeto // barra espaciadora
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("Frame index= %d\n", FrameIndex);
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				//printf("entro aquí\n");
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//printf("se quedó aqui\n");
			//printf("max steps: %f", i_max_steps);
			//Draw animation

			giroBigGear += KeyFrame[FrameIndex].giroBigGearInc;
			giroCentralGearBig += KeyFrame[FrameIndex].giroCentralGearBigInc;
			giroCentralGearSmall += KeyFrame[FrameIndex].giroCentralGearSmallInc;
			giroGear1 += KeyFrame[FrameIndex].giroGear1Inc;
			giroGear2 += KeyFrame[FrameIndex].giroGear2Inc;
			giroMinutero += KeyFrame[FrameIndex].giroMinuteroInc;
			giroHoraria += KeyFrame[FrameIndex].giroHorariaInc;

			i_curr_steps++;
		}

	}
}

///////////////* FIN KEYFRAMES*////////////////////////////


int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	


	BigGear = Model();
	BigGear.LoadModel("Models/BigGear.obj");
	CentralGearBig = Model();
	CentralGearBig.LoadModel("Models/CentralGearBig.obj");
	CentralGearSmall = Model();
	CentralGearSmall.LoadModel("Models/CentralGearSmall.obj");
	Gear1 = Model();
	Gear1.LoadModel("Models/Gear1.obj");
	Gear2 = Model();
	Gear2.LoadModel("Models/Gear2.obj");
	MarcoReloj = Model();
	MarcoReloj.LoadModel("Models/MarcoReloj.obj");
	M_Minutero = Model();
	M_Minutero.LoadModel("Models/M_Mnutero.obj");
	M_Horaria = Model();
	M_Horaria.LoadModel("Models/M_Horaria.obj");




	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 2.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;



	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset=0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	
	

	glm::vec3 lowerLight(0.0f, 0.0f, 0.0f);

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec2 toffset = glm::vec2(0.0f, 0.0f);


	printf("\nTeclas para uso de Keyframes:\n"
		"1.-Presionar barra espaciadora para reproducir animacion.\n"
		"2.-Presionar 0 para volver a habilitar reproduccion\n"
		"3.-Presiona L para guardar frame en memoria\n"
		"4.-Presiona P para habilitar guardar nuevo frame\n"
		"5.-Presiona G para GUARDAR frames en archivo (.txt)\n"
		"6.-Presiona H para habilitar guardar en archivo nuevamente\n"
		"7.-Presiona J para CARGAR frames desde archivo (.txt)\n"
		"8.-Presiona K para habilitar cargar archivo nuevamente\n"
		"=== CONTROLES DEL RELOJ ===\n"
		"[1]\n"
		"[2]\n"
		"[3]\n"
		"[4]\n"
		"[5]\n"
		"[6]\n"
		"[7]\n"
		"[8] Desbloquear movimientos (Habilita volver a usar 1,2,3,4,5)\n\n");
	
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//angulovaria += 0.5f*deltaTime;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);


		//reiniciar variables antes de que sean enviadas al shader

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		toffset = glm::vec2(0.0f, 0.0f); 
		
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();



		//MODELOS DEL RELOJ
		// Marco Reloj (Estático)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 2.0f, -4.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MarcoReloj.RenderModel();

		// BigGear
		model = modelaux;
		model = glm::rotate(model, glm::radians(0.2f*mainWindow.getengranemovadicionalBigGear()), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BigGear.RenderModel();

		// CentralGearBig
		model = modelaux;
		model = glm::rotate(model, glm::radians(0.5f * mainWindow.getengranemovadicionalCentralGearBig()), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CentralGearBig.RenderModel();

		// CentralGearSmall
		model = modelaux;
		model = glm::rotate(model, glm::radians(6.0f * mainWindow.getengranemovadicionalCentralGearSmall()), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CentralGearSmall.RenderModel();

		// Gear1
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.3f, 0.9f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getengranemovadicionalGear1()), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Gear1.RenderModel();

		// Gear2
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.4f, 0.9f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getengranemovadicionalGear2()), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Gear2.RenderModel();

		// Minutero (M_Minutero)
		model = modelaux;
		model = glm::rotate(model, glm::radians(6.0f*mainWindow.getobjetomovadicionalM_Minutero()), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		M_Minutero.RenderModel();

		// Horaria (M_Horaria)
		model = modelaux;
		model = glm::rotate(model, glm::radians(0.5f*mainWindow.getobjetomovadicionalM_Horaria()), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		M_Horaria.RenderModel();

		

		

		//Modelos con blending al final para que no afecten a los demás objetos, aunque también se pueden renderizar al inicio pero con blending  activado y desactivado
		
		//blending: transparencia o traslucidez
		/*
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Agave ¿qué sucede si lo renderizan antes del coche y de la pista?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -2.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		glDisable(GL_BLEND);
		*/

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
