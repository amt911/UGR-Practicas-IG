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
Tipo tipo;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


// objetos
const int ROTACIONES=32;

_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply; 
_rotacion rotacion, rotacion_x, raro; 
_esfera esfera(1, ROTACIONES, ROTACIONES, y);
_cono cono(1, 3, ROTACIONES, z);
_cilindro cilindro(1, 3, ROTACIONES, z);
_ply_rot reloj("revolucion", ROTACIONES, y);
// _objeto_ply *ply1;
_tornado caza(Materiales::GOMA);

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
		case CAZA: caza.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,20, tipo); break;
	}

}


//**************************************************************************
//
//***************************************************************************
void luces(){			//INCLUIR LO DE LA FOTO
	float  luz1[]={1.0, 1.0, 1.0, 1.0},		//Azul
        pos1[]= {0, 20.0, 20, 1.0};
/*
	float  luz2[]={0, 1.0, 0, 1.0},
        pos2[]= {40, 20.0, 0, 1.0};
*/
	glLightfv (GL_LIGHT1, GL_DIFFUSE, luz1);
glLightfv (GL_LIGHT1, GL_SPECULAR, luz1);

glLightfv (GL_LIGHT1, GL_POSITION, pos1);




/*
	glLightfv (GL_LIGHT2, GL_DIFFUSE, luz2);
glLightfv (GL_LIGHT2, GL_SPECULAR, luz2);

glLightfv (GL_LIGHT2, GL_POSITION, pos2);*/
//glEnable(GL_LIGHTING);
/*
float ambiente[]={0.25, 0.148, 0.06475, 1.0};
float l1[]={0.4, 0.2368, 0.1036, 1.0};
float l2[]={0.774597, 0.458561, 0.200621, 1.0};
float l3[]={76.8};//76.8;


glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
glLightfv(GL_LIGHT1, GL_DIFFUSE, l1);
glLightfv(GL_LIGHT3, GL_SPECULAR, l2);
glLightfv(GL_LIGHT3, GL_SHININESS, l3);

//glDisable (GL_LIGHT0);
glEnable(GL_LIGHT0);*/
glEnable (GL_LIGHT1);
//glEnable (GL_LIGHT2);

}


void draw(void)
{

clean_window();
change_observer();
//luces(alfa, beta);//Por ahora sera vacia
luces();
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

//FUncion de animacion

int sleep=0;
const double mult=0.5;	//Factor que permite que la animacion vaya mas rapido o mas lento (debido a que la velocidad es dependiente de la maquina)
void animacion(){
	bool encontrado=false;
	int acto=0;
	
	for(int i=0; i<39 && !encontrado; i++){
		if(!caza.actos[i]){
			encontrado=true;
			acto=i;
		}
	}

	switch(acto){
		case 0:{		//Abre la ventana para entrar
			if(caza.giro_ventana<=caza.max_giro_ventana)
				caza.giro_ventana+=mult*0.3;

			if(caza.giro_ventana>caza.max_giro_ventana)
				caza.actos[acto]=true;

			break;
		}

		//Fase de esperar un poco
		case 1:{
		//
			sleep++;

			if(sleep==45){
				caza.actos[acto]=true;
				sleep=0;
			}

			break;
		}
		case 2:{	//La cierra
		
			caza.giro_ventana-=mult*0.3;

			if(caza.giro_ventana<0)
				caza.actos[acto]=true;			

			break;
		}

		case 3:{	//Baja los flaps
		
			if(caza.flap_giro<=caza.max_flap_giro)
				caza.flap_giro+=mult*0.3;

			if(caza.flap_trans<=caza.max_flap_trans)
				caza.flap_trans+=mult*0.003;


			if(caza.flap_giro>caza.max_flap_giro and caza.flap_trans>caza.max_flap_trans)
				caza.actos[acto]=true;
			break;
		}

		case 4:{
		
			sleep++;
			if(sleep==45){
				caza.actos[acto]=true;
				sleep=0;
			}
			break;
		}

		case 5:{		//Fase de mover aeronave un poco hacia arriba y las alas
		

			if(caza.giro_aeronave_x>=-15)
				caza.giro_aeronave_x-=mult*0.1;

			if(caza.angulo_trasero_l<=20){
				caza.angulo_trasero_l+=mult*0.2;
				caza.angulo_trasero_r+=mult*0.2;
			}

			if(caza.angulo_trasero_l>20 and caza.giro_aeronave_x<-15)
				caza.actos[acto]=true;

			break;
		}

		case 6:{		//Fase de poner las alas traseras de nuevo en su sitio
			

			if(caza.angulo_trasero_l>=0){
				caza.angulo_trasero_l-=mult*0.3;
				caza.angulo_trasero_r-=mult*0.3;
			}			

			if(caza.angulo_trasero_l<0)
				caza.actos[acto]=true;			

			break;
		}

		case 7:{
		
			sleep++;
			if(sleep==24){
				caza.actos[acto]=true;
				sleep=0;
			}

			break;
		}

		case 8:{		//Fase de levantar el tren de aterrizaje
		
			if(caza.tt_giro_x<=caza.max_tt_giro_x)
				caza.tt_giro_x+=mult*0.5;

			if(caza.tt_giro_y<=caza.max_tt_giro_y)
				caza.tt_giro_y+=mult*0.5;

			if(caza.giro_tren_d<=caza.max_giro_tren_d)
				caza.giro_tren_d+=mult*0.5;


			if(caza.tt_giro_x>caza.max_tt_giro_x and caza.tt_giro_y>caza.max_tt_giro_y and caza.giro_tren_d>caza.max_giro_tren_d){
				caza.actos[acto]=true;
			}

			break;
		}		

		case 9:{		//Fase de poner todo recto
		

			if(caza.giro_aeronave_x<=0)
				caza.giro_aeronave_x+=mult*0.1;

			if(caza.angulo_trasero_l>=-10){
				caza.angulo_trasero_l-=mult*0.3;
				caza.angulo_trasero_r-=mult*0.3;
			}

			if(caza.angulo_trasero_l<-10 and caza.giro_aeronave_x>0)
				caza.actos[acto]=true;

			break;
		}				
		case 10:{		//Fase de poner todo recto
		

			if(caza.angulo_trasero_l<=0){
				caza.angulo_trasero_l+=mult*0.3;
				caza.angulo_trasero_r+=mult*0.3;
			}

			if(caza.angulo_trasero_l>0)
				caza.actos[acto]=true;

			break;
		}	

		case 11:{
			sleep++;
			if(sleep==45){
				caza.actos[acto]=true;
				sleep=0;
			}

			break;
		}

		case 12:{		//Fase de levantar los flaps
		
			if(caza.flap_giro>=0)
				caza.flap_giro-=mult*0.3;

			if(caza.flap_trans>=0)
				caza.flap_trans-=mult*0.003;


			if(caza.flap_giro<0 and caza.flap_trans<0)
				caza.actos[acto]=true;

			break;
		}	

		//Fase de levantar un spd brk a la mitad de la posicion final
		case 13:{
			

			if(caza.giro_frenos_l<=(caza.max_giro_frenos/3))
				caza.giro_frenos_l+=mult*1;

			if(caza.giro_frenos_l>(caza.max_giro_frenos/3))
				caza.actos[acto]=true;

			break;
		}
		//Fase de levantar del todo el spd brk y de girar la aeronave en el eje z 90 grados							
		case 14:{
			

			if(caza.giro_frenos_l<=caza.max_giro_frenos)
				caza.giro_frenos_l+=mult*1;

			if(caza.giro_aeronave_z>=-90)
				caza.giro_aeronave_z-=mult*0.5;


			if(caza.giro_frenos_l>caza.max_giro_frenos and caza.giro_aeronave_z<-90)
				caza.actos[acto]=true;

			break;
		}	

		//Bajamos de nuevo el spd brk levantado
		case 15:{
			if(caza.giro_frenos_l>=0)
				caza.giro_frenos_l-=mult*1.4;			

			if(caza.giro_frenos_l<0)
				caza.actos[acto]=true;

			break;
		}

		//Movemos el eje y 90 grados
		case 16:{
			

			if(caza.giro_aeronave_y<=90)
				caza.giro_aeronave_y+=mult*0.3;

			if(caza.angulo_trasero_l<=20){
				caza.angulo_trasero_l+=mult*0.2;
				caza.angulo_trasero_r+=mult*0.2;
			}


			if(caza.giro_aeronave_y>90 and caza.angulo_trasero_l>20)
				caza.actos[acto]=true;

			break;
		}	


		//Fase de poner de nuevo las alas traseras en su sitio
		case 17:{
			

			if(caza.angulo_trasero_l>=0){
				caza.angulo_trasero_l-=mult*0.2;
				caza.angulo_trasero_r-=mult*0.2;
			}			

			if(caza.angulo_trasero_l<0)
				caza.actos[acto]=true;

			break;
		}

		//SPD BRK DERECHO A UN TERCIO
		case 18:{
			

			if(caza.giro_frenos_r<=(caza.max_giro_frenos/3))
				caza.giro_frenos_r+=mult*1;

			if(caza.giro_frenos_r>(caza.max_giro_frenos/3))
				caza.actos[acto]=true;

			break;
		}

		//Fase de ponerse de nuevo recto (bien posicionada toda la aeronave) mover el eje y
		case 19:{
			
			if(caza.giro_frenos_r<=caza.max_giro_frenos)
				caza.giro_frenos_r+=mult*1;

			if(caza.giro_aeronave_z<=0)
				caza.giro_aeronave_z+=mult*0.3;

			
			if(caza.giro_frenos_r>caza.max_giro_frenos and caza.giro_aeronave_z>0)
				caza.actos[acto]=true;

			break;
		}

		//Fase de poner el spd brk derecho en su sitio
		case 20:{
			

			if(caza.giro_frenos_r>=0)
				caza.giro_frenos_r-=mult*1.4;			

			if(caza.giro_frenos_r<0)
				caza.actos[acto]=true;

			break;
		}


		//Fase de mover las alas principales y ponerse en modo supersonico
		case 21:{
			

			if(caza.angulo_alas<=caza.max_angulo_alas)
				caza.angulo_alas+=mult*0.3;

			if(caza.angulo_alas>caza.max_angulo_alas)
				caza.actos[acto]=true;

			break;
		}


		//Fase de mover un poco las alas traseras para realizar giros
		case 22:{
			

			if(caza.angulo_trasero_r<=6.7){
				caza.angulo_trasero_r+=mult*0.6;
				caza.angulo_trasero_l-=mult*0.6;
			}

			if(caza.angulo_trasero_r>5)
				caza.actos[acto]=true;

			break;
		}


		//Fase de hacer unos giros en supersonico 15 grados para las alas traseras
		case 23:{
			if(caza.angulo_trasero_r<=20){
				caza.angulo_trasero_r+=mult*0.6;
				caza.angulo_trasero_l-=mult*0.6;
			}


			if(caza.giro_aeronave_x<=360)
				caza.giro_aeronave_x+=mult*1;

			if(caza.angulo_trasero_r>15 and caza.giro_aeronave_x>360){
				caza.giro_aeronave_x=0;
				caza.actos[acto]=true;
			}

			break;
		}

		//Fase de poner las alas traseras en su sitio
		case 24:{
			if(caza.angulo_trasero_r>=0){
				caza.angulo_trasero_r-=mult*0.8;
				caza.angulo_trasero_l+=mult*0.8;
			}			

			if(caza.angulo_trasero_r<0)
				caza.actos[acto]=true;

			break;
		}

		//Fase de esperar un poco
		case 25:{
		//
			sleep++;

			if(sleep==45){
				caza.actos[acto]=true;
				sleep=0;
			}

			break;
		}		

		//Fase de deceleracion
		case 26:{
			if(caza.angulo_alas>=0)
				caza.angulo_alas-=mult*0.3;

			if(caza.angulo_alas<0)
				caza.actos[acto]=true;		

			break;	
		}

		//Fase de sleep un poco
		case 27:{
			sleep++;

			if(sleep==45){
				caza.actos[acto]=true;
				sleep=0;
			}

			break;
		}

		//Fase de moverse con el timon hacia la derecha EJE Y
		case 28:{
			if(caza.giro_aeronave_y>=0)
				caza.giro_aeronave_y-=mult*0.3;

			if(caza.timon_giro<=caza.max_timon_giro)
				caza.timon_giro+=1;

			

			if(caza.giro_aeronave_y<0 and caza.timon_giro>caza.max_timon_giro)
				caza.actos[acto]=true;

			break;
		}


		//Fase de poner el timon en sus sitio
		case 29:{
			if(caza.timon_giro>=0)
				caza.timon_giro-=mult*1;			

			if(caza.timon_giro<0)
				caza.actos[acto]=true;

			break;
		}

		//Fase de abrir flaps y mover un poco la aeronave hacia arriba (muy lento esto ultimo)
		case 30:{
			if(caza.flap_giro<=caza.max_flap_giro)
				caza.flap_giro+=mult*0.3;

			if(caza.flap_trans<=caza.max_flap_trans)
				caza.flap_trans+=mult*0.003;

			if(caza.giro_aeronave_x>=-2.5)
				caza.giro_aeronave_x-=mult*0.01;


			if(caza.flap_giro>caza.max_flap_giro and caza.flap_trans>caza.max_flap_trans and caza.giro_aeronave_x<-2.5)
				caza.actos[acto]=true;

			break;
		}		

		//Fase de abrir el tren de aterrizaje
		case 31:{
			if(caza.tt_giro_x>=0)
				caza.tt_giro_x-=mult*0.5;

			if(caza.tt_giro_y>=0)
				caza.tt_giro_y-=mult*0.5;

			if(caza.giro_tren_d>=0)
				caza.giro_tren_d-=mult*0.5;


			if(caza.tt_giro_x<0 and caza.tt_giro_y<0 and caza.giro_tren_d<0){
				caza.actos[acto]=true;
			}

			break;			
		}


		//Fase de girar hasta 5 grados la aeronave y girar -5 grados el tren trasero
		case 32:{
			if(caza.giro_aeronave_x>=-10)
				caza.giro_aeronave_x-=mult*0.02;			

			if(caza.angulo_trasero_l<=10){
				caza.angulo_trasero_l+=mult*0.03;
				caza.angulo_trasero_r+=mult*0.03;
			}

			if(caza.giro_aeronave_x<-10 and caza.angulo_trasero_l>10)
				caza.actos[acto]=true;

			break;
		}

		//Sleep
		case 33:{
			sleep++;
			if(sleep==45){
				caza.actos[acto]=true;
				sleep=0;
			}

			break;			
		}		

		//Touchdown: (Mover la aeronave a 0 grados y las alas traseras a 3 grados hacia abajo)
		case 34:{
			if(caza.giro_aeronave_x<=0)
				caza.giro_aeronave_x+=mult*0.1;						

			if(caza.angulo_trasero_l>=-10){
				caza.angulo_trasero_l-=mult*0.3;
				caza.angulo_trasero_r-=mult*0.3;
			}

			if(caza.giro_aeronave_x>0 and caza.angulo_trasero_l<-10)
				caza.actos[acto]=true;


			break;
		}

		//Mover las alas traseras a su sitio y abrir todos los spd brk
		case 35:{
			if(caza.angulo_trasero_l<=0){
				caza.angulo_trasero_l+=mult*0.7;
				caza.angulo_trasero_r+=mult*0.7;
			}			

			if(caza.giro_frenos_l<=caza.max_giro_frenos){
				caza.giro_frenos_l+=mult*0.7;
				caza.giro_frenos_r+=mult*0.7;
			}

			if(caza.ft_giro<=caza.max_ft_giro)
				caza.ft_giro+=0.7;


			if(caza.angulo_trasero_l>0 and caza.giro_frenos_l>caza.max_giro_frenos and caza.ft_giro>caza.max_ft_giro)
				caza.actos[acto]=true;

			break;
		}

		//Sleep
		case 36:{
			sleep++;
			if(sleep==45){
				caza.actos[acto]=true;
				sleep=0;
			}

			break;			
		}

		//Cerrar todos los flaps y frenos aereos
		case 37:{
			if(caza.flap_giro>=0)
				caza.flap_giro-=mult*0.3;

			if(caza.flap_trans>=0)
				caza.flap_trans-=mult*0.003;			

			if(caza.giro_frenos_l>=0){
				caza.giro_frenos_l-=mult*1;
				caza.giro_frenos_r-=mult*1;
			}

			if(caza.ft_giro>=0)
				caza.ft_giro-=1;				


			if(caza.flap_giro<0 and caza.flap_trans<0 and caza.ft_giro<0)
				caza.actos[acto]=true;

			break;
		}

		//Abir ventana
		case 38:{
			if(caza.giro_ventana<=caza.max_giro_ventana)
				caza.giro_ventana+=mult*0.3;

			if(caza.giro_ventana>caza.max_giro_ventana)
				caza.actos[acto]=true;			

			break;
		}

		default: break;
	}

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
int indice=0;	//Indice usado para elegir cambiar velocidad a una articulacion
int indiceObjetos=0;	//INDICE QUE SE USA PARA CICLAR ENTRE OBJETOS
void normal_key(unsigned char Tecla1,int x,int y)
{
	/*
	
	cout <<"******************************************************************" <<endl;
	cout <<"******************************************************************" <<endl;
	cout <<"** IMPORTANTE: Debido a la evidente falta de teclas, los objetos se puede ciclar si se pulsa repetidamente la tecla P" <<endl;
	cout <<"** Controles avion: " <<endl;
	cout <<"** Mover aeronave sobre eje x: W/S" <<endl;
	cout <<"** Mover aeronave sobre eje y: Z/X" <<endl;
	cout <<"** Mover aeronave sobre eje z: A/D" <<endl;
	cout <<"** Mover ventana de cabina: F1/F2" <<endl;
	cout <<"** Mover flaps: F3/F4" <<endl;
	cout <<"** Mover alas principales (subsonico/supersonico): F5/F6" <<endl;
	cout <<"** Mover frenos aereos delantero: F7/F8" <<endl;
	cout <<"** Mover timon de la aeronave: F9/F10" <<endl;
	cout <<"** Mover ala trasera: F11/F12" <<endl;
	cout <<"** Mover frenos aereos traseros: G/T" <<endl;
	cout <<"** Mover tren de aterrizaje: H/Y" <<endl;
	cout <<"** Cambiar a pintado especial: 6" <<endl;
	cout <<"** Cambiar a pintado normal: 5" <<endl;
	cout <<"** Activar animacion: 9" <<endl;
	cout <<"** Desactivar animacion: 0" <<endl;
	cout <<"******************************************************************" <<endl;
	cout <<"******************************************************************" <<endl;


*/
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_CHESS;break;
	case '5':tipo=NORMAL;break;
	case '6':tipo=ESPECIAL;break;
	case '9': caza.limpiar_actos();glutPostRedisplay();glutIdleFunc(animacion);break;
	case '0': glutIdleFunc(NULL); caza.limpiar_actos(); glutPostRedisplay(); break;
	case 'F':t_objeto=CAZA; break;

	case 'P':{
		indiceObjetos=(indiceObjetos+1)%10;

		switch (indiceObjetos)
		{
			case 0:t_objeto=PIRAMIDE;break;
			case 1:t_objeto=CUBO;break;
			case 2:t_objeto=OBJETO_PLY;break;	
			case 3:t_objeto=ROTACION;break;
			case 4:t_objeto=ESFERA;break;
			case 5:t_objeto=CONO; break;
			case 6:t_objeto=CILINDRO; break;
			case 7:t_objeto=ROTACION_X; break;
			case 8:t_objeto=RELOJ; break;
			case 9:t_objeto=RARO; break;			
		}

		break;
	}


		case '7':modo=SOLID_ILLUMINATED_FLAT;break;
		case '8':modo=SOLID_ILLUMINATED_GOURAUD;break;

	case 'D': caza.giro_aeronave_z+=caza.constantes_animacion[2]*caza.factor_mult[2]; break;
	case 'A': caza.giro_aeronave_z-=caza.constantes_animacion[2]*caza.factor_mult[2]; break;

	case 'Z':{
		caza.giro_aeronave_y+=caza.constantes_animacion[1]*caza.factor_mult[1]; 
		
		//SOLO CUANDO LA Z ESTE A 90 O -90

		break;
	} 

	case 'X':{
	 caza.giro_aeronave_y-=caza.constantes_animacion[1]*caza.factor_mult[1];
	 break;
	}

	case 'W': caza.giro_aeronave_x+=caza.constantes_animacion[0]*caza.factor_mult[0]; break;
	case 'S': caza.giro_aeronave_x-=caza.constantes_animacion[0]*caza.factor_mult[0]; break;		

	case 'T': {
		caza.ft_giro+=caza.constantes_animacion[3]*caza.factor_mult[3]; 

		if(caza.ft_giro>caza.max_ft_giro)
			caza.ft_giro=caza.max_ft_giro;
					
		break;
	}
	case 'G':{
		caza.ft_giro-=caza.constantes_animacion[3]*caza.factor_mult[3];

		if(caza.ft_giro<0)
			caza.ft_giro=0;

		break;
	} 

	case 'Y': {
		caza.tt_giro_x+=caza.constantes_animacion[4]*caza.factor_mult[4];
		caza.tt_giro_y+=caza.constantes_animacion[5]*caza.factor_mult[5]; 
		caza.giro_tren_d+=caza.constantes_animacion[6]*caza.factor_mult[6];

		if(caza.tt_giro_x>caza.max_tt_giro_x)
			caza.tt_giro_x=caza.max_tt_giro_x;


		if(caza.tt_giro_y>caza.max_tt_giro_y)
			caza.tt_giro_y=caza.max_tt_giro_y;

		if(caza.giro_tren_d>caza.max_giro_tren_d)
			caza.giro_tren_d=caza.max_giro_tren_d;					

		break;
	}
	case 'H':{
		caza.tt_giro_x-=caza.constantes_animacion[4]*caza.factor_mult[4];
		caza.tt_giro_y-=caza.constantes_animacion[5]*caza.factor_mult[5];
		caza.giro_tren_d-=caza.constantes_animacion[6]*caza.factor_mult[6];

		if(caza.tt_giro_x<0)
			caza.tt_giro_x=0;

		if(caza.tt_giro_y<0)
			caza.tt_giro_y=0;

		if(caza.giro_tren_d<0)
			caza.giro_tren_d=0;						

		break;
	} 	

	case 'B':{
		indice=(indice+1)%14;
		cout <<"La articulacion elegida es: ";
		switch(indice){
			case 0:
				cout <<"Giro de la aeronave en el eje x" <<endl;
				break;

			case 1:
				cout <<"Giro de la aeronave en el eje y" <<endl;
				break;

			case 2:
				cout <<"Giro de la aeronave en el eje z" <<endl;
				break;

			case 3:
				cout <<"Giro de los frenos aereos traseros" <<endl;
				break;

			case 4:
				cout <<"Giro en el eje x del tren de aterrizaje trasero" <<endl;
				break;

			case 5:
				cout <<"Giro en el eje y del tren de aterrizaje trasero" <<endl;
				break;

			case 6:
				cout <<"Giro del tren delantero" <<endl;
				break;

			case 7:
				cout <<"Giro de la ventana" <<endl;
				break;

			case 8:
				cout <<"Giro del flap" <<endl;
				break;

			case 9:
				cout <<"Movimiento del flap" <<endl;
				break;

			case 10:
				cout <<"Giro de las alas principales" <<endl;
				break;

			case 11:
				cout <<"Giro de los frenos aereos delanteros" <<endl;
				break;

			case 12:
				cout <<"Giro del timon" <<endl;
				break;

			case 13:
				cout <<"Giro de las alas traseras" <<endl;
				break;

			default: exit(-1); break;
		}
		break;
	}

		case 'N':{
			if(caza.factor_mult[indice]>0.2)
				caza.factor_mult[indice]-=0.1;

			cout <<"El valor de la variable es: " <<caza.constantes_animacion[indice]*caza.factor_mult[indice] <<endl;
			break;
		}

		case 'M':{
			caza.factor_mult[indice]+=0.1;

			cout <<"El valor de la variable es: " <<caza.constantes_animacion[indice]*caza.factor_mult[indice] <<endl;
			break;			
		}

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
	/*
	
	cout <<"******************************************************************" <<endl;
	cout <<"******************************************************************" <<endl;
	cout <<"** Controles: " <<endl;
	cout <<"** Mover aeronave sobre eje x: W/S" <<endl;
	cout <<"** Mover aeronave sobre eje y: Z/X" <<endl;
	cout <<"** Mover aeronave sobre eje z: A/D" <<endl;
	cout <<"** Mover ventana de cabina: F1/F2" <<endl;
	cout <<"** Mover flaps: F3/F4" <<endl;
	cout <<"** Mover alas principales (subsonico/supersonico): F5/F6" <<endl;
	cout <<"** Mover frenos aereos delantero: F7/F8" <<endl;
	cout <<"** Mover timon de la aeronave: F9/F10" <<endl;
	cout <<"** Mover ala trasera: F11/F12" <<endl;
	cout <<"** Mover frenos aereos traseros: G/T" <<endl;
	cout <<"** Mover tren de aterrizaje: H/Y" <<endl;
	cout <<"** Cambiar a pintado especial: 6" <<endl;
	cout <<"** Cambiar a pintado normal: 5" <<endl;
	cout <<"** Activar animacion: 9" <<endl;
	cout <<"** Desactivar animacion: 0" <<endl;	
	cout <<"******************************************************************" <<endl;
	cout <<"******************************************************************" <<endl;
*/
	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
		case GLUT_KEY_F1: {
			caza.giro_ventana+=caza.constantes_animacion[7]*caza.factor_mult[7]; 

			if(caza.giro_ventana>caza.max_giro_ventana)
				caza.giro_ventana=caza.max_giro_ventana;
				
			break;
		}
		case GLUT_KEY_F2:{
			caza.giro_ventana-=caza.constantes_animacion[7]*caza.factor_mult[7]; 
			
			if(caza.giro_ventana<caza.min_giro_ventana)
				caza.giro_ventana=caza.min_giro_ventana;

			break;

		} 		


		case GLUT_KEY_F3: {
			caza.flap_giro+=caza.constantes_animacion[8]*caza.factor_mult[8]; 

			caza.flap_trans+=caza.constantes_animacion[9]*caza.factor_mult[9];

			if(caza.flap_trans>caza.max_flap_trans)
				caza.flap_trans=caza.max_flap_trans;

			if(caza.flap_giro>caza.max_flap_giro)
				caza.flap_giro=caza.max_flap_giro;

						
			break;
		}
		case GLUT_KEY_F4:{
			caza.flap_giro-=caza.constantes_animacion[8]*caza.factor_mult[8]; 
			caza.flap_trans-=caza.constantes_animacion[9]*caza.factor_mult[9];

			if(caza.flap_trans<0)
				caza.flap_trans=0;

			if(caza.flap_giro<0)
				caza.flap_giro=0;

			break;
		} 					

		case GLUT_KEY_F5: {
			caza.angulo_alas+=caza.constantes_animacion[10]*caza.factor_mult[10]; 

			if(caza.angulo_alas>caza.max_angulo_alas)
				caza.angulo_alas=caza.max_angulo_alas;

				
			break;
		}
		case GLUT_KEY_F6:{
			caza.angulo_alas-=caza.constantes_animacion[10]*caza.factor_mult[10]; 
			
			if(caza.angulo_alas<0)
				caza.angulo_alas=0;

			break;
		}


		case GLUT_KEY_F7: {
			caza.giro_frenos_l+=caza.constantes_animacion[11]*caza.factor_mult[11]; 
			caza.giro_frenos_r+=caza.constantes_animacion[11]*caza.factor_mult[11]; 

			if(caza.giro_frenos_l>caza.max_giro_frenos)
				caza.giro_frenos_l=caza.giro_frenos_r=caza.max_giro_frenos;

			break;
		}
		case GLUT_KEY_F8:{
			caza.giro_frenos_l-=caza.constantes_animacion[11]*caza.factor_mult[11]; 
			caza.giro_frenos_r-=caza.constantes_animacion[11]*caza.factor_mult[11];
			
			if(caza.giro_frenos_l<0)
				caza.giro_frenos_l=caza.giro_frenos_r=0;

			break;
		} 	

		case GLUT_KEY_F9: {
			caza.timon_giro+=caza.constantes_animacion[12]*caza.factor_mult[12]; 

							if(caza.timon_giro>caza.max_timon_giro){
								caza.timon_giro=caza.max_timon_giro;
							}
								
							break;
		}
		case GLUT_KEY_F10:{
			caza.timon_giro-=caza.constantes_animacion[12]*caza.factor_mult[12]; 
			
			if(caza.timon_giro<-caza.max_timon_giro){
				caza.timon_giro=-caza.max_timon_giro;
			}

			break;

		} 	


		case GLUT_KEY_F11: {
			caza.angulo_trasero_l+=caza.constantes_animacion[13]*caza.factor_mult[13]; 
			caza.angulo_trasero_r+=caza.constantes_animacion[13]*caza.factor_mult[13]; 

							if(caza.angulo_trasero_l>caza.max_angulo_trasero)
								caza.angulo_trasero_l=caza.max_angulo_trasero;
								

							if(caza.angulo_trasero_r>caza.max_angulo_trasero)
								caza.angulo_trasero_r=caza.max_angulo_trasero;							
							break;
		}
		case GLUT_KEY_F12:{
			caza.angulo_trasero_l-=caza.constantes_animacion[13]*caza.factor_mult[13]; 
			caza.angulo_trasero_r-=caza.constantes_animacion[13]*caza.factor_mult[13]; 
			
			if(caza.angulo_trasero_r<-caza.max_angulo_trasero)
				caza.angulo_trasero_r=-caza.max_angulo_trasero;

			if(caza.angulo_trasero_l<-caza.max_angulo_trasero)
				caza.angulo_trasero_l=-caza.max_angulo_trasero;

			break;

		} 	

		
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


