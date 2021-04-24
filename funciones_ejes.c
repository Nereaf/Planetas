#include <windows.h>	//Inclusion de variables de windows

#include <glut.h>	//Inclusion de GLUT
#include <GL/gl.h>		//Inclusion de GL		 	
#include <GL/glu.h>	
#include <stdio.h>
#include <math.h>	//Inclusion de librerias auxiliares	
#define INCREMENTO .01
#define DISTANCIA 4000
#define Frac_Circ 1000 //fracciones del circulo
#define PI 3.141592
//float alpha=90;
//float beta =50.7;
GLuint lista;
float alpha=0;
float beta =0;

boolean isOrbitas = TRUE;
boolean isEjes = TRUE;
float h= 1500;
float w= 1000;
int camara=0;
void myCamera() {

	//Configuración de la matriz de proyeccion
	glMatrixMode(GL_PROJECTION);
	//La ponemos auno
	glLoadIdentity();

	gluPerspective(45.0, w/h, 1000, 100000.0);
	gluLookAt(((float)DISTANCIA*(float) sin(alpha)*cos(beta)),((float)DISTANCIA*(float) sin(beta)), ((float)DISTANCIA*cos(alpha)*cos(beta)), 0,0,0,0,cos(beta),0);  


}

void onMenu(int option) {
	camara = option;
	glutPostRedisplay();
}

void myMenu(void) {
	int menu;
	menu = glutCreateMenu(onMenu);
	glutAddMenuEntry("Sistema solar completo", 1);
	glutAddMenuEntry("Sol", 2);
	glutAddMenuEntry("Mercurio", 3);
	glutAddMenuEntry("Marte", 4);
	glutAddMenuEntry("Luna", 5);
	glutAddMenuEntry("Jupiter", 6);
	glutAddMenuEntry("Saturno", 7);
	glutAddMenuEntry("Urano", 8);
	glutAddMenuEntry("Neptuno", 9);
	glutAddMenuEntry("ISS", 10);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void myTelescopio(float distancia, float angulo, float distancia_obj, float angulo_obj) {
	//conf matriz proyeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, w / h, 1, 2000.0);
	//anglo*PI/180 para tener el angulo en radianes
	gluLookAt(distancia*cos(angulo*PI/180.0),0,(-1)*distancia*sin(angulo*PI/180.0),
		distancia_obj*cos(angulo_obj*PI/180.0),0,(-1)*distancia_obj*sin(angulo_obj*PI/180.0),0,1,0);

}
void myTelescopioSatelite(float distancia, float angulo, float distancia_sat, float angulo_sat) {
	//conf matriz proyeccion
	glMatrixMode(GL_PROJECTION);
	//calculamos las coordenadas de la luna en función de la distancia de la tierra y la distancia del satélite
	float y= distancia*sin(angulo*PI/180.0)+ distancia_sat * sin((angulo_sat+angulo) * PI / 180.0);
	float x = cos(angulo*PI/180.0)*distancia + distancia_sat * cos((angulo_sat + angulo) * PI / 180.0);
	glLoadIdentity();
	gluPerspective(45.0, w / h, 1, 2000.0);
	//anglo*PI/180 para tener el angulo en radianes
	gluLookAt(distancia * cos(angulo * PI / 180.0), 0, (-1) * distancia * sin(angulo * PI / 180.0),x, 0,-y, 0, 1, 0);
}


void myEjes() {

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(200.0f, 0.0f, 0.0f);
	glEnd();


	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 200.0f, 0.0f);
	glEnd();


	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0, 200.0f);
	glEnd();

	//Diagonal
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(.35f, .35, .35f);
	glEnd();

}




void myTeclado(unsigned char tras,int x,int y)
{
	switch (tras) {
	case 'l':
		
	break;
	case 'o':
		if (isOrbitas) {
			isOrbitas = FALSE;
		}
		else {
			isOrbitas = TRUE;
		}
			break;
	case 'e':
		if (isEjes) {
			isEjes = FALSE;
		}
		else {
			isEjes = TRUE;
		}

			break;
	case 'p':
		
	break;
	
	default:
	break;
	}
// Se se modificou algo redebúxase
  glutPostRedisplay();
}

/**************************************
FUNCION DE CONTROL DE TECLAS ESPECIAIS:
**************************************
*/

void CreaListaOrbita(void) {
	lista = glGenLists(1);
	glNewList(lista, GL_COMPILE);

	glBegin(GL_LINE_LOOP);

	glColor3f(0.0f, 1.0f, 1.0f);

	float theta = -PI;

	while (theta < PI) {
		glVertex3f(100.0* sin(theta), 100.0* cos(theta), 0);
		theta += 0.1;
	}

	glEnd();

	glEndList();
}


void myOrbitas(int radio) {

		glPushMatrix();
		glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
		glScalef(radio / 100.0, radio / 100.0, radio / 100.0);
		glCallList(lista);
		glPopMatrix();
	

}
 void myTeclasespeciales(int cursor,int x,int y) 
{
	switch(cursor) 
	{
//Traslaciones:
		case GLUT_KEY_F1:
	   		break;
		case GLUT_KEY_F2:
		Sleep(100);
		break;
		case GLUT_KEY_F3:
			
		break;
		case GLUT_KEY_F4:

		break;
		case GLUT_KEY_F5:
			
		break;
		case GLUT_KEY_F6:
		
		break;
//Giros:
		case GLUT_KEY_UP:
			beta-=INCREMENTO;
			break;
		case GLUT_KEY_DOWN:
			beta+=INCREMENTO;
			break;
		case GLUT_KEY_RIGHT:
			alpha-=INCREMENTO;
			break;
		case GLUT_KEY_LEFT:
			alpha+=INCREMENTO;
			break;
		
		
			
		default:
			break;
	}

	if(alpha>=PI*2.0 && alpha<=0 ) alpha=0;
	if(beta>=PI*2.0 && beta<=0 ) beta=0; //hay que repasarlo para evitar el salto


		glutPostRedisplay();
}

