#include <windows.h>

#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
 int W_WIDTH = 1000;
 int W_HEIGHT = 1500;
GLfloat fAngulo;
#include "Planetas/Header.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>




float Rot; 
extern GLuint lista;
int myObjeto;
extern boolean isOrbitas;
extern boolean isEjes;
extern float w;
extern float h;
extern int  camara;
float AnguloNuevo = 45;
GLuint textura;
extern int myEsfera();

/*typedef struct {

	float distancia;
	float velocidad_Trans;
	float angulo_Tran;
	float velocidad_Rot;
	float angulo_Rot;
	float tamano;
	int lista;
	float cR;
	float cG;
	float cB;
	int textura


} Planeta;
*/
	//						  dist   vTr  atr  vRt  art tam	lista
Planeta sol = {  0 , 0   , 0 , 10 , 0 , 150  , 0,1.0f, 0.50f, 0.0f, FALSE, FALSE,0 };
Planeta Mercurio = { 300, 0.3 , 0 , 50 , 0 , 70  , 0,1.0f, 1.0f,  0.0f , FALSE, FALSE,0 };
Planeta Venus =	{ 400, 0.25 , 0 , 10 , 0 , 75  , 0,0.2f, 0.2f, 0.0f , FALSE , FALSE,0 };

Planeta Marte =	{ 700, 0.19 , 0 , 10 , 0 , 95  , 0,1.0f, 0.50f, 0.0f , FALSE , FALSE,0 };
Planeta Jupiter =		{ 900, 0.15 , 0 , 10 , 0 , 95  , 0,0.0f, 0.50f, 0.5f, FALSE , FALSE,0 };
Planeta  Saturno=		{ 1100, 0.16 , 0 , 10 , 0 , 120, 0,1.0f, 0.50f, 0.0f , TRUE , FALSE ,0 };
Planeta Urano =			{ 1300, 0.1 , 0 , 10 , 0 , 100  , 0,  0.5f, 1.0f, 1.0f , FALSE , FALSE,0 };
Planeta Neptuno =		{ 1500, 0.09 , 0 , 10 , 0 , 100  , 0, 0.0f, 1.0f, 1.0f , FALSE, FALSE,0 };
Planeta Luna =			{ 70 , 0.1 , 0 , 10 , 0 , 10   , 0, 0.0f, 0.50f, 1.0f , FALSE, FALSE,0 };
Planeta Iss =			{ 60 , 0.2 , 0 , 10 , 0 , 7   , 0,1.5f, 1.0f, 01.0f , FALSE , FALSE ,0 };


Planeta Tierra ={ 550, 0.21 , 0 , 10 , 0 , 75  , 0, 0.0f, 0.0f, 1.0f , FALSE, TRUE ,0 };

//Ángulos de rotación
static GLfloat Ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
static GLfloat Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat Specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat SpecRef[] = { 1.0f, 1.0f, 1.0f, 1.0f };

//Posición del foco y dirección de la iluminación
static GLfloat LPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };
static GLfloat SpotDir[] = { 1.0f, 1.0f, 1.0f };



//función de rescalado
void reshape(int ww, int wh)
{
	glViewport(0, 0, (GLsizei)ww, (GLsizei)wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	W_HEIGHT = wh;//redefinimos los valores de venta
	W_WIDTH = ww;
	w = ww;//redefinimos los valores de la ventana que se le pasan desde el archivo de funciones ejes
	h = wh;
	gluPerspective(AnguloNuevo, (float)w / h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	//glutPostRedisplay();
}

void cambiaAngulo(Planeta* planeta) {

	planeta->angulo_Tran += planeta->velocidad_Trans * MYTIEMPO;
	if (planeta->angulo_Tran > 360)
		planeta->angulo_Tran -= 360;
	planeta->angulo_Rot += planeta->velocidad_Rot * MYTIEMPO;
	if (planeta->angulo_Rot > 360)
		planeta->angulo_Rot -= 360;
}


void myMovimiento(int value) {

	cambiaAngulo(&sol);
	cambiaAngulo(&Mercurio);
	cambiaAngulo(&Venus);
	cambiaAngulo(&Tierra);
	cambiaAngulo(&Luna);
	cambiaAngulo(&Iss);
	cambiaAngulo(&Marte);
	cambiaAngulo(&Jupiter);
	cambiaAngulo(&Saturno);
	cambiaAngulo(&Urano);
	cambiaAngulo(&Neptuno);
	glutPostRedisplay();
	glutTimerFunc(MYTIEMPO, myMovimiento, 0);

}

void openGlInit() {
	//Incializaciones varias
	glClearDepth(1.0f); //Valor z-buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // valor limpieza buffer color
	glViewport(0,0,W_WIDTH, W_HEIGHT);
	gluPerspective(AnguloNuevo, (float)W_WIDTH / W_HEIGHT, 1, 1000);  
	glTranslatef(0, 0, -5);
	//Normaliza las normas
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST); // z-buffer
	glEnable(GL_CULL_FACE); //ocultacion caras back
	glCullFace(GL_BACK);


}

void dibujaPlaneta(Planeta* planeta) {
	
		glPushMatrix();
		glRotatef(planeta->angulo_Tran, 0.0, 1.0, 0.0);
		glTranslatef(planeta->distancia, 0.0, 0.0);
		glPushMatrix();
		glRotatef(planeta->angulo_Rot, 0, 1, 0);
		if (isEjes) {
			myEjes();
		}
		glScalef(planeta->tamano, planeta->tamano, planeta->tamano);
		glColor3f(planeta->cR, planeta->cG, planeta->cB);
		glBindTexture(GL_TEXTURE_2D, planeta->textura);
		glCallList(planeta->lista);
		if (planeta->tOrbita) {
			glPopMatrix();
			glPushMatrix();
			glRotatef(60, 1.0, 1.0, 0.0);
			glColor3f(0.5f, 1.0f, 1.0f);
			//dibujo de órbitas
			for (int p = 140; p < 150; p += 2) {
				myOrbitas(p);
			}
			for (int p = 160; p < 170; p += 2) {
				myOrbitas(p);
			}
		}
		glPopMatrix();
		if (planeta->hijos) {
			{
				if (isOrbitas) {
					glPushMatrix();
					glColor3f(1.0f, 1.0f, 1.0f);
					glRotatef(90, 1.0, 0.0, 0.0);
					myOrbitas(Luna.distancia);
					myOrbitas(Iss.distancia);
					glPopMatrix();
				}

				glPushMatrix();
				glRotatef(Luna.angulo_Tran, 0.0, 1.0, 0.0);
				glTranslatef(Luna.distancia, 0.0, 0.0);
				glPushMatrix();
				glRotatef(Luna.angulo_Rot, 0, 1, 0);
				if (isEjes) {
					myEjes();
				}
				glScalef(Luna.tamano, Luna.tamano, Luna.tamano);
				glColor3f(0.0f, 0.50f, 1.0f);
				glBindTexture(GL_TEXTURE_2D, Luna.textura);
				glCallList(Luna.lista);
				glPopMatrix();
				glPopMatrix();
			}

			{
				glPushMatrix();
				glRotatef(Iss.angulo_Tran, 0.0, 1.0, 0.0);
				glTranslatef(Iss.distancia, 0.0, 0.0);
				glPushMatrix();
				glRotatef(Iss.angulo_Rot, 0, 1, 0);
				if (isEjes) {
					myEjes();
				}
				glScalef(Iss.tamano, Iss.tamano, Iss.tamano);
				glColor3f(1.5f, 1.0f, 01.0f);
				glCallList(Iss.lista);
				glPopMatrix();
				glPopMatrix();




			}
		}
		
		glPopMatrix();
	
}

void Carga_Texturas(Planeta* planeta, char* imagenPlaneta) {
	// load and create a texture 
	// -------------------------

	glGenTextures(1, &planeta->textura);
	glBindTexture(GL_TEXTURE_2D, planeta->textura); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	unsigned char* data = stbi_load(imagenPlaneta, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data); //con mimap 

	}
	else
	{
		//std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}



// Función de display
void display(void) {
	// Clear the window with current clearing color

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	switch (camara)
	{
	case 1:
		myCamera();
		break;
	case 2:
		myTelescopio(Tierra.distancia, Tierra.angulo_Tran, sol.distancia, sol.angulo_Tran);
		break;
	case 3:
		myTelescopio(Tierra.distancia, Tierra.angulo_Tran, Mercurio.distancia, Mercurio.angulo_Tran);
		break;
	case 4:
		myTelescopio(Tierra.distancia, Tierra.angulo_Tran, Marte.distancia, Marte.angulo_Tran);
		break;
	case 5:

		myTelescopioSatelite(Tierra.distancia, Tierra.angulo_Tran,Luna.distancia, Luna.angulo_Tran);

		break;
	case 6:
		myTelescopio(Tierra.distancia, Tierra.angulo_Tran, Jupiter.distancia, Jupiter.angulo_Tran);
		break;
	case 7:
		myTelescopio(Tierra.distancia, Tierra.angulo_Tran, Saturno.distancia, Saturno.angulo_Tran);
		break;
	case 8:
		myTelescopio(Tierra.distancia, Tierra.angulo_Tran, Urano.distancia, Urano.angulo_Tran);
		break;
	case 9:
		myTelescopio(Tierra.distancia, Tierra.angulo_Tran, Neptuno.distancia, Neptuno.angulo_Tran);
		break;

	case 10:
		myTelescopioSatelite(Tierra.distancia, Tierra.angulo_Tran, Iss.distancia, Iss.angulo_Tran);
		break;
	default:
		myCamera();
		break;
	}

	// Se activa la matriz del modelador
	glMatrixMode(GL_MODELVIEW);
	// Inicializamos la matriz del modelo a la identidad
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glRotatef(90, 1.0, 0.0, 0.0);
		if (isOrbitas) {
			myOrbitas(Mercurio.distancia);
			myOrbitas(Venus.distancia);
			myOrbitas(Tierra.distancia);
			myOrbitas(Marte.distancia);
			myOrbitas(Jupiter.distancia);
			myOrbitas(Saturno.distancia);
			myOrbitas(Urano.distancia);
			myOrbitas(Neptuno.distancia);
		}
		glPopMatrix();
	



		glDisable(GL_LIGHTING);
		dibujaPlaneta(&sol);
		glEnable(GL_LIGHTING);


		dibujaPlaneta(&Mercurio);
		dibujaPlaneta(&Venus);	
		dibujaPlaneta(&Marte);
	
		dibujaPlaneta(&Tierra); 
	
		dibujaPlaneta(&Jupiter);		
		dibujaPlaneta(&Saturno);
		dibujaPlaneta(&Urano);
		dibujaPlaneta(&Neptuno);
	
	// Se limpian los buffers
	glutSwapBuffers();
	glFlush();
}


int main(int argc, char** argv)
{


	glutInit(&argc, argv);
	//Posicion de la ventana
	glutInitWindowPosition(100, 100);
	//Tamano de la ventana
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	//Tipo de color y buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	//Crear la ventana
	glutCreateWindow("Sistema Solar");
	openGlInit();
	//Eventos
	glutDisplayFunc(display);

	glutKeyboardFunc(myTeclado);
	glutSpecialFunc(myTeclasespeciales);
    glutReshapeFunc(reshape);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(AnguloNuevo, (float)W_WIDTH / (float)W_HEIGHT, 1.0, 100.0);
	//cargamos las listas de las esferas en las listas de la estrucctura
	myObjeto = myEsfera();
	sol.lista = myObjeto;
	Mercurio.lista = myObjeto;
	Venus.lista = myObjeto;
	Tierra.lista = myObjeto;
	Marte.lista = myObjeto;
	Jupiter.lista = myObjeto;
	Saturno.lista = myObjeto;
	Urano.lista = myObjeto;
	Neptuno.lista = myObjeto;
	Luna.lista = myObjeto;
	Iss.lista = myObjeto;

	CreaListaOrbita();
	//Lazo principal
	myMovimiento(1);
	//Normalizar las normales
	glEnable(GL_NORMALIZE);


	//Definimos las iluminaciones
	glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
	glLightfv(GL_LIGHT0, GL_POSITION, LPosition);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SpotDir);



	//  Activa el test de profundidad y oculta caras internas.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//	Activa las texturas y el modelo de sombreado suavizado.
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	//Efectos de foco
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 179.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0f);
	//Activamos las luces
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	//Definimos seguimiento del color
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//Definimos brillo metálico
	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecRef);
	glMateriali(GL_FRONT, GL_SHININESS, 1);



	myMenu();
	//myCamera();
	Carga_Texturas(&sol, "sola.jpg");
	Carga_Texturas(&Tierra, "Terra.bmp");
	Carga_Texturas(&Mercurio, "mercurio.jpg");
	Carga_Texturas(&Venus, "venus.jpg");
	Carga_Texturas(&Marte, "marte.jpg");
	Carga_Texturas(&Jupiter, "jupiter.jpg");
	Carga_Texturas(&Saturno, "saturno.jpg");
	Carga_Texturas(&Urano, "urano.jpg");
	Carga_Texturas(&Neptuno, "neptuno.jpg");
	Carga_Texturas(&Luna, "luna.jpg");
	//Carga_Texturas(&Iss, "");
	glutMainLoop();
	return 0;
}