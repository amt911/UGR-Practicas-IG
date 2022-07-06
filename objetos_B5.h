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
		Luces(float *luz, float *pos);
		Luces(float l1, float l2, float l3, float l4, float p1, float p2, float p3, float p4);
		float getLuz(int i);
		float getPosicion(int i);
		void setLuz(int i, float valor);
		void setPosicion(int i, float valor);
		void setDesactivado(bool v);
		bool getDesactivado() const;
		const float *getLuzVector() const;
		const float *getPosicionVector() const;

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
	void seleccion();
	void RGB_Suma(int *v, int salto);
	void recolorea(int *v, int salto);
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, bool s = false);

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

	void seleccion();
	void RGB_Suma(int *v, int salto);

	void recolorea(int *v, int salto);

	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, bool s=false){
		float r_p, g_p, b_p;

		r_p = color_pick[0];
		g_p = color_pick[1];
		b_p = color_pick[2];

		_triangulos3D aux;
		aux.vertices = vertices;

		if (modo != SOLID_ILLUMINATED_FLAT and modo != SOLID_ILLUMINATED_GOURAUD)
		{
			for (long unsigned int i = 0; i < caras.size(); i++)
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

			for (long unsigned int i = 0; i < caras.size(); i++)
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

			_triangulos3D aux;
			aux.vertices=vertices;
			aux.caras=caras;

			for(long unsigned int i=0; i<caras.size(); i++){
					int c[3]={color_selec[0][i], color_selec[1][i], color_selec[2][i]};
					_triangulos3D aux;
					aux.vertices=vertices;
					aux.caras.push_back(caras[i]);

					aux.draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1);
			}
	}

	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}
	void recolorea(int *v, int salto){
		//int c=empieza;


		for (long unsigned int i = 0; i < caras.size(); i++)
		{
				//piezas[i].color_selec[0][j] = piezas[i].color_selec[1][j] = piezas[i].color_selec[2][j] = c;
				//c = (c + salto) % 255;
				color_selec[0][i]=v[0];
				color_selec[1][i]=v[1];
				color_selec[2][i]=v[2];

				RGB_Suma(v, salto);
				//c+=salto;
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
			for (long unsigned int i = 0; i < caras.size(); i++)
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

			for (long unsigned int i = 0; i < caras.size(); i++)
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

			_triangulos3D aux;
			aux.vertices=vertices;
			aux.caras=caras;

			for(long unsigned int i=0; i<caras.size(); i++){
					int c[3]={color_selec[0][i], color_selec[1][i], color_selec[2][i]};
					_triangulos3D aux;
					aux.vertices=vertices;
					aux.caras.push_back(caras[i]);

					aux.draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1);
			}
	}

	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}
	void recolorea(int *v, int salto){
		//int c=empieza;


		for (long unsigned int i = 0; i < caras.size(); i++)
		{
				//piezas[i].color_selec[0][j] = piezas[i].color_selec[1][j] = piezas[i].color_selec[2][j] = c;
				//c = (c + salto) % 255;
				color_selec[0][i]=v[0];
				color_selec[1][i]=v[1];
				color_selec[2][i]=v[2];

				RGB_Suma(v, salto);
				//c+=salto;
				//cout <<v[0] <<"\t" <<v[1] <<"\t" <<v[2] <<endl;
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
			for (long unsigned int i = 0; i < caras.size(); i++)
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

			for (long unsigned int i = 0; i < caras.size(); i++)
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
		nariz(CONO_RADIO, CONO_H, NUM, eje,  tipo), nariz_curva(ES_RADIO, NUM, NUM, eje, tipo){
			for(int i=0; i<16; i++)
				esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, tipo));

			for(int i=0; i<27; i++)
				base.push_back(_cubo(CUBO_TAM, tipo));

		}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);

	double y=1.95865;

	public:
	const int CUBO_TAM=2;
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;
	const double CONO_RADIO=1, CONO_H=2;
	const double ES_RADIO=1;

	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}

	void recolorea(int *v, int salto){
		for (long unsigned int i = 0; i < base.size(); i++)
		{
			for (long unsigned int j = 0; j < base[i].color_selec[0].size(); j++)
			{
				base[i].color_selec[0][j]=v[0];
				base[i].color_selec[1][j]=v[1];
				base[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}	

		for (long unsigned int i = 0; i < esquinas.size(); i++)
		{
			for (long unsigned int j = 0; j < esquinas[i].color_selec[0].size(); j++)
			{
				esquinas[i].color_selec[0][j]=v[0];
				esquinas[i].color_selec[1][j]=v[1];
				esquinas[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}

		for(int i=0; i<nariz.triangulos; i++){
				nariz.color_selec[0][i]=v[0];
				nariz.color_selec[1][i]=v[1];
				nariz.color_selec[2][i]=v[2];

				RGB_Suma(v, salto);			
		}	

		for(int i=0; i<nariz_curva.triangulos; i++){
				nariz_curva.color_selec[0][i]=v[0];
				nariz_curva.color_selec[1][i]=v[1];
				nariz_curva.color_selec[2][i]=v[2];

				RGB_Suma(v, salto);			
		}			
	}

	bool algunoActivo() const{
		bool alguno_activo=false;

		for(auto it=base.cbegin(); it!=base.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}

		for(auto it=esquinas.cbegin(); it!=esquinas.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}

		for(int i=0; i<nariz.triangulos; i++){
			if(nariz.activo[i]==1)
				alguno_activo=true;
		}

		for(int i=0; i<nariz_curva.triangulos; i++){
			if(nariz_curva.activo[i]==1)
				alguno_activo=true;
		}

		return alguno_activo;
	}


	void seleccion(){
  glPushMatrix();
  glTranslatef(-0.9218, 0.1132, 1.4685);
  glRotatef(3.59, 1, 0, 0);
  glScalef(0.432, 0.406, 1);
  base[0].seleccion();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.9218, 0.1132, 1.4685);
  glRotatef(3.59, 1, 0, 0);
  glScalef(0.432, 0.406, 1);
  base[1].seleccion();
  glPopMatrix();


//Frame
  glPushMatrix();
  glTranslatef(0, -0.2509, 1.5759);
  glScalef(0.59, 0.302, 3.62);
  base[2].seleccion();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0.0721, 3.468);
  glRotatef(3.59, 1, 0, 0);
  glScalef(0.59, 0.116, 1.031);
  base[3].seleccion();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0.1484, 0.8318);
  glRotatef(4.92, 1, 0, 0);
  glScalef(0.925, 0.406, 0.466);
  base[4].seleccion();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0.1692, -0.4898);
  glScalef(0.925, 0.406, 1);
  base[5].seleccion();
  glPopMatrix();  


//Laterales del instake que se curvan hacia dentro
  glPushMatrix();
  glTranslatef(-0.9414, 0.1692, -0.4284);
  glRotatef(-8.05, 0, 1, 0);
  glScalef(0.270, 0.406, 0.976);
  base[6].seleccion();
  glPopMatrix();  

  glPushMatrix();
  glTranslatef(0.9414, 0.1692, -0.4284);
  glRotatef(8.05, 0, 1, 0);
  glScalef(0.270, 0.406, 0.976);
  base[7].seleccion();
  glPopMatrix();  

//Alisadores de curvas
  glPushMatrix();
  glTranslatef(0.5176, -0.3433, -0.0620);
  glRotatef(-13.9, 0, 1, 0);
  glScalef(0.270, 0.137, 1.061);
  base[8].seleccion();
  glPopMatrix();  

  glPushMatrix();
  glTranslatef(-0.5176, -0.3433, -0.0620);
  glRotatef(13.9, 0, 1, 0);
  glScalef(0.270, 0.137, 1.061);
  base[9].seleccion();
  glPopMatrix();  


//Sujeta alas, los que permite que se puedan plegar
  //1 izquierda y derecha

  glPushMatrix();
  glTranslatef(1.2496, 0.323, -0.7854);
  glRotatef(-38.4, 0, 1, 0);
  glScalef(0.451, 0.209, 0.29);
  base[10].seleccion();
  glPopMatrix();  


  glPushMatrix();
  glTranslatef(-1.2496, 0.323, -0.7854);
  glRotatef(38.4, 0, 1, 0);
  glScalef(0.451, 0.209, 0.29);
  base[11].seleccion();
  glPopMatrix();

  //2 izquierda y derecha

  glPushMatrix();
  glTranslatef(1.4784, 0.323, -0.2166);
  glRotatef(9.56, 0, 1, 0);
  glScalef(0.381, 0.209, 0.46);
  base[12].seleccion();
  glPopMatrix();  

  glPushMatrix();
  glTranslatef(-1.4784, 0.323, -0.2166);
  glRotatef(-9.56, 0, 1, 0);
  glScalef(0.381, 0.209, 0.46);
  base[13].seleccion();
  glPopMatrix();  


  //3 izquierda y derecha

  glPushMatrix();
  glTranslatef(1.3179, 0.323, 0.4604);
  glRotatef(-30.9, 0, 1, 0);
  glScalef(0.381, 0.209, 0.56);
  base[14].seleccion();
  glPopMatrix();    

  glPushMatrix();
  glTranslatef(-1.3179, 0.323, 0.4604);
  glRotatef(30.9, 0, 1, 0);
  glScalef(0.381, 0.209, 0.56);
  base[15].seleccion();
  glPopMatrix();      


//Alisadores de curva cola
  glPushMatrix();
  glTranslatef(0, -0.0379, -2.0821);
  glScalef(1.061, 0.24, 0.651);
  base[16].seleccion();
  glPopMatrix();    

  glPushMatrix();
  glTranslatef(0, 0.0713, -3.3869);
  glScalef(1.061, 0.123, 0.651);
  base[17].seleccion();
  glPopMatrix();    

  glPushMatrix();
  glTranslatef(0, 0.0713, -4.6922);
  glScalef(1.061, 0.087, 0.651);
  base[18].seleccion();
  glPopMatrix();      

  glPushMatrix();
  glTranslatef(0, -0.0844, -3.3869);
  glRotatef(6.37, 1, 0, 0);
  glScalef(1.061, 0.123, 0.651);
  base[19].seleccion();
  glPopMatrix();    


//Estabilizador de cola
  glPushMatrix();
  glTranslatef(0, 0.8568, -2.5387);
  glRotatef(-71.4, 1, 0, 0);
  glScalef(0.126, 1.08, 0.435);
  base[20].seleccion();
  glPopMatrix();    

  glPushMatrix();
  glTranslatef(0, 1.8809, -4.4713);
  glRotatef(-55.3, 1, 0, 0);
  glScalef(0.126, 1.96, 0.435);
  base[21].seleccion();
  glPopMatrix();    

  glPushMatrix();
  glTranslatef(0, 1.6522, -4.8354);
  glRotatef(-37.5, 1, 0, 0);
  glScalef(0.126, 1.33, 0.435);
  base[22].seleccion();
  glPopMatrix();    

  glPushMatrix();
  glTranslatef(0, 0.578, -5.0584);
  glScalef(0.126, 0.247, 0.509);
  base[23].seleccion();
  glPopMatrix();      

  glPushMatrix();
  glTranslatef(0, 2.8776, -6.2732);
  glScalef(0.126, 0.477, 0.435);
  base[24].seleccion();
  glPopMatrix();    

  glPushMatrix();
  glTranslatef(0, 2.8706, -6.787);
  glRotatef(-33.3, 1, 0, 0);
  glScalef(0.126, 0.437, 0.195);
  base[25].seleccion();
  glPopMatrix(); 

  glPushMatrix();
  glTranslatef(0, 3.198, -6.9019);
  glScalef(0.126, 0.157, 0.195);
  base[26].seleccion();
  glPopMatrix();           

  glPushMatrix();
  glTranslatef(0, -0.524, 1.5759);
  glRotatef(270, 1, 0, 0);
  glScalef(0.595, 3.620, 0.279);
  esquinas[0].seleccion();
  glPopMatrix();


  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(0.2268, -0.504, -0.2723);
  glRotatef(-13.9, 0, 1, 0);
  glRotatef(270, 1, 0, 0);
  glScalef(0.608, 0.899, 0.279);
  esquinas[1].seleccion();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.2268, -0.504, -0.2723);
  glRotatef(13.9, 0, 1, 0);
  glRotatef(270, 1, 0, 0);
  glScalef(0.608, 0.899, 0.279);
  esquinas[2].seleccion();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0.2058, 2.8629);
  glRotatef(93.2, 1, 0, 0);
  glScalef(0.595, 2.297, 0.279);
  esquinas[3].seleccion();
  glPopMatrix();       

  glPushMatrix();
  glTranslatef(0, 0.6863, -1.3726);
  glRotatef(88.2, 1, 0, 0);
  glScalef(0.226, 2.951, 0.235);
  esquinas[4].seleccion();
  glPopMatrix();    

  glPushMatrix();
  glTranslatef(0, -0.3637, -1.58);
  glRotatef(271, 1, 0, 0);
  glScalef(1.059, 0.538, 0.422);
  esquinas[5].seleccion();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0.171, -2.7727);
  glRotatef(270, 1, 0, 0);
  glScalef(1.059, 1.257, 0.422);
  esquinas[6].seleccion();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, -0.2311, -3.0631);
  glRotatef(276, 1, 0, 0);
  glScalef(1.059, 0.990, 0.423);
  esquinas[7].seleccion();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0.1517, -4.4509);
  glRotatef(269, 1, 0, 0);
  glScalef(1.059, 0.41, 0.422);
  esquinas[8].seleccion();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, -0.0391, -4.6683);
  glRotatef(276, 1, 0, 0);
  glScalef(1.059, 0.632, 0.422);
  esquinas[9].seleccion();
  glPopMatrix();  

  glPushMatrix();
  glTranslatef(0, 0.1189, -5.1279);
  glRotatef(266, 1, 0, 0);
  glScalef(1.059, 0.41, 0.422);
  esquinas[10].seleccion();
  glPopMatrix();  

  glPushMatrix();
  glTranslatef(0.4586, 0.0771, -5.5719);
  glRotatef(270, 1, 0, 0);
  glScalef(0.321, 0.129, 0.321);
esquinas[11].seleccion();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.4586, 0.0771, -5.5719);
  glRotatef(270, 1, 0, 0);
  glScalef(0.321, 0.129, 0.321);
  esquinas[12].seleccion();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, -0.3454, 6.407);
  glRotatef(94.7, 1, 0, 0);
  glScalef(0.475, 0.73, 0.502);
  nariz.seleccion();
  glPopMatrix();  


//Curva de la nariz
  glPushMatrix();
  glTranslatef(0, -0.2473, 5.201);
  glRotatef(4.72, 1, 0, 0);
  glScalef(0.557, 0.557, 1.112);
  nariz_curva.seleccion();
  glPopMatrix();  

  glPushMatrix();
  glTranslatef(0, 1.095, -2.1481);
  glRotatef(-71.4, 1, 0, 0);
  glScalef(0.12, 1.2, 0.232);
  esquinas[13].seleccion();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 2.3451, -4.5454);
  glRotatef(-55.3, 1, 0, 0);
  glScalef(0.12, 1.64, 0.232);
  esquinas[14].seleccion();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 3.2411, -6.4318);
  glRotatef(90, 1, 0, 0);
  glScalef(0.12, 0.67, 0.232);
  esquinas[15].seleccion();
  glPopMatrix(); 		
	}


	//protected:
	public:
	vector<_cubo> base;
	vector<_cilindro> esquinas;
	_cono nariz;
	_esfera nariz_curva;


public:
};


//************************************************************************

//************************************************************************

class _ala_izda: public _triangulos3D{
	public:
	const int CUBO_TAM=2;
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;
	const double ES_RADIO=1;


		_ala_izda(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo),
		esquina(ES_RADIO, NUM, NUM, eje, tipo){
			for(int i=0; i<4; i++)
				base.push_back(_cubo(CUBO_TAM, tipo));

			for(int i=0; i<2; i++)
				filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, tipo));			
		}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

		const double angulo_y=23.5;
		const double angulo_z=-4.6;
		const double x=1.3854;

	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}

	void recolorea(int *v, int salto){
		for (long unsigned int i = 0; i < base.size(); i++)
		{
			for (long unsigned int j = 0; j < base[i].color_selec[0].size(); j++)
			{
				base[i].color_selec[0][j]=v[0];
				base[i].color_selec[1][j]=v[1];
				base[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}	

		for (long unsigned int i = 0; i < filos.size(); i++)
		{
			for (long unsigned int j = 0; j < filos[i].color_selec[0].size(); j++)
			{
				filos[i].color_selec[0][j]=v[0];
				filos[i].color_selec[1][j]=v[1];
				filos[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}

		for(int i=0; i<esquina.triangulos; i++){
				esquina.color_selec[0][i]=v[0];
				esquina.color_selec[1][i]=v[1];
				esquina.color_selec[2][i]=v[2];

				RGB_Suma(v, salto);			
		}	
	}

	bool algunoActivo() const{
		bool alguno_activo=false;

		for(auto it=base.cbegin(); it!=base.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}

		for(auto it=filos.cbegin(); it!=filos.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}

		for(int i=0; i<esquina.triangulos; i++){
			if(esquina.activo[i]==1)
				alguno_activo=true;
		}

		return alguno_activo;
	}

	void seleccion(){
  glPushMatrix();
  glTranslatef(3.354, 2.1596, -1.5932);
  glRotatef(15.9, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.38);
  base[0].seleccion();
  glPopMatrix();     

  glPushMatrix();
  glTranslatef(3.3537, 2.1749, -1.1572);
  glRotatef(23.5, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.3);
  base[1].seleccion();
  glPopMatrix();    

  glPushMatrix();
  glTranslatef(5.7552, 1.9762, -2.4362);
  glRotatef(15.9, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(0.1, 0.105, 0.23);
  base[2].seleccion();
  glPopMatrix();   

  glPushMatrix();
  glTranslatef(5.8797, 1.9762, -2.7862);
  glRotatef(15.9, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(0.16, 0.075, 0.11);
  base[3].seleccion();
  glPopMatrix();  
  
  glPushMatrix();
  glTranslatef(3.6565, 2.1568, -1.0302);
  glRotatef(24.8, 0, 1, 0);
  glRotatef(-94.6, 0, 0, 1);
  glScalef(0.12, 2.096, 0.366);
  filos[0].seleccion();
  glPopMatrix();  

  glPushMatrix();
  glTranslatef(5.8499, 1.9745, -2.315);
  glRotatef(90, 1, 0, 0);  
  glRotatef(14.5, 0, 0, 1);
  glRotatef(4.6, 0, 1, 0);
  glScalef(0.165, 0.465, 0.12);
  filos[1].seleccion();
  glPopMatrix();  

  glPushMatrix();
  glTranslatef(5.6556, 1.9831, -1.8168);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(0.237, 0.12, 0.237);
  esquina.seleccion();
  glPopMatrix();
	}
	//protected:
	public:
	vector<_cubo> base;
	vector<_cilindro> filos;
	_esfera esquina;

};

class _ala_dcha: public _triangulos3D{
	public:
	const int CUBO_TAM=2;
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;
	const double ES_RADIO=1;

		_ala_dcha(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo),
		esquina(ES_RADIO, NUM, NUM, eje, tipo){
			for(int i=0; i<4; i++)
				base.push_back(_cubo(CUBO_TAM, tipo));

			for(int i=0; i<2; i++)
				filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, tipo));
		}

		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

	const double angulo_y=-23.5;
	const double angulo_z=4.6;
	const double x=-1.3854;

	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}

	public:
	vector<_cubo> base;
	vector<_cilindro> filos;
	_esfera esquina;

	void recolorea(int *v, int salto){
		for (long unsigned int i = 0; i < base.size(); i++)
		{
			for (long unsigned int j = 0; j < base[i].color_selec[0].size(); j++)
			{
				base[i].color_selec[0][j]=v[0];
				base[i].color_selec[1][j]=v[1];
				base[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}	

		for (long unsigned int i = 0; i < filos.size(); i++)
		{
			for (long unsigned int j = 0; j < filos[i].color_selec[0].size(); j++)
			{
				filos[i].color_selec[0][j]=v[0];
				filos[i].color_selec[1][j]=v[1];
				filos[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}

		for(int i=0; i<esquina.triangulos; i++){
				esquina.color_selec[0][i]=v[0];
				esquina.color_selec[1][i]=v[1];
				esquina.color_selec[2][i]=v[2];

				RGB_Suma(v, salto);			
		}	
	}

	bool algunoActivo() const{
		bool alguno_activo=false;

		for(auto it=base.cbegin(); it!=base.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}

		for(auto it=filos.cbegin(); it!=filos.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}

		for(int i=0; i<esquina.triangulos; i++){
			if(esquina.activo[i]==1)
				alguno_activo=true;
		}

		return alguno_activo;
	}


	void seleccion(){

  glPushMatrix();
  glTranslatef(-3.354, 2.1596, -1.5932);
  glRotatef(-15.9, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.38);
  base[0].seleccion();
  glPopMatrix();     

  glPushMatrix();
  glTranslatef(-3.3537, 2.1749, -1.1572);
  glRotatef(-23.5, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.3);
  base[1].seleccion();
  glPopMatrix();     

  glPushMatrix();
  glTranslatef(-5.7552, 1.9762, -2.4362);
  glRotatef(-15.9, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(0.1, 0.105, 0.23);
  base[2].seleccion();
  glPopMatrix();    


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-5.8797, 1.9762, -2.7862);
  glRotatef(-15.9, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(0.16, 0.075, 0.11);
  base[3].seleccion();
  glPopMatrix();    

  glPushMatrix();
  glTranslatef(-3.6565, 2.1568, -1.0302);  
  glRotatef(-24.8, 0, 1, 0);
  glRotatef(94.6, 0, 0, 1);
  glScalef(0.12, 2.096, 0.366);
  filos[0].seleccion();
  glPopMatrix();  


  glPushMatrix();
  glTranslatef(-5.8499, 1.9745, -2.315);
  glRotatef(90, 1, 0, 0);  
  glRotatef(-14.5, 0, 0, 1);
  glRotatef(-4.6, 0, 1, 0);
  glScalef(0.165, 0.465, 0.12);
  filos[1].seleccion();
  glPopMatrix();  

  glPushMatrix();
  glTranslatef(-5.6556, 1.9831, -1.8168);
  glRotatef(4.6, 0, 0, 1);
  glScalef(0.237, 0.12, 0.237);
  esquina.seleccion();
  glPopMatrix();   
	}






};


//************************************************************************
class _ala_td: public _triangulos3D{
	public:
		_ala_td(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo),
		esquina(ES_RADIO, NUM, NUM, eje, tipo){
			for (int i = 0; i < 8; i++)
				base.push_back(_cubo(CUBO_TAM, tipo));

			for(int i=0; i<2; i++)
				filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, tipo));

		}

		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}

	void recolorea(int *v, int salto){
		for (long unsigned int i = 0; i < base.size(); i++)
		{
			for (long unsigned int j = 0; j < base[i].color_selec[0].size(); j++)
			{
				base[i].color_selec[0][j]=v[0];
				base[i].color_selec[1][j]=v[1];
				base[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}	

		for (long unsigned int i = 0; i < filos.size(); i++)
		{
			for (long unsigned int j = 0; j < filos[i].color_selec[0].size(); j++)
			{
				filos[i].color_selec[0][j]=v[0];
				filos[i].color_selec[1][j]=v[1];
				filos[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}

		for(int i=0; i<esquina.triangulos; i++){
				esquina.color_selec[0][i]=v[0];
				esquina.color_selec[1][i]=v[1];
				esquina.color_selec[2][i]=v[2];

				RGB_Suma(v, salto);			
		}	
	}

	bool algunoActivo() const{
		bool alguno_activo=false;

		for(auto it=base.cbegin(); it!=base.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}

		for(auto it=filos.cbegin(); it!=filos.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}

		for(int i=0; i<esquina.triangulos; i++){
			if(esquina.activo[i]==1)
				alguno_activo=true;
		}

		return alguno_activo;
	}


	void seleccion(){
    glPushMatrix();
    glTranslatef(-1.0904, -0.035261, -0.61322);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(31.4, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.451, 0.045, 0.68);
    base[0].seleccion();
    glPopMatrix();      



    glPushMatrix();
    glTranslatef(-0.5252, -0.014561, 0.26328);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(35.2, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.451, 0.045, 0.4);
    base[1].seleccion();
    glPopMatrix(); 



    glPushMatrix();
    glTranslatef(-0.5423, -0.012661, -0.62752);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.32, 0.045, 0.411);
    base[2].seleccion();
    glPopMatrix(); 



    glPushMatrix();
    glTranslatef(-1.5295, -0.045961, -1.14682);
    glRotatef(1.19, 1, 0, 0);
    glRotatef(1.66, 0, 0, 1);
    glScalef(0.4, 0.045, 0.181);
    base[3].seleccion();
    glPopMatrix(); 



    glPushMatrix();
    glTranslatef(-0.4695, -0.017161, 0.73348);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(35.2, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.231, 0.045, 0.330);
    base[4].seleccion();
    glPopMatrix(); 



    glPushMatrix();
    glTranslatef(-0.3154, -0.016461, 1.14298);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(35.2, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.121, 0.045, 0.16);
    base[5].seleccion();
    glPopMatrix(); 


    glPushMatrix();
    glTranslatef(-0.1629, -0.001461, 0.29108);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.16, 0.045, 1.222);
    base[6].seleccion();
    glPopMatrix(); 



    glPushMatrix();
    glTranslatef(-0.8785, -0.020161, -1.18222);
    glRotatef(1.19, 1, 0, 0);
    glRotatef(-18, 0, 1, 0);
    glRotatef(1.66, 0, 0, 1);
    glScalef(1.06, 0.045, 0.181);
    base[7].seleccion();
    glPopMatrix(); 


//Ahora los cilindros que hacen que los filos sean redondeados
  //derecha

    glPushMatrix();
    glTranslatef(-1.0211, -0.034261, 0.33208);
    glRotatef(35.2, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glRotatef(88.9, 1, 0, 0);       
    glScalef(0.15, 1.56, 0.04);
    filos[0].seleccion();
    glPopMatrix();   



    glPushMatrix();
    glTranslatef(-1.9383, -0.049661, -1.32752);
    glRotatef(1.19, 0, 0, 1);
    glRotatef(91.7, 1, 0, 0);       
    glScalef(0.15, 0.34, 0.04);
    filos[1].seleccion();
    glPopMatrix();   

    glPushMatrix();
    glTranslatef(-1.9503, -0.058461, -0.95252);
    glRotatef(3.9, 1, 0, 0);       
    glRotatef(5.9, 0, 0, 1);
    glScalef(0.135, 0.035, 0.125);
    esquina.seleccion();
    glPopMatrix();  
	}

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

	//protected:
	public:
	vector<_cubo> base;
	vector<_cilindro> filos;
	_esfera esquina;	
};




class _ala_ti: public _triangulos3D{
	public:
		_ala_ti(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo),
		esquina(ES_RADIO, NUM, NUM, eje, tipo){
			for (int i = 0; i < 8; i++)
				base.push_back(_cubo(CUBO_TAM, tipo));

			for(int i=0; i<2; i++)
				filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, tipo));
			
		}

		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

	const double x=1.0603;
	const double y=1.984261;
	const double z=-4.66768;

	//const double intermedio_y=0.025641;
	//const double y_i_f=y-intermedio_y;


	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}

	void recolorea(int *v, int salto){
		for (long unsigned int i = 0; i < base.size(); i++)
		{
			for (long unsigned int j = 0; j < base[i].color_selec[0].size(); j++)
			{
				base[i].color_selec[0][j]=v[0];
				base[i].color_selec[1][j]=v[1];
				base[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}	

		for (long unsigned int i = 0; i < filos.size(); i++)
		{
			for (long unsigned int j = 0; j < filos[i].color_selec[0].size(); j++)
			{
				filos[i].color_selec[0][j]=v[0];
				filos[i].color_selec[1][j]=v[1];
				filos[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}

		for(int i=0; i<esquina.triangulos; i++){
				esquina.color_selec[0][i]=v[0];
				esquina.color_selec[1][i]=v[1];
				esquina.color_selec[2][i]=v[2];

				RGB_Suma(v, salto);			
		}	
	}

	bool algunoActivo() const{
		bool alguno_activo=false;

		for(auto it=base.cbegin(); it!=base.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}

		for(auto it=filos.cbegin(); it!=filos.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}

		for(int i=0; i<esquina.triangulos; i++){
			if(esquina.activo[i]==1)
				alguno_activo=true;
		}

		return alguno_activo;
	}


void seleccion(){
    glPushMatrix();
    glTranslatef(1.0904, -0.035261, -0.61322);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(-31.4, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.451, 0.045, 0.68);
    base[0].seleccion();
    glPopMatrix();     


    glPushMatrix();
    glTranslatef(0.5252, -0.014561, 0.26328);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(-35.2, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.451, 0.045, 0.4);
    base[1].seleccion();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.5423, -0.012661, -0.62752);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.32, 0.045, 0.411);
    base[2].seleccion();
    glPopMatrix();          



    glPushMatrix();
    glTranslatef(1.5295, -0.045961, -1.14682);
    glRotatef(1.19, 1, 0, 0);
    glRotatef(-1.66, 0, 0, 1);
    glScalef(0.4, 0.045, 0.181);
    base[3].seleccion();
    glPopMatrix();     



    glPushMatrix();
    glTranslatef(0.4695, -0.017161, 0.73348);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(-35.2, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.231, 0.045, 0.330);
    base[4].seleccion();
    glPopMatrix();     



    glPushMatrix();
    glTranslatef(0.3154, -0.016461, 1.14298);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(-35.2, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.121, 0.045, 0.16);
    base[5].seleccion();
    glPopMatrix();     



    glPushMatrix();
    glTranslatef(0.1629, -0.001461, 0.29108);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.16, 0.045, 1.222);
    base[6].seleccion();
    glPopMatrix();     



    glPushMatrix();
    glTranslatef(0.8785, -0.020161, -1.18222);
    glRotatef(1.19, 1, 0, 0);
    glRotatef(18, 0, 1, 0);
    glRotatef(-1.66, 0, 0, 1);
    glScalef(1.06, 0.045, 0.181);
    base[7].seleccion();
    glPopMatrix(); 

    glPushMatrix();
    glTranslatef(1.0211, -0.034261, 0.33208);
    glRotatef(-35.2, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glRotatef(88.9, 1, 0, 0);       
    glScalef(0.15, 1.56, 0.04);
    filos[0].seleccion();
    glPopMatrix();   


    glPushMatrix();
    glTranslatef(1.9383, -0.049661, -1.32752);
    glRotatef(-1.19, 0, 0, 1);
    glRotatef(91.7, 1, 0, 0);       
    glScalef(0.15, 0.34, 0.04);
    filos[1].seleccion();
    glPopMatrix();   

    glPushMatrix();
    glTranslatef(1.9503, -0.058461, -0.95252);
    glRotatef(3.9, 1, 0, 0);
    glRotatef(-5.9, 0, 0, 1);
    glScalef(0.135, 0.035, 0.125);
    esquina.seleccion();
    glPopMatrix(); 	
}

	private:
	const int CUBO_TAM=2;
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;
	const double ES_RADIO=1;

	public:
	vector<_cubo> base;
	vector<_cilindro> filos;
	_esfera esquina;	
};
//************************************************************************

class _ventana_movil: public _triangulos3D{
	public:
		_ventana_movil(Materiales::tipoMaterial tipo=Materiales::PERLADO):_triangulos3D(tipo)//,
		//pico(CONO_RADIO, CONO_H, NUM, eje, tipo){
			{

			for(int i=0; i<3; i++)
				base.push_back(_cubo(CUBO_TAM, tipo));

			for(int i=0; i<2; i++)
				filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, tipo));
		}

		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		
		
		double x=0;
		double y=2.99002;
		double z=1.60318;
		//double intermedio_y=1.03152;
		//double y_i_f=y-intermedio_y;	//Lo que hay que subir desde el intermedio hasta el final




	
	const int CUBO_TAM=2;
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;
	const double CONO_RADIO=1, CONO_H=2;


	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}

	void recolorea(int *v, int salto){
		for (long unsigned int i = 0; i < base.size(); i++)
		{
			for (long unsigned int j = 0; j < base[i].color_selec[0].size(); j++)
			{
				base[i].color_selec[0][j]=v[0];
				base[i].color_selec[1][j]=v[1];
				base[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}	

		for (long unsigned int i = 0; i < filos.size(); i++)
		{
			for (long unsigned int j = 0; j < filos[i].color_selec[0].size(); j++)
			{
				filos[i].color_selec[0][j]=v[0];
				filos[i].color_selec[1][j]=v[1];
				filos[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}	
	}

	bool algunoActivo() const{
		bool alguno_activo=false;

		for(auto it=base.cbegin(); it!=base.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}

		for(auto it=filos.cbegin(); it!=filos.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}

		return alguno_activo;
	}


void seleccion(){
  glPushMatrix();
  glTranslatef(0, -0.64416, 1.204);
  glRotatef(1.1, 1, 0, 0);
  glScalef(0.324, 0.064, 1.21);
base[0].seleccion();
  glPopMatrix(); 

  //derecha

  glPushMatrix();
  glTranslatef(-0.2509, -0.44495, 1.1041);
  glRotatef(-11.3, 0, 0, 1);
  glScalef(0.05, 0.16, 1.11);
  base[1].seleccion();
  glPopMatrix(); 


  //izquierda

  glPushMatrix();
  glTranslatef(0.2509, -0.44495, 1.1041);
  glRotatef(11.3, 0, 0, 1);
  glScalef(0.05, 0.16, 1.11);
  base[2].seleccion();
  glPopMatrix(); 

  glPushMatrix();
  glTranslatef(0, -0.26732, 0.97712);
  glRotatef(90, 1, 0, 0);
  glScalef(0.265, 0.985, 0.265);
filos[0].seleccion();
  glPopMatrix();     




  glPushMatrix();
  glTranslatef(0, -0.28891, 2.0103);
  glRotatef(104, 1, 0, 0);
  glScalef(0.265, 0.115, 0.265);
filos[1].seleccion();
  glPopMatrix(); 	
}

	//protected:

	public:
	vector<_cubo> base;
	vector<_cilindro> filos;
	//_cono pico;	
};


//************************************************************************

class _ventana_fija: public _triangulos3D{
	public:
		_ventana_fija(Materiales::tipoMaterial tipo=Materiales::PERLADO):_triangulos3D(tipo),
		filos(CIL_RAD, CIL_H, NUM, eje, tipo), pico(CONO_RADIO, CONO_H, NUM, eje, tipo){
			for(int i=0; i<2; i++)
				base.push_back(_cubo(CUBO_TAM, tipo));
		}

		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

		double x=0;
		double y=2.99002;
		double z=1.60318;

	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}

	void recolorea(int *v, int salto){
		for (long unsigned int i = 0; i < base.size(); i++)
		{
			for (long unsigned int j = 0; j < base[i].color_selec[0].size(); j++)
			{
				base[i].color_selec[0][j]=v[0];
				base[i].color_selec[1][j]=v[1];
				base[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}	

		for(long unsigned int i=0; i<filos.color_selec[0].size(); i++){
				filos.color_selec[0][i]=v[0];
				filos.color_selec[1][i]=v[1];
				filos.color_selec[2][i]=v[2];

				RGB_Suma(v, salto);			
		}

		for(long unsigned int i=0; i<pico.color_selec[0].size(); i++){
				pico.color_selec[0][i]=v[0];
				pico.color_selec[1][i]=v[1];
				pico.color_selec[2][i]=v[2];

				RGB_Suma(v, salto);						
		}
	}

	bool algunoActivo() const{
		bool alguno_activo=false;

		for(auto it=base.cbegin(); it!=base.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}

		for(long unsigned int i=0; i<filos.activo.size(); i++){
							if(filos.activo[i]==1)
					alguno_activo=true;
		}

		for(long unsigned int i=0; i<pico.activo.size(); i++){
							if(pico.activo[i]==1)
					alguno_activo=true;			
		}
		return alguno_activo;
	}


	void seleccion(){
  glPushMatrix();
  glTranslatef(-0.2208, -0.47467, 2.4468);
  glRotatef(-14.5, 0, 0, 1);
  glRotatef(12.1, 0, 1, 0);
  glRotatef(7.47, 1, 0, 0);
  glScalef(0.05, 0.16, 0.26);
  base[0].seleccion();
  glPopMatrix();   



  glPushMatrix();
  glTranslatef(0.2208, -0.47467, 2.4468);
  glRotatef(14.5, 0, 0, 1);
  glRotatef(-12.1, 0, 1, 0);
  glRotatef(7.47, 1, 0, 0);
  glScalef(0.05, 0.16, 0.26);
  base[1].seleccion();
  glPopMatrix();   

  glPushMatrix();
  glTranslatef(0, -0.403, 2.26);
  glRotatef(117, 1, 0, 0);
  glScalef(0.265, 0.225, 0.265);
  filos.seleccion();
  glPopMatrix(); 

  glPushMatrix();
  glTranslatef(0, -0.60895, 2.9173);
  glRotatef(106, 1, 0, 0);
  glScalef(0.249, 0.429, 0.249);
  pico.seleccion();
  glPopMatrix();		
	}

	private:
	const int CUBO_TAM=2;
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;
	const double CONO_RADIO=1, CONO_H=2;

	//protected:
	public:
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

	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}

	void recolorea(int *v, int salto){
		//for (int i = 0; i < piezas.size(); i++)
		//{
			for (long unsigned int j = 0; j < flap.color_selec[0].size(); j++)
			{
				flap.color_selec[0][j]=v[0];
				flap.color_selec[1][j]=v[1];
				flap.color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		//}		
	}

	bool algunoActivo() const{
		bool alguno_activo=false;

		//for(auto it=flap.cbegin(); it!=piezas.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<flap.activo.size() and !alguno_activo; j++){
				if(flap.activo[j]==1)
					alguno_activo=true;
			}
		//}


		return alguno_activo;
	}


	void seleccion(){
  glPushMatrix();
  glScalef(2.23, 0.08, 0.26);
  flap.seleccion();
  glPopMatrix();
	}

	private:
	const int CUBO_TAM=2;

		//const double intermedio_y=1.95865;
	//protected:
	public:
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
		const double freno_delantero_angulo_y=-15.9;
		const double freno_delantero_angulo_z=4.6;

	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}

	void recolorea(int *v, int salto){

			for (long unsigned int j = 0; j < base.color_selec[0].size(); j++)
			{
				base.color_selec[0][j]=v[0];
				base.color_selec[1][j]=v[1];
				base.color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
	}

	bool algunoActivo() const{
		bool alguno_activo=false;

			for(long unsigned int j=0; j<base.activo.size() and !alguno_activo; j++){
				if(base.activo[j]==1)
					alguno_activo=true;
			}


		return alguno_activo;
	}


	void seleccion(){
  glPushMatrix();
  glTranslatef(0, 0, -0.18);
  glScalef(1.29, 0.02, 0.18);
  base.seleccion();
  glPopMatrix(); 		
	}


	private:
	const int CUBO_TAM=2;

	public:
	_cubo base;
};


//************************************************************************

class _timon: public _triangulos3D{
	public:
		_timon(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo){
			for(int i=0; i<9; i++)
				base.push_back(_cubo(CUBO_TAM, tipo));  

			
		}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		


		const double y=3.579368;
		const double z=-5.78512;

	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}

	void recolorea(int *v, int salto){
		for (long unsigned int i = 0; i < base.size(); i++)
		{
			for (long unsigned int j = 0; j < base[i].color_selec[0].size(); j++)
			{
				base[i].color_selec[0][j]=v[0];
				base[i].color_selec[1][j]=v[1];
				base[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}		
	}

	bool algunoActivo() const{
		bool alguno_activo=false;

		for(auto it=base.cbegin(); it!=base.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}


		return alguno_activo;
	}

	void seleccion(){
 glPushMatrix();
  glTranslatef(0, -0.735068, 0.57972);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.48, 0.05);
  base[0].seleccion();
  glPopMatrix(); 



  glPushMatrix();
  glTranslatef(0, -0.013668, -0.35948);
  glRotatef(-33.5, 1, 0, 0);
  glScalef(0.126, 0.9, 0.05);
  base[1].seleccion();
  glPopMatrix();   



  glPushMatrix();
  glTranslatef(0, 0.725832, -0.52188);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.34, 0.05);
  base[2].seleccion();
  glPopMatrix(); 



  glPushMatrix();
  glTranslatef(0, -0.006568, 0.36032);
  glRotatef(-37.8, 1, 0, 0);
  glScalef(0.126, 0.95, 0.05);
  base[3].seleccion();
  glPopMatrix();     

  //Relleno del marco (de arriba a abajo)

  glPushMatrix();
  glTranslatef(0, 0.635032, -0.49598);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.28, 0.08);
  base[4].seleccion();
  glPopMatrix();     



  glPushMatrix();
  glTranslatef(0, 0.507032, -0.41638);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.28, 0.08);
  base[5].seleccion();
  glPopMatrix();  



  glPushMatrix();
  glTranslatef(0, -0.000268, 0.00522);
  glRotatef(-35.6, 1, 0, 0);
  glScalef(0.126, 0.71, 0.29);
  base[6].seleccion();
  glPopMatrix();            



  glPushMatrix();
  glTranslatef(0, -0.499868, 0.43822);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.3, 0.08);
  base[7].seleccion();
  glPopMatrix();       



  glPushMatrix();
  glTranslatef(0, -0.658968, 0.55672);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.3, 0.08);
  base[8].seleccion();
  glPopMatrix();
	}

	private:
	const int CUBO_TAM=2;

	//protected:
	public:
	vector<_cubo> base;
};


//************************************************************************

//************************************************************************

class _freno_trasero_individual: public _triangulos3D{
	public:
		_freno_trasero_individual(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo), base(CUBO_TAM, tipo){}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

		const double angulo_z_l=-23.5;
		const double x=0.7922;
		const double y=2.3859;
		const double z=-2.9941;

	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}

	void recolorea(int *v, int salto){
		//for (int i = 0; i < piezas.size(); i++)
		//{
			for (long unsigned int j = 0; j < base.color_selec[0].size(); j++)
			{
				base.color_selec[0][j]=v[0];
				base.color_selec[1][j]=v[1];
				base.color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		//}		
	}

	bool algunoActivo() const{
		bool alguno_activo=false;

		//for(auto it=base.cbegin(); it!=piezas.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<base.activo.size() and !alguno_activo; j++){
				if(base.activo[j]==1)
					alguno_activo=true;
			}
		//}


		return alguno_activo;
	}

	void seleccion(){
  glPushMatrix();
  glTranslatef(0, 0, -0.64);
  glScalef(0.26, 0.02, 0.64);
  base.seleccion();
  glPopMatrix(); 		
	}

		const double centro_z=0.64;	//Para centrar la figura

	private:
	const int CUBO_TAM=2;

	//protected:
	public:
	_cubo base;
};



//************************************************************************

class _tren_trasero: public _triangulos3D{
	public:
		_tren_trasero(Materiales::tipoMaterial tipo=Materiales::GOMA):_triangulos3D(tipo){
			piezas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
			piezas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
			piezas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));


			int v[3]={0, 0, 1};
			recolorea(v, 1);

		}

		bool algunoActivo() const{
			bool alguno_activo=false;

			for(auto it=piezas.cbegin(); it!=piezas.cend() and !alguno_activo; ++it){
				for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
					if(it->activo[j]==1)
						alguno_activo=true;
				}
			}


			return alguno_activo;			
		}

	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}
	void recolorea(int *v, int salto){
		//int c=empieza;


		for (long unsigned int i = 0; i < piezas.size(); i++)
		{
			for (long unsigned int j = 0; j < piezas[i].color_selec[0].size(); j++)
			{
				//piezas[i].color_selec[0][j] = piezas[i].color_selec[1][j] = piezas[i].color_selec[2][j] = c;
				//c = (c + salto) % 255;
				piezas[i].color_selec[0][j]=v[0];
				piezas[i].color_selec[1][j]=v[1];
				piezas[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
				//c+=salto;
				//cout <<v[0] <<"\t" <<v[1] <<"\t" <<v[2] <<endl;
			}
		}		
	}

		void seleccion(){
			glPushMatrix();
			glTranslatef(0, -0.6, 0);
			glScalef(0.05, 0.57, 0.05);
			piezas[0].seleccion();
			glPopMatrix();

			//Rueda
			glPushMatrix();
			glTranslatef(-0.1262, -1.1462, 0);
			glRotatef(90, 0, 0, 1);
			glScalef(0.34, 0.16, 0.34);
			piezas[1].seleccion();
			glPopMatrix();			
		}

		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

		const double x_r=-0.89669;
		const double y_r=1.30617;
		const double z_r=-1.107;


	private:
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;

	//protected:
	public:
	vector<_cilindro> piezas;
};



//************************************************************************

class _tren_delantero: public _triangulos3D{
	public:
		_tren_delantero(Materiales::tipoMaterial tipo=Materiales::COBRE_PULIDO):_triangulos3D(tipo){

    piezas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, tipo));
	piezas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, tipo));
	piezas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, tipo));

		int v[3]={0, 0, 1};
	recolorea(v, 1);
		}
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s=false);		

		const double y=1.28617;
		const double z=3.5297;

	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}

	void recolorea(int *v, int salto){
		for (long unsigned int i = 0; i < piezas.size(); i++)
		{
			for (long unsigned int j = 0; j < piezas[i].color_selec[0].size(); j++)
			{
				piezas[i].color_selec[0][j]=v[0];
				piezas[i].color_selec[1][j]=v[1];
				piezas[i].color_selec[2][j]=v[2];

				RGB_Suma(v, salto);
			}
		}		
	}

	bool algunoActivo() const{
		bool alguno_activo=false;

		for(auto it=piezas.cbegin(); it!=piezas.cend() and !alguno_activo; ++it){
			for(long unsigned int j=0; j<it->activo.size() and !alguno_activo; j++){
				if(it->activo[j]==1)
					alguno_activo=true;
			}
		}


		return alguno_activo;
	}

	void seleccion(){
  //Brazo 0.7 0.4
  glPushMatrix();
  glTranslatef(0, -0.55, 0);
  glScalef(0.05, 0.57, 0.05);
    piezas[0].seleccion();
  glPopMatrix();

  //Ruedas 0.24 0.12
  //Izquierda
  //No hay otra forma de hacer el material que creando otra pieza

  glPushMatrix();
  glTranslatef(-0.1543, -1.1262, -0.006611);
  glRotatef(90, 0, 0, 1);
  glScalef(0.2, 0.12, 0.2);
    piezas[1].seleccion();
  glPopMatrix();

  //Derecha
  //No hay otra forma de hacer el material que creando otra pieza

  glPushMatrix();
  glTranslatef(0.1543, -1.1262, -0.006611);
  glRotatef(90, 0, 0, 1);
  glScalef(0.2, 0.12, 0.2);
    piezas[2].seleccion();
  glPopMatrix();		
	}





/*
	float  color_pick[3];
	vector<int>    color_selec[3];
	vector<int>    activo;
	int    triangulos;
*/

	private:
	const double CIL_RAD=1, CIL_H=2;
	const int NUM=12;
	const Eje eje=Eje::y;

	//protected:
	public:
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

	void RGB_Suma(int *v, int salto){
				v[2]+=salto;

				if(v[2]>255){
					if(v[1]==255){
						v[0]++;
						v[1]=0;
					}
					
					v[1]++;
					v[2]=0;
				}
	}

		_tornado(Materiales::tipoMaterial mat): cuerpo(mat), ala_izda(mat), ala_dcha(mat), td(mat), ti(mat),
		ventana_fija(mat), ventana_movil(mat), timon(mat), tren_d(mat){
			
			////cout <<"--------------------------------------------------------------" <<endl;
			tt[0].material.setValores(mat);
			tt[1].material.setValores(mat);

			flap[0].material.setValores(mat);
			flap[1].material.setValores(mat);


			frenos[0].material.setValores(mat);
			frenos[1].material.setValores(mat);

			ft[0].material.setValores(mat);
			ft[1].material.setValores(mat);

			for (int i = 0; i < 50; i++)
				actos[i] = false;


			//int c=1;
			int v[3]={0, 0, 1};
			tren_d.recolorea(v, 1);
			//cout <<v[0] <<"\t" <<v[1] <<"\t" <<v[2] <<endl;
			tt[0].recolorea(v, 1);
			//cout <<v[0] <<"\t" <<v[1] <<"\t" <<v[2] <<endl;
			tt[1].recolorea(v, 1);
			//cout <<v[0] <<"\t" <<v[1] <<"\t" <<v[2] <<endl;
			flap[0].recolorea(v, 1);
			//cout <<v[0] <<"\t" <<v[1] <<"\t" <<v[2] <<endl;
			flap[1].recolorea(v, 1);
			//cout <<v[0] <<"\t" <<v[1] <<"\t" <<v[2] <<endl;
			
			frenos[0].recolorea(v, 1);
			frenos[1].recolorea(v, 1);

			ft[0].recolorea(v, 1);
			ft[1].recolorea(v, 1);

			timon.recolorea(v, 1);

			ventana_fija.recolorea(v, 1);

			ventana_movil.recolorea(v, 1);

			ti.recolorea(v, 1);

			td.recolorea(v, 1);

			ala_dcha.recolorea(v, 1);
			ala_izda.recolorea(v, 1);

			cuerpo.recolorea(v, 1);

			RGB_Suma(v, 1);
			//c++;
			////cout <<"c: " <<c <<endl;
			//int c = 14;
			//c%=255;
			color_pick[0] = 1.0;
			color_pick[1] = 0.0;
			color_pick[2] = 0.0;
			for (int i = 0; i < piezas; i++)
			{
				activo[i] = 0;
				color_selec[0][i] = v[0];
				color_selec[1][i] = v[1];
				color_selec[2][i] = v[2];
				RGB_Suma(v, 1);
				//cout <<v[0] <<"\t" <<v[1] <<"\t" <<v[2] <<endl;
			}

			////cout <<"c: " <<c <<endl;
			////cout <<"--------------------------------------------------------------" <<endl;

		}


		void setMaterial(Materiales::tipoMaterial tipo){
			cuerpo.material=ala_izda.material=ala_dcha.material=td.material=ti.material=ventana_fija.material=ventana_movil.material=flap[0].material=flap[1].material=frenos[0].material=
			frenos[1].material=ft[0].material=ft[1].material=timon.material=tt[0].material=tt[1].material=tren_d.material=Materiales(tipo);	
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

	//protected:
	_cuerpo cuerpo;
	_ala_izda ala_izda;				//
	_ala_dcha ala_dcha;				//
	_ala_td td;						//
	_ala_ti ti;						//
	_ventana_fija ventana_fija;		//
	_ventana_movil ventana_movil;	//
	_flap flap[2];					//
	_freno_individual frenos[2];	//
	_freno_trasero_individual ft[2];//
	_timon timon;					//
	_tren_trasero tt[2];			//
	_tren_delantero tren_d;			//
};