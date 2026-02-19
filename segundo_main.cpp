#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>

//Librerías para generar números aleatorios
#include <stdlib.h> // Para rand() y srand()
#include <time.h>   // Para time()

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 800;
GLuint VAO, VBO, shader;

//LENGUAJE DE SHADER (SOMBRAS) GLSL
//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";

//Fragment Shader
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(1.0f,0.0f,1.0f,1.0f);	 			\n\
}";


void CrearFiguras()
{
	GLfloat vertices[] = {
		// LETRA J
		//Parte inferior
		-0.75f, -0.9f, 0.0f,
		-0.69f, -0.9f, 0.0f,
		-0.75f, -0.84f, 0.0f,
		-0.69f, -0.9f, 0.0f,
		-0.69f, -0.84f, 0.0f,
		-0.75f, -0.84f, 0.0f,
		//Curva
		-0.69f, -0.9f, 0.0f,
		-0.67f, -0.9f, 0.0f,
		-0.69f, -0.84f, 0.0f,
		-0.69f, -0.84f, 0.0f,
		-0.67f, -0.9f, 0.0f,
		-0.66f, -0.825f, 0.0f,
		-0.67f, -0.9f, 0.0f,
		-0.66f, -0.825f, 0.0f,
		-0.61875f, -0.8781f, 0.0f,
		-0.66f, -0.825f, 0.0f,
		-0.61875f, -0.8781f, 0.0f,
		-0.63f, -0.8f, 0.0f,
		-0.61875f, -0.8781f, 0.0f,
		-0.63f, -0.8f, 0.0f,
		-0.567f, -0.8125f, 0.0f,
		-0.63f, -0.8f, 0.0f,
		-0.567f, -0.8125f, 0.0f,
		-0.62, -0.75, 0.0f,
		-0.567f, -0.8125f, 0.0f,
		-0.62, -0.75, 0.0f,
		-0.55, -0.75, 0.0f,
		//Parte superior
		-0.62, -0.75, 0.0f,
		-0.55, -0.75, 0.0f,
		-0.62, -0.35, 0.0f,
		-0.55, -0.75, 0.0f,
		-0.55, -0.35, 0.0f,
		-0.62, -0.35, 0.0f,
		// LETRA A
		//Pata izquierda
		-0.24f, -0.275f, 0.0f,
		-0.165f, -0.275f, 0.0f,
		-0.04f, 0.275f, 0.0f,
		-0.165f, -0.275f, 0.0f,
		0.04f, 0.275f, 0.0f,
		-0.04f, 0.275f, 0.0f,
		//Pata derecha
		0.24f, -0.275f, 0.0f,
		0.165f, -0.275f, 0.0f,
		0.04f, 0.275f, 0.0f,
		0.165f, -0.275f, 0.0f,
		-0.04f, 0.275f, 0.0f,
		0.04f, 0.275f, 0.0f,
		//Palo central
		-0.115f, -0.125f, 0.0f,
		-0.095f, -0.06f, 0.0f,
		0.095f, -0.06f, 0.0f,
		0.115f, -0.125f, 0.0f,
		0.095f, -0.06f, 0.0f,
		-0.115f, -0.125f, 0.0f,
		// LETRA R
		0.5f, 0.9f, 0.0f,
		0.5f, 0.37f, 0.0f,
		0.57f, 0.9f, 0.0f,
		0.5f, 0.37f, 0.0f,
		0.57f, 0.37f, 0.0f,
		0.57f, 0.9f, 0.0f,
		0.57f, 0.9f, 0.0f,
		0.75f, 0.9f, 0.0f,
		0.57f, 0.84f, 0.0f,
		0.75f, 0.84f, 0.0f,
		0.75f, 0.9f, 0.0f,
		0.57f, 0.84f, 0.0f,
		0.57f, 0.595f, 0.0f,
		0.57f, 0.65f, 0.0f,
		0.72f, 0.595f, 0.0f,
		0.57f, 0.65f, 0.0f,
		0.72f, 0.595f, 0.0f,
		0.72f, 0.65f, 0.0f,
		0.9f, 0.37f, 0.0f,
		0.83f, 0.37f, 0.0f,
		0.85f, 0.57f, 0.0f,
		0.78f, 0.57f, 0.0f,
		0.85f, 0.57f, 0.0f,
		0.83f, 0.37f, 0.0f,
		0.81f, 0.6225f, 0.0f,
		0.72f, 0.595f, 0.0f,
		0.72f, 0.65f, 0.0f,
		0.81f, 0.6225f, 0.0f,
		0.72f, 0.595f, 0.0f,
		0.78f, 0.57f, 0.0f,
		0.81f, 0.6225f, 0.0f,
		0.85f, 0.57f, 0.0f,
		0.78f, 0.57f, 0.0f,
		0.75f, 0.9f, 0.0f,
		0.75f, 0.84f, 0.0f,
		0.8f, 0.745f, 0.0f,
		0.86f, 0.745f, 0.0f,
		0.8f, 0.745f, 0.0f,
		0.75f, 0.9f, 0.0f,
		0.86f, 0.745f, 0.0f,
		0.8f, 0.745f, 0.0f,
		0.72f, 0.65f, 0.0f,
		0.78f, 0.57f, 0.0f,
		0.72f, 0.65f, 0.0f,
		0.86f, 0.745f, 0.0f

	};
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
	glEnableVertexAttribArray(0);
	//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica

//the Program recibe los datos de theShader

{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader, 1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n", shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader = glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	//verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}



}
int main()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}

	//****  LAS SIGUIENTES 4 LÍNEAS SE COMENTAN EN DADO CASO DE QUE AL USUARIO NO LE FUNCIONE LA VENTANA Y PUEDA CONOCER LA VERSIÓN DE OPENGL QUE TIENE ****/

	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

	//Llamada a las funciones creadas antes del main
	CrearFiguras();
	CompileShaders();

	// Variables para la frecuencia
	double lastTime = glfwGetTime();	// El último cambio hecho iniciará con el tiempo inicial
	float flashSpeed = 3.0f;			// Velocidad de cambio (3 segundos por color en este caso)


	// Inicializar la semilla aleatoria basada en el tiempo actual
	srand(time(NULL));
	// Variables para almacenar el color actual (R, G, B)
	float currR = (float)rand() / (float)RAND_MAX;
	float currG = (float)rand() / (float)RAND_MAX;
	float currB = (float)rand() / (float)RAND_MAX;


	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow)) {
		glfwPollEvents();  //Recibir eventos del usuario
		double currentTime = glfwGetTime(); // Obtener tiempo actual
		// Si han pasado dos segundos
		if (currentTime - lastTime >= flashSpeed) {
			//Generar nuevos colores
			currR = (float)rand() / (float)RAND_MAX;
			currG = (float)rand() / (float)RAND_MAX;
			currB = (float)rand() / (float)RAND_MAX;
			lastTime = currentTime; // Se reinicia el contador de tiempo
		}
		// Aplicar color aleatorio
		glClearColor(currR, currG, currB, 1.0f);
		//Limpiar la ventana
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 102);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);

		//NO ESCRIBIR NINGUNA LÍNEA DESPUÉS DE glfwSwapBuffers(mainWindow); 
	}


	return 0;
}