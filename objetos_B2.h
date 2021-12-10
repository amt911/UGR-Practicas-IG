//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID, SOLID_ILLUMINATED_FLAT, SOLID_ILLUMINATED_GOURAUD, SELECT} _modo;
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
// clase luces
//*************************************************************************

class Luces{
	private:
		float luz[4], posicion[4];
		const float desV[4]={0, 0, 0, 1};
		bool desactivado=false;
	public:
		Luces()=default;
		Luces(float *luz, float *pos){
			for(int i=0; i<4; i++){
				this->luz[i]=luz[i];
				posicion[i]=pos[i];
			}
		}
		Luces(float l1, float l2, float l3, float l4, float p1, float p2, float p3, float p4){
			luz[0]=l1;
			luz[1]=l2;
			luz[2]=l3;
			luz[3]=l4;

			posicion[0]=p1;
			posicion[1]=p2;
			posicion[2]=p3;
			posicion[3]=p4;

		}

		float getLuz(int i){
			if(desactivado)
				return 0;

			return luz[i];
		}

		float getPosicion(int i){
			return posicion[i];
		}

		void setLuz(int i, float valor){
			luz[i]=valor;
		}
		void setPosicion(int i, float valor){
			posicion[i]=valor;
		}

		void setDesactivado(bool v){
			desactivado=v;
		}

		bool getDesactivado() const{
			return desactivado;
		}

		const float *getLuzVector() const{
			if(desactivado)
				return desV;

			return luz;
		}

		const float *getPosicionVector() const{
			return posicion;
		}
};


//*************************************************************************
// clase materiales
//*************************************************************************

class Materiales{
	private:
	_vertex4f ambiente;     //coeficientes ambiente y difuso
	_vertex4f especular;           //coeficiente especular
	_vertex4f difusa;
	float brillo;                  //exponente del brillo 

	public:
	enum tipoMaterial{LATON, BRONCE, BRONCE_PULIDO, CROMADO, COBRE, COBRE_PULIDO, ORO, ORO_PULIDO, TIN, PLATA, PLATA_PULIDA,
	ESMERALDA, JADE, OBSIDIANA, PERLADO, RUBI, TURQUESA, PLASTICO, GOMA, ALUMINIO, CRISTAL};

	tipoMaterial mat;

	Materiales(tipoMaterial material);
	const _vertex4f &getAmbiente() const;
	const _vertex4f &getEspecular() const;
	const _vertex4f &getDifusa() const;

	void setAmbiente(double v1, double v2, double v3);
	void setEspecular(double v1, double v2, double v3);
	void setDifusa(double v1, double v2, double v3);
	void setBrillo(double valor);

	void setValores(tipoMaterial tipo);

	const float getBrillo();
};



//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
	public:

		_triangulos3D(Materiales::tipoMaterial m=Materiales::LATON);
	void 	draw_aristas(float r, float g, float b, int grosor);
	void    draw_solido(float r, float g, float b);
	void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
	void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, bool selec=false);
	void draw_seleccion(int r, int g, int b);
	//Practica 4
	void 	draw_iluminacion_plana( bool selec=false);		//Por ahora asi
	void 	draw_iluminacion_suave( bool selec=false);		//Por ahora asi

	void	calcular_normales_caras();
	virtual void 	calcular_normales_vertices();
	//void calcular_normal_cara(int i);
	vector<_vertex3i> caras;

	//Practica 4
	vector<_vertex3f> normales_caras;
	vector<_vertex3f> normales_vertices;

	bool b_normales_caras;
	bool b_normales_vertices;
	Materiales material;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:
	_cubo(float tam=2, Materiales::tipoMaterial tipo=Materiales::CROMADO);

	//Practica 5

	void seleccion(){
		int c;

			_triangulos3D aux;
			aux.vertices=vertices;
			aux.caras=caras;

			for(int i=0; i<caras.size(); i++){
					int c=color_selec[0][i];
					_triangulos3D aux;
					aux.vertices=vertices;
					aux.caras.push_back(caras[i]);

					aux.draw(SELECT, c, c, c, c, c, c, 1);
			}
	}

	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, bool s = false)
	{
		float r_p, g_p, b_p;

		r_p = color_pick[0];
		g_p = color_pick[1];
		b_p = color_pick[2];

		_triangulos3D aux;
		aux.vertices = vertices;

		if (modo != SOLID_ILLUMINATED_FLAT and modo != SOLID_ILLUMINATED_GOURAUD)
		{
			for (int i = 0; i < caras.size(); i++)
			{

				aux.caras.clear();
				aux.caras.push_back(caras[i]);

				if (activo[i] == 1)
					aux.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, true);

				else
				{
					if (modo == SOLID_CHESS)
					{
						if (i % 2 == 0)
							aux.draw(modo, r1, g1, b1, r1, g1, b1, grosor, s);

						else
							aux.draw(modo, r2, g2, b2, r2, g2, b2, grosor, s);
					}

					else
						aux.draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
				}
			}
		}
		else
		{
			_triangulos3D a(material.mat), noa(material.mat);
			a.vertices = noa.vertices = vertices;

			for (int i = 0; i < caras.size(); i++)
			{
				if (activo[i] == 1)
					a.caras.push_back(caras[i]);

				else
					noa.caras.push_back(caras[i]);
			}

			if (a.caras.size() > 0)
				a.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, true);

			noa.draw(modo, r1, g1, b1, r1, g1, b1, grosor, s);
		}
	}

	float  color_pick[3];
	vector<int>    color_selec[3];
	vector<int>    activo;
	int    triangulos;
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75, Materiales::tipoMaterial tipo=Materiales::CROMADO);


	//Practica 5

	void seleccion(){
		int c;

			_triangulos3D aux;
			aux.vertices=vertices;
			aux.caras=caras;

			for(int i=0; i<caras.size(); i++){
					int c=color_selec[0][i];
					_triangulos3D aux;
					aux.vertices=vertices;
					aux.caras.push_back(caras[i]);

					aux.draw(SELECT, c, c, c, c, c, c, 1);
			}
	}

	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, bool s=false){
		float r_p, g_p, b_p;

		r_p = color_pick[0];
		g_p = color_pick[1];
		b_p = color_pick[2];

		_triangulos3D aux;
		aux.vertices = vertices;

		if (modo != SOLID_ILLUMINATED_FLAT and modo != SOLID_ILLUMINATED_GOURAUD)
		{
			for (int i = 0; i < caras.size(); i++)
			{

				aux.caras.clear();
				aux.caras.push_back(caras[i]);

				if (activo[i] == 1)
					aux.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, true);

				else
				{
					if (modo == SOLID_CHESS)
					{
						if (i % 2 == 0)
							aux.draw(modo, r1, g1, b1, r1, g1, b1, grosor, s);

						else
							aux.draw(modo, r2, g2, b2, r2, g2, b2, grosor, s);
					}

					else
						aux.draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
				}
			}
		}
		else
		{
			_triangulos3D a(material.mat), noa(material.mat);
			a.vertices = noa.vertices = vertices;

			for (int i = 0; i < caras.size(); i++)
			{
				if (activo[i] == 1)
					a.caras.push_back(caras[i]);

				else
					noa.caras.push_back(caras[i]);
			}

			if (a.caras.size() > 0)
				a.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, true);

			noa.draw(modo, r1, g1, b1, r1, g1, b1, grosor, s);
		}
	}

	float  color_pick[3];
	vector<int>    color_selec[3];
	vector<int>    activo;
	int    triangulos;
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
       _rotacion(Materiales::tipoMaterial tipo=Materiales::LATON);
//void  parametros(vector<_vertex3f> perfil1, int num1);
void  parametros(vector<_vertex3f> perfil1, int num1, Eje axis=y);

vector<_vertex3f> perfil; 
int num;






	//Practica 5

	void seleccion(){
		int c;

			_triangulos3D aux;
			aux.vertices=vertices;
			aux.caras=caras;

			for(int i=0; i<caras.size(); i++){
					int c=color_selec[0][i];
					_triangulos3D aux;
					aux.vertices=vertices;
					aux.caras.push_back(caras[i]);

					aux.draw(SELECT, c, c, c, c, c, c, 1);
			}
	}

	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, bool s=false){
		float r_p, g_p, b_p;

		r_p = color_pick[0];
		g_p = color_pick[1];
		b_p = color_pick[2];

		_triangulos3D aux;
		aux.vertices = vertices;

		if (modo != SOLID_ILLUMINATED_FLAT and modo != SOLID_ILLUMINATED_GOURAUD)
		{
			for (int i = 0; i < caras.size(); i++)
			{

				aux.caras.clear();
				aux.caras.push_back(caras[i]);

				if (activo[i] == 1)
					aux.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, true);

				else
				{
					if (modo == SOLID_CHESS)
					{
						if (i % 2 == 0)
							aux.draw(modo, r1, g1, b1, r1, g1, b1, grosor, s);

						else
							aux.draw(modo, r2, g2, b2, r2, g2, b2, grosor, s);
					}

					else
						aux.draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
				}
			}
		}
		else
		{
			_triangulos3D a(material.mat), noa(material.mat);
			a.vertices = noa.vertices = vertices;

			for (int i = 0; i < caras.size(); i++)
			{
				if (activo[i] == 1)
					a.caras.push_back(caras[i]);

				else
					noa.caras.push_back(caras[i]);
			}

			if (a.caras.size() > 0)
				a.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, true);

			noa.draw(modo, r1, g1, b1, r1, g1, b1, grosor, s);
		}
	}

	float  color_pick[3];
	vector<int>    color_selec[3];
	vector<int>    activo;
	int    triangulos;
};

//************************************************************************
// clase esfera
//************************************************************************

class _esfera: public _rotacion
{
	public:
	_esfera(int radio=1, int num_puntos=12, int num_rot=12, Eje axis=y, Materiales::tipoMaterial tipo=Materiales::CROMADO);
	void 	calcular_normales_vertices() override;
};

//************************************************************************
// clase cono
//************************************************************************

class _cono: public _rotacion
{
	public:
		_cono(double radio=1, double h=2, int num=12, Eje axis=y, Materiales::tipoMaterial tipo=Materiales::ORO);
};

//************************************************************************
// clase cilindro
//************************************************************************

class _cilindro: public _rotacion
{
	public:
		_cilindro(double radio=1, double h=2, int num=12, Eje axis=y, Materiales::tipoMaterial tipo=Materiales::ORO);
};

//************************************************************************
// clase ply_rot
//************************************************************************

class _ply_rot: public _objeto_ply
{
	public:
		_ply_rot(const char *file, int rot=3, Eje axis=y, Materiales::tipoMaterial tipo=Materiales::ORO);


	void seleccion(){
		int c;

			_triangulos3D aux;
			aux.vertices=vertices;
			aux.caras=caras;

			for(int i=0; i<caras.size(); i++){
					int c=color_selec[0][i];
					_triangulos3D aux;
					aux.vertices=vertices;
					aux.caras.push_back(caras[i]);

					aux.draw(SELECT, c, c, c, c, c, c, 1);
			}
	}


	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, bool s=false){
		float r_p, g_p, b_p;

		r_p = color_pick[0];
		g_p = color_pick[1];
		b_p = color_pick[2];

		_triangulos3D aux;
		aux.vertices = vertices;

		if (modo != SOLID_ILLUMINATED_FLAT and modo != SOLID_ILLUMINATED_GOURAUD)
		{
			for (int i = 0; i < caras.size(); i++)
			{

				aux.caras.clear();
				aux.caras.push_back(caras[i]);

				if (activo[i] == 1)
					aux.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, true);

				else
				{
					if (modo == SOLID_CHESS)
					{
						if (i % 2 == 0)
							aux.draw(modo, r1, g1, b1, r1, g1, b1, grosor, s);

						else
							aux.draw(modo, r2, g2, b2, r2, g2, b2, grosor, s);
					}

					else
						aux.draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
				}
			}
		}
		else
		{
			_triangulos3D a(material.mat), noa(material.mat);
			a.vertices = noa.vertices = vertices;

			for (int i = 0; i < caras.size(); i++)
			{
				if (activo[i] == 1)
					a.caras.push_back(caras[i]);

				else
					noa.caras.push_back(caras[i]);
			}

			if (a.caras.size() > 0)
				a.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, true);

			noa.draw(modo, r1, g1, b1, r1, g1, b1, grosor, s);
		}
	}

	float  color_pick[3];
	vector<int>    color_selec[3];
	vector<int>    activo;
	int    triangulos;


	private:
	Materiales material;
	vector<_vertex3f> perfil;
};


//************************************************************************
// caza
//************************************************************************

class _cuerpo: public _triangulos3D{
	public:
		_cuerpo(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo), 
		nariz(CONO_RADIO, CONO_H, NUM, eje,  tipo), nariz_curva(ES_RADIO, NUM, NUM, eje, tipo){}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);

	double y=1.95865;

	private:
	const int CUBO_TAM=2;
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;
	const double CONO_RADIO=1, CONO_H=2;
	const double ES_RADIO=1;

	protected:
	vector<_cubo> base;
	vector<_cilindro> esquinas;
	_cono nariz;
	_esfera nariz_curva;


public:
};

//************************************************************************

class _alas: public _triangulos3D{
	public:
		_alas(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo){}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

	private:
	const int CUBO_TAM=2;
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;
	const double ES_RADIO=1;

	protected:
	vector<_cubo> base;
	vector<_cilindro> filos;
	vector<_esfera> esquinas;

};


//************************************************************************

//************************************************************************

class _ala_izda: public _triangulos3D{
	public:
		_ala_izda(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo),
		esquina(ES_RADIO, NUM, NUM, eje, tipo){}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

		const double angulo_y=23.5;
		const double angulo_z=-4.6;
		const double x=1.3854;

	private:
	const int CUBO_TAM=2;
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;
	const double ES_RADIO=1;

	protected:
	vector<_cubo> base;
	vector<_cilindro> filos;
	_esfera esquina;

};

class _ala_dcha: public _triangulos3D{
	public:
		_ala_dcha(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo),
		esquina(ES_RADIO, NUM, NUM, eje, tipo){}

		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

	const double angulo_y=-23.5;
	const double angulo_z=4.6;
	const double x=-1.3854;

	private:
	const int CUBO_TAM=2;
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;
	const double ES_RADIO=1;

	protected:
	vector<_cubo> base;
	vector<_cilindro> filos;
	_esfera esquina;

};


//************************************************************************
class _ala_td: public _triangulos3D{
	public:
		_ala_td(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo),
		esquina(ES_RADIO, NUM, NUM, eje, tipo){}

		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

	const double x=-1.0603;
	const double y=1.984261;
	const double z=-4.66768;

	const double intermedio_y=0.025641;
	const double y_i_f=y-intermedio_y;

	private:
	const int CUBO_TAM=2;
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;
	const double ES_RADIO=1;

	protected:
	vector<_cubo> base;
	vector<_cilindro> filos;
	_esfera esquina;	
};




class _ala_ti: public _triangulos3D{
	public:
		_ala_ti(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo),
		esquina(ES_RADIO, NUM, NUM, eje, tipo){}

		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

	const double x=1.0603;
	const double y=1.984261;
	const double z=-4.66768;

	//const double intermedio_y=0.025641;
	//const double y_i_f=y-intermedio_y;


	private:
	const int CUBO_TAM=2;
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;
	const double ES_RADIO=1;

	protected:
	vector<_cubo> base;
	vector<_cilindro> filos;
	_esfera esquina;	
};
//************************************************************************

class _ventana_movil: public _triangulos3D{
	public:
		_ventana_movil(Materiales::tipoMaterial tipo=Materiales::PERLADO):_triangulos3D(tipo),
		pico(CONO_RADIO, CONO_H, NUM, eje, tipo){}

		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		
		
		double x=0;
		double y=2.99002;
		double z=1.60318;
		//double intermedio_y=1.03152;
		//double y_i_f=y-intermedio_y;	//Lo que hay que subir desde el intermedio hasta el final

	private:
	const int CUBO_TAM=2;
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;
	const double CONO_RADIO=1, CONO_H=2;

	protected:
	vector<_cubo> base;
	vector<_cilindro> filos;
	_cono pico;	
};


//************************************************************************

class _ventana_fija: public _triangulos3D{
	public:
		_ventana_fija(Materiales::tipoMaterial tipo=Materiales::PERLADO):_triangulos3D(tipo),
		filos(CIL_RAD, CIL_H, NUM, eje, tipo), pico(CONO_RADIO, CONO_H, NUM, eje, tipo){}

		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

		double x=0;
		double y=2.99002;
		double z=1.60318;

	private:
	const int CUBO_TAM=2;
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;
	const double CONO_RADIO=1, CONO_H=2;

	protected:
	vector<_cubo> base;
	_cilindro filos;
	_cono pico;	
};


//************************************************************************

class _flaps: public _triangulos3D{
	public:
		_flaps(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo){}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

	private:
	const int CUBO_TAM=2;

	protected:
	vector<_cubo> flaps;
};


//************************************************************************
class _flap: public _triangulos3D{
	public:
		_flap(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo), flap(CUBO_TAM, tipo){}

		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

		const double angulo_y_r=14.6;
		const double angulo_z_r=-4.6;

		const double z=-1.7697;

		const double mover_centro_x_r=-3.5797;
		const double mover_centro_z=0.26;
		const double mover_centro_y=-2.1596;

	private:
	const int CUBO_TAM=2;

		//const double intermedio_y=1.95865;
	protected:
	_cubo flap;
};


//************************************************************************



class _frenos_delanteros: public _triangulos3D{
	public:
		_frenos_delanteros(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo){}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

	private:
	const int CUBO_TAM=2;

	protected:
	vector<_cubo> base;
};

//************************************************************************

class _freno_individual: public _triangulos3D{
	public:
		_freno_individual(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo), base(CUBO_TAM, tipo){}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

		const double y=2.2518;
		//const double intermedio_y=0.29316;
		//const double y_i_f=y-intermedio_y;
		const double freno_delantero_angulo_y=-15.9;
		const double freno_delantero_angulo_z=4.6;

	private:
	const int CUBO_TAM=2;

	protected:
	_cubo base;
};


//************************************************************************

class _timon: public _triangulos3D{
	public:
		_timon(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo){}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		


		const double y=3.579368;
		const double z=-5.78512;

	private:
	const int CUBO_TAM=2;

	protected:
	vector<_cubo> base;
};


//************************************************************************

class _frenos_traseros: public _triangulos3D{
	public:
		_frenos_traseros(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo){}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

	private:
	const int CUBO_TAM=2;

	protected:
	vector<_cubo> base;
};


//************************************************************************

class _freno_trasero_individual: public _triangulos3D{
	public:
		_freno_trasero_individual(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo), base(CUBO_TAM, tipo){}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

		const double angulo_z_l=-23.5;
		const double x=0.7922;
		const double y=2.3859;
		const double z=-2.9941;


		const double centro_z=0.64;	//Para centrar la figura

	private:
	const int CUBO_TAM=2;

	protected:
	_cubo base;
};



//************************************************************************

class _tren_trasero: public _triangulos3D{
	public:
		_tren_trasero(Materiales::tipoMaterial tipo=Materiales::GOMA):_triangulos3D(tipo){}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

		const double x_r=-0.89669;
		const double y_r=1.30617;
		const double z_r=-1.107;


	private:
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;

	protected:
	vector<_cilindro> piezas;
};



//************************************************************************

class _tren_delantero: public _triangulos3D{
	public:
		_tren_delantero(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo){
			
		}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

		const double y=1.28617;
		const double z=3.5297;


	void seleccion(){
  //Brazo 0.7 0.4
  glPushMatrix();
  glTranslatef(0, -0.55, 0);
  glScalef(0.05, 0.57, 0.05);
    piezas[piezas.size()-1].seleccion();
  glPopMatrix();

  //Ruedas 0.24 0.12
  //Izquierda
  //No hay otra forma de hacer el material que creando otra pieza

  glPushMatrix();
  glTranslatef(-0.1543, -1.1262, -0.006611);
  glRotatef(90, 0, 0, 1);
  glScalef(0.2, 0.12, 0.2);
    piezas[piezas.size()-1].seleccion();
  glPopMatrix();

  //Derecha
  //No hay otra forma de hacer el material que creando otra pieza

  glPushMatrix();
  glTranslatef(0.1543, -1.1262, -0.006611);
  glRotatef(90, 0, 0, 1);
  glScalef(0.2, 0.12, 0.2);
    piezas[piezas.size()-1].seleccion();
  glPopMatrix();		
	}






	float  color_pick[3];
	vector<int>    color_selec[3];
	vector<int>    activo;
	int    triangulos;


	private:
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;

	protected:
	vector<_cilindro> piezas;
};



//************************************************************************

class _tornado{
	public:
float  color_pick[3];
int    color_selec[3][17];
int    activo[17];
const int    piezas=17;
	/*
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
	_tren_delantero tren_d;*/

		_tornado(){
			for(int i=0; i<50; i++)
				actos[i]=false;
		}

		_tornado(Materiales::tipoMaterial mat): cuerpo(mat), ala_izda(mat), ala_dcha(mat), td(mat), ti(mat),
		ventana_fija(mat), ventana_movil(mat), flap(mat), frenos(mat), ft(mat), timon(mat), tt(mat), tren_d(mat){
			for(int i=0; i<50; i++)
				actos[i]=false;		

			int c=14;

			color_pick[0]=1.0;
			color_pick[1]=0.0;
			color_pick[2]=0.0; 
			for (int i=0;i<piezas;i++)
			{activo[i]=0;
			color_selec[0][i]=color_selec[1][i]=color_selec[2][i]=c;
			c=c+14;
			}			
			
		}


		void setMaterial(Materiales::tipoMaterial tipo){
			cuerpo.material=ala_izda.material=ala_dcha.material=td.material=ti.material=ventana_fija.material=ventana_movil.material=flap.material=frenos.material=
			ft.material=ft.material=timon.material=tt.material=tren_d.material=Materiales(tipo);	
		}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

		//Cuando se corta la animacion es necesario restaurar todo a su estado original
		void limpiar_actos(){
			for(int i=0; i<50; i++)
				actos[i]=false;

			giro_ventana=giro_aeronave_x=giro_aeronave_y=giro_aeronave_z=
			timon_giro=angulo_trasero_l=angulo_trasero_r=angulo_alas=
			giro_frenos_l=giro_frenos_r=flap_giro=flap_trans=ft_giro=
			tt_giro_x=tt_giro_y=giro_tren_d=0;

			
		}

		void seleccion();

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