//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;
enum Eje{x, y, z};

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

vector<_vertex3i> caras;
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
	_esfera(int radio=1, int num_puntos=6, int num_rot=5, Eje axis=y);
};

//************************************************************************
// clase cono
//************************************************************************

class _cono: public _rotacion
{
	public:
		_cono(double radio=1, double h=2, int num=12, Eje axis=z);
};

//************************************************************************
// clase cilindro
//************************************************************************

class _cilindro: public _rotacion
{
	public:
		_cilindro(double radio=1, double h=2, int num=12, Eje axis=z);
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

class _cuerpo{
	public:
		_cuerpo();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	float altura, anchura;

	protected:
	vector<_cubo> base;
	vector<_cilindro> esquinas;
	_cono nariz;
};