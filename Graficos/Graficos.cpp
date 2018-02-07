// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include <iostream>
using namespace std;

//Declaraci�n de ventana
GLFWwindow *window;

GLfloat red, green, blue;
GLfloat ty = 0.0f;
GLfloat tx = 0.0f;
GLfloat angulo = 0.0f;

double tiempoAnterior = 0.0f;
double velocidad = 0.1f;

void actualizar() { 
	//Aqu� esta bien para cambiar los valores
	//De las variables de mi programa!
	double tiempoActual = glfwGetTime();
	double tiempoTranscurrido = 
		tiempoActual - tiempoAnterior;
	
	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS) {
		if (ty < 1)
			ty += velocidad * tiempoTranscurrido;
	}

	int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajo == GLFW_PRESS) {
		if (ty > -1)
			ty -= velocidad * tiempoTranscurrido;
	}

	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS) {
		/*if (tx < 1)
			tx += velocidad * tiempoTranscurrido;*/

		if (angulo < 360) {
			angulo += 0.01;
		}
		else
		{
			angulo = 0;
		}
	}

	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS) {
		/*if (tx > -1)
			tx -= velocidad * tiempoTranscurrido;*/
		if (angulo < 360) {
			angulo -= 0.01;
		}
		else
		{
			angulo = 0;
		}
	}

	tiempoAnterior = tiempoActual;

}

void dibujar() {
	glPushMatrix();
	glTranslatef(tx, ty, 0.0f);
	glScalef(0.08f, 0.08f, 0.08f);
	glBegin(GL_TRIANGLES); //Inicia la rutina con un modo de dibujo
	glRotatef(angulo, 0.0f, 0.0f, 1.0f); //Afecta eje z
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(1.0, -0.5f, 0.0f);
	glEnd();//Finaliza la rutina
	glPopMatrix();
}

void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {

	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (ty < 1)
			ty += 0.05f;
	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (ty > -1)
			ty -= 0.05f;
	}

	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (tx < 1)
			tx += 0.05f;
	}

	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (tx > -1)
			tx -= 0.05f;
	}


}

int main()
{
	
	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 768;

	//Inicializaci�n de GLFW
	if (!glfwInit()) {
		//Si no se inici� bien, terminar la ejecuci�n
		exit(EXIT_FAILURE);
	}

	//Inicializar la ventana
	window = glfwCreateWindow(ancho, alto, "Graficos", NULL, NULL);
	//Verficar si se cre� bien la ventana
	if (!window) {
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecuci�n
		exit(EXIT_FAILURE);
	}

	//Establecer "window" como contexto
	glfwMakeContextCurrent(window);

	//Se trae las funciones de OpenGL Moderno
	glewExperimental = true;
	//Inicializar GLEW
	GLenum glewError = glewInit();
	//Verificar que GLEW se inicializ� bien
	if (glewError != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}



	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL: " << version << endl;


	red = green = blue = 0.0f;

	//glfwSetKeyCallback(window, key_callback);

	tiempoAnterior = glfwGetTime();

	//Ciclo de dibujo
	while (!glfwWindowShouldClose(window)) {
		//Establecer el area de render (viewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia la pantalla
		glClearColor(red, green, blue, 1);
		//Limpiar la pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//rutina de dibujo
		actualizar();
		dibujar();

		//Intercambio de buffers
		glfwSwapBuffers(window);
		//Buscar se�ales de entrada
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

