//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID, SOLID_ILLUMINATED_FLAT, SOLID_ILLUMINATED_GOURAUD} _modo;
enum Eje{x, y, z};
enum Tipo{NORMAL, ESPECIAL};

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

//Practica 4
void 	draw_iluminacion_plana( );
void 	draw_iluminacion_suave( );

void	calcular_normales_caras();
void 	calcular_normales_vertices();
//void calcular_normal_cara(int i);
vector<_vertex3i> caras;

//Practica 4
vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;

bool b_normales_caras;
bool b_normales_vertices;

_vertex4f ambiente_difusa;     //coeficientes ambiente y difuso
_vertex4f especular;           //coeficiente especular
_vertex4f difusa;
float brillo;                  //exponente del brillo 


void prueba(){

}
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=2);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
//void  parametros(vector<_vertex3f> perfil1, int num1);
void  parametros(vector<_vertex3f> perfil1, int num1, Eje axis=y);

vector<_vertex3f> perfil; 
int num;
};

//************************************************************************
// clase esfera
//************************************************************************

class _esfera: public _rotacion
{
	public:
	_esfera(int radio=1, int num_puntos=12, int num_rot=12, Eje axis=y);
};

//************************************************************************
// clase cono
//************************************************************************

class _cono: public _rotacion
{
	public:
		_cono(double radio=1, double h=2, int num=12, Eje axis=y);
};

//************************************************************************
// clase cilindro
//************************************************************************

class _cilindro: public _rotacion
{
	public:
		_cilindro(double radio=1, double h=2, int num=12, Eje axis=y);
};

//************************************************************************
// clase ply_rot
//************************************************************************

class _ply_rot: public _objeto_ply
{
	public:
		_ply_rot(char *file, int rot=3, Eje axis=y);

	private:
	vector<_vertex3f> perfil;
};


//************************************************************************
// caza
//************************************************************************

class _cuerpo: public _triangulos3D{
	public:
		_cuerpo();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);

	double y=1.95865;

	protected:
	vector<_cubo> base;
	vector<_cilindro> esquinas;
	_cono nariz;
	_esfera nariz_curva;
};

//************************************************************************

class _alas: public _triangulos3D{
	public:
		_alas();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

	protected:
	vector<_cubo> base;
	vector<_cilindro> filos;
	vector<_esfera> esquinas;

};


//************************************************************************

//************************************************************************

class _ala_izda: public _triangulos3D{
	public:
		_ala_izda()=default;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

		const double angulo_y=23.5;
		const double angulo_z=-4.6;
		const double x=1.3854;

	protected:
	vector<_cubo> base;
	vector<_cilindro> filos;
	_esfera esquina;

};

class _ala_dcha: public _triangulos3D{
	public:
		_ala_dcha()=default;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

	const double angulo_y=-23.5;
	const double angulo_z=4.6;
	const double x=-1.3854;

	protected:
	vector<_cubo> base;
	vector<_cilindro> filos;
	_esfera esquina;

};


//************************************************************************
class _ala_td: public _triangulos3D{
	public:
		_ala_td(){}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

	const double x=-1.0603;
	const double y=1.984261;
	const double z=-4.66768;

	const double intermedio_y=0.025641;
	const double y_i_f=y-intermedio_y;

	protected:
	vector<_cubo> base;
	vector<_cilindro> filos;
	_esfera esquina;	
};




class _ala_ti: public _triangulos3D{
	public:
		_ala_ti(){}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

	const double x=1.0603;
	const double y=1.984261;
	const double z=-4.66768;

	//const double intermedio_y=0.025641;
	//const double y_i_f=y-intermedio_y;

	protected:
	vector<_cubo> base;
	vector<_cilindro> filos;
	_esfera esquina;	
};
//************************************************************************

class _ventana_movil: public _triangulos3D{
	public:
		_ventana_movil()=default;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		
		
		double x=0;
		double y=2.99002;
		double z=1.60318;
		//double intermedio_y=1.03152;
		//double y_i_f=y-intermedio_y;	//Lo que hay que subir desde el intermedio hasta el final

	protected:
	vector<_cubo> base;
	vector<_cilindro> filos;
	//_esfera esquina;	
	_cono pico;	
};


//************************************************************************

class _ventana_fija: public _triangulos3D{
	public:
		_ventana_fija()=default;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

		double x=0;
		double y=2.99002;
		double z=1.60318;

	protected:
	vector<_cubo> base;
	_cilindro filos;
	_cono pico;	
};


//************************************************************************

class _flaps: public _triangulos3D{
	public:
		_flaps()=default;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

	protected:
	vector<_cubo> flaps;
};


//************************************************************************
class _flap: public _triangulos3D{
	public:
		_flap()=default;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

		const double angulo_y_r=14.6;
		const double angulo_z_r=-4.6;

		const double z=-1.7697;

		const double mover_centro_x_r=-3.5797;
		const double mover_centro_z=0.26;
		const double mover_centro_y=-2.1596;

		//const double intermedio_y=1.95865;
	protected:
	_cubo flap;
};


//************************************************************************



class _frenos_delanteros: public _triangulos3D{
	public:
		_frenos_delanteros()=default;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

	protected:
	vector<_cubo> base;
};

//************************************************************************

class _freno_individual: public _triangulos3D{
	public:
		_freno_individual()=default;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

		const double y=2.2518;
		//const double intermedio_y=0.29316;
		//const double y_i_f=y-intermedio_y;
		const double freno_delantero_angulo_y=-15.9;
		const double freno_delantero_angulo_z=4.6;

	protected:
	_cubo base;
};


//************************************************************************

class _timon: public _triangulos3D{
	public:
		_timon()=default;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		


		const double y=3.579368;
		const double z=-5.78512;

		//const double intermedio_y=1.620681;
		//const double y_i_f=y-intermedio_y;	//Lo que hay que subir desde el intermedio hasta el final

		//double intermedio_x=1.03152;
		//double x_i_f=x-intermedio_x;	//Lo que hay que subir desde el intermedio hasta el final		
	protected:
	vector<_cubo> base;
};


//************************************************************************

class _frenos_traseros: public _triangulos3D{
	public:
		_frenos_traseros()=default;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

	protected:
	vector<_cubo> base;
};


//************************************************************************

class _freno_trasero_individual: public _triangulos3D{
	public:
		_freno_trasero_individual()=default;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

		const double angulo_z_l=-23.5;
		const double x=0.7922;
		const double y=2.3859;
		const double z=-2.9941;


		const double centro_z=0.64;	//Para centrar la figura



	protected:
	_cubo base;
};



//************************************************************************

class _tren_trasero: public _triangulos3D{
	public:
		_tren_trasero()=default;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

		const double x_r=-0.89669;
		const double y_r=1.30617;
		const double z_r=-1.107;

	protected:
	vector<_cilindro> piezas;
};



//************************************************************************

class _tren_delantero: public _triangulos3D{
	public:
		_tren_delantero()=default;
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

		const double y=1.28617;
		const double z=3.5297;

	protected:
	vector<_cilindro> piezas;
};



//************************************************************************

class _tornado: public _triangulos3D{
	public:
		_tornado(){
			for(int i=0; i<50; i++)
				actos[i]=false;
		}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo);		

		//Cuando se corta la animacion es necesario restaurar todo a su estado original
		void limpiar_actos(){
			for(int i=0; i<50; i++)
				actos[i]=false;

			giro_ventana=giro_aeronave_x=giro_aeronave_y=giro_aeronave_z=
			timon_giro=angulo_trasero_l=angulo_trasero_r=angulo_alas=
			giro_frenos_l=giro_frenos_r=flap_giro=flap_trans=ft_giro=
			tt_giro_x=tt_giro_y=giro_tren_d=0;
		}

	/**
	 * 0: giro_aeronave_x
	 * 1: giro_aeronave_y
	 * 2: giro_aeronave_z
	 * 3: ft_giro
	 * 4/5/6: tt_giro (tt_giro_x/tt_giro_y/giro_tren_d)
	 * 7: giro_ventana
	 * 8/9: flap_giro (flap_giro / flap_trans)
	 * 10: angulo_alas
	 * 11: giro_frenos (en general, solo un index)
	 * 12: timon_giro
	 * 13: angulo_trasero (en general, solo un index)
	 * 
	 */

	const double constantes_animacion[14]={1, 1, 1, 1, 1, 1, 1, 1, 1, 0.01, 1, 1, 1, 1};
	double factor_mult[14]={1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};


	double giro_ventana=0;
	const double max_giro_ventana=45;
	const double min_giro_ventana=0;

	double giro_aeronave_x=0;

	double giro_aeronave_y=0;

	double giro_aeronave_z=0;
	
	
	double timon_giro=0;
	const double max_timon_giro=45;

	double angulo_trasero_r=0;
	double angulo_trasero_l=0;
	const double max_angulo_trasero=45;



	double angulo_alas=0;
	double max_angulo_alas=40;


	double giro_frenos_l=0;
	double giro_frenos_r=0;
	const double max_giro_frenos=60;


	double flap_giro=0;
	const double max_flap_giro=45;

	double flap_trans=0;
	const double max_flap_trans=0.25;


	double ft_giro=0;
	const double max_ft_giro=60;


	double tt_giro_x=0;
	const double max_tt_giro_x=120;
	double tt_giro_y=0;
	const double max_tt_giro_y=30;

	double giro_tren_d=0;
	const double max_giro_tren_d=100;


	bool actos[50];

	protected:
	_cuerpo cuerpo;
	_ala_izda ala_izda;
	_ala_dcha ala_dcha;
	_ala_td td;
	_ala_ti ti;
	_ventana_fija ventana_fija;
	_ventana_movil ventana_movil;
	_flap flap;
	_freno_individual frenos;
	_freno_trasero_individual ft;
	_timon timon;
	_tren_trasero tt;
	_tren_delantero tren_d;
};