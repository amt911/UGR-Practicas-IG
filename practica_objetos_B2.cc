//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B2.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, ESFERA, CONO, CILINDRO, ROTACION_X, RELOJ, RARO, CAZA} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


// objetos
const int ROTACIONES=6;

_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply; 
_rotacion rotacion, rotacion_x, raro; 
_esfera esfera(1, ROTACIONES, ROTACIONES, y);
_cono cono(1, 3, ROTACIONES, z);
_cilindro cilindro(1, 3, ROTACIONES, x);
_ply_rot reloj("revolucion", ROTACIONES, y);
// _objeto_ply *ply1;


_cuerpo prueba;
_alas prueba2;
_alas_traseras prueba3;

//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

switch (t_objeto){
	case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,20);break;
	case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,20);break;
        case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,20);break;
        case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,20);break;
		case ESFERA: esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,20);break;
		case CONO: cono.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,20);break;
		case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,20);break;
		case ROTACION_X: rotacion_x.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,20);break;
		case RELOJ: reloj.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,20);break;
		case RARO: raro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,20);break;
		case CAZA: prueba.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,20);
		prueba2.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,20);
		prueba3.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,20);break;
	}

}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{

clean_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_CHESS;break;
        case 'P':t_objeto=PIRAMIDE;break;
        case 'C':t_objeto=CUBO;break;
        case 'O':t_objeto=OBJETO_PLY;break;	
        case 'R':t_objeto=ROTACION;break;
		case '5':t_objeto=ESFERA;break;
		case 'N':t_objeto=CONO; break;
		case 'Z':t_objeto=CILINDRO; break;
		case 'X':t_objeto=ROTACION_X; break;
		case 'A':t_objeto=RELOJ; break;
		case 'W':t_objeto=RARO; break;
		case 'F':t_objeto=CAZA; break;
	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);



}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{
 const int ROT=4;



// perfil 

vector<_vertex3f> perfil2;
_vertex3f aux;

//Copa implementada por el profesor
/*
aux.x=1.2; aux.y=-1.0; aux.z=0.0;
perfil2.push_back(aux);

aux.x=0.6; aux.y=0; aux.z=0.0;
perfil2.push_back(aux);

aux.x=1.2; aux.y=1.2; aux.z=0.0;
perfil2.push_back(aux);

aux.x=1.0; aux.y=1.8; aux.z=0.0;
perfil2.push_back(aux);
*/

//Figura que se puede rotar tanto en el eje y como en el x para probar que funciona
aux.x=3; aux.y=0; aux.z=0.0;
perfil2.push_back(aux);

aux.x=2.5; aux.y=0.5; aux.z=0.0;
perfil2.push_back(aux);

aux.x=2; aux.y=0.7; aux.z=0.0;
perfil2.push_back(aux);

aux.x=1; aux.y=0.9; aux.z=0.0;
perfil2.push_back(aux);

aux.x=1; aux.y=2; aux.z=0.0;
perfil2.push_back(aux);

aux.x=1.2; aux.y=3; aux.z=0.0;
perfil2.push_back(aux);

aux.x=2; aux.y=3.8; aux.z=0.0;
perfil2.push_back(aux);

aux.x=2.6; aux.y=4.3; aux.z=0.0;
perfil2.push_back(aux);

aux.x=3.2; aux.y=5.1; aux.z=0.0;
perfil2.push_back(aux);

aux.x=3; aux.y=6; aux.z=0.0;
perfil2.push_back(aux);

aux.x=0; aux.y=6; aux.z=0.0;
perfil2.push_back(aux);


rotacion_x.parametros(perfil2, ROT, x);
rotacion.parametros(perfil2, ROT, y);

perfil2.clear();

//Figura rara

aux.x=1; aux.y=0; aux.z=0.0;
perfil2.push_back(aux);

aux.x=0.71; aux.y=2; aux.z=0.71;
perfil2.push_back(aux);

raro.parametros(perfil2, ROT);

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 2");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);

//ply1 = new _objeto_ply(argv[1]);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}


