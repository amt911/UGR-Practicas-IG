//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
  /*
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
*/

//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size()); 

}

//*************************************************************************
// materiales
//*************************************************************************
Materiales::Materiales(tipoMaterial material){
  setValores(material);
}

const _vertex4f &Materiales::getAmbiente() const{
  return ambiente;
}

const _vertex4f &Materiales::getEspecular() const{
  return especular;
}
const _vertex4f &Materiales::getDifusa() const{
  return difusa;
}


const float Materiales::getBrillo(){
  return brillo;
}

void Materiales::setValores(tipoMaterial tipo){
  mat=tipo;
  switch(tipo){
    case LATON:{
      ambiente=_vertex4f(0.329412, 0.223529, 0.027451, 1);
      difusa=_vertex4f(0.780392, 0.568627, 0.113725, 1);
      especular=_vertex4f(0.992157, 0.941176, 0.807843, 1);
      brillo=27.8974;
      
      break;
    }

    case BRONCE:{
      ambiente=_vertex4f(0.2125, 0.1275, 0.054, 1);
      difusa=_vertex4f(0.714, 0.4284, 0.18144, 1);
      especular=_vertex4f(0.393548, 0.271906, 0.166721, 1);
      brillo=25.6;
      
      break;
    }

    case BRONCE_PULIDO:{
      ambiente=_vertex4f(0.25, 0.148, 0.06475, 1);
      difusa=_vertex4f(0.4, 0.2368, 0.1036, 1);
      especular=_vertex4f(0.774597, 0.458561, 0.200621, 1);
      brillo=76.8;
      
      break;
    }

    case CROMADO:{
      ambiente=_vertex4f(0.25, 0.25, 0.25, 1);
      difusa=_vertex4f(0.4, 0.4, 0.4, 1);
      especular=_vertex4f(0.774597, 0.774597, 0.774597, 1);
      brillo=76.8;
      
      break;
    }

    case COBRE:{
      ambiente=_vertex4f(0.19125, 0.0735, 0.0225, 1);
      difusa=_vertex4f(0.7038, 0.27048, 0.0828, 1);
      especular=_vertex4f(0.256777, 0.137622, 0.086014, 1);
      brillo=12.8;
      
      break;
    }

    case COBRE_PULIDO:{
      ambiente=_vertex4f(0.2295, 0.08825, 0.0275, 1);
      difusa=_vertex4f(0.5508, 0.2118, 0.066, 1);
      especular=_vertex4f(0.580594, 0.223257, 0.0695701, 1);
      brillo=51.2;
      
      break;
    }

    case ORO:{
      ambiente=_vertex4f(0.24725, 0.1995, 0.0745, 1);
      difusa=_vertex4f(0.75164, 0.60648, 0.22648, 1);
      especular=_vertex4f(0.628281, 0.555802, 0.366065, 1);
      brillo=51.2;
      
      break;
    }

    case ORO_PULIDO:{
      ambiente=_vertex4f(0.24725, 0.2245, 0.0645, 1);
      difusa=_vertex4f(0.34615, 0.3143, 0.0903, 1);
      especular=_vertex4f(0.797357, 0.723991, 0.208006, 1);
      brillo=83.2;
      
      break;
    }

    case TIN:{
      ambiente=_vertex4f(0.105882, 0.058824, 0.113725, 1);
      difusa=_vertex4f(0.427451, 0.470588, 0.541176, 1);
      especular=_vertex4f(0.333333, 0.333333, 0.521569, 1);
      brillo=9.84615;

      break;      
    }

    case PLATA:{
      ambiente=_vertex4f(0.19225, 0.19225, 0.19225, 1);
      difusa=_vertex4f(0.50754, 0.50754, 0.50754, 1);
      especular=_vertex4f(0.508273, 0.508273, 0.508273, 1);
      brillo=51.2;      

      break;
    }

    case PLATA_PULIDA:{
      ambiente=_vertex4f(0.23125, 0.23125, 0.23125, 1);
      difusa=_vertex4f(0.2775, 0.2775, 0.2775, 1);
      especular=_vertex4f(0.773911, 0.773911, 0.773911, 1);
      brillo=89.6;

      break;      
    }

    case ESMERALDA:{
      ambiente=_vertex4f(0.0215, 0.1745, 0.0215, 0.55);
      difusa=_vertex4f(0.07568, 0.61424, 0.07568, 0.55);
      especular=_vertex4f(0.633, 0.727811, 0.633, 0.55);
      brillo=76.8;      

      break;
    }

    case JADE:{
      ambiente=_vertex4f(0.135, 0.2225, 0.1575, 0.95);
      difusa=_vertex4f(0.54, 0.89, 0.63, 0.95);
      especular=_vertex4f(0.316228, 0.316228, 0.316228, 0.95);
      brillo=12.8;

      break;
    }

    case OBSIDIANA:{
      ambiente=_vertex4f(0.05375, 0.05, 0.06625, 0.82);
      difusa=_vertex4f(0.18275, 0.17, 0.22525, 0.82);
      especular=_vertex4f(0.332741, 0.328634, 0.346435, 0.82);
      brillo=38.4;

      break;
    }

    case PERLADO:{
      ambiente=_vertex4f(0.25, 0.20725, 0.20725, 0.922);
      difusa=_vertex4f(1, 0.829, 0.829, 0.922);
      especular=_vertex4f(0.296648, 0.296648, 0.296648, 0.922);
      brillo=11.264;

      break;      
    }

    case RUBI:{
      ambiente=_vertex4f(0.1745, 0.01175, 0.01175, 0.55);
      difusa=_vertex4f(0.61424, 0.04136, 0.04136, 0.55);
      especular=_vertex4f(0.727811, 0.626959, 0.626959, 0.55);
      brillo=76.8;

      break;      
    }

    case TURQUESA:{
      ambiente=_vertex4f(0.1, 0.18725, 0.1745, 0.8);
      difusa=_vertex4f(0.396, 0.74151, 0.69102, 0.8);
      especular=_vertex4f(0.297254, 0.30829, 0.306678, 0.8);
      brillo=12.8;

      break;
    }

    case PLASTICO:{
      ambiente=_vertex4f(0, 0, 0, 1);
      difusa=_vertex4f(0.01, 0.01, 0.01, 1);
      especular=_vertex4f(0.5, 0.5, 0.5, 1);
      brillo=32;      

      break;
    }

    case GOMA:{
      ambiente=_vertex4f(0.02, 0.02, 0.02, 1);
      difusa=_vertex4f(0.01, 0.01, 0.01, 1);
      especular=_vertex4f(0.4, 0.4, 0.4, 1);
      brillo=10;

      break;      
    }

    case ALUMINIO:{
      /*
      ambiente=_vertex4f(0.4, 0.4, 0.4, 1);
      difusa=_vertex4f(0.4, 0.4, 0.4, 1);
      especular=_vertex4f(0.2, 0.2, 0.2, 1);
      brillo=89.6;
*/

      ambiente=_vertex4f(0.4, 0.5, 0.4, 1);
      difusa=_vertex4f(0.4, 0.5, 0.4, 1);
      especular=_vertex4f(0.2, 0.2, 0.2, 1);
      brillo=89.6;

      break;            
    }

    case CRISTAL:{
      ambiente=_vertex4f(0.3, 0.3, 0.3, 1);
      difusa=_vertex4f(0.7, 0.7, 1, 1);
      especular=_vertex4f(0.8, 0.8, 0.8, 1);
      brillo=100;

      break;
    }
  }
}

void Materiales::setAmbiente(double v1, double v2, double v3){
  _vertex4f aux(v1, v2, v3, 1);

  ambiente=aux;
}

void Materiales::setEspecular(double v1, double v2, double v3){
  _vertex4f aux(v1, v2, v3, 1);

  especular=aux;
}


void Materiales::setDifusa(double v1, double v2, double v3){
  _vertex4f aux(v1, v2, v3, 1);

  difusa=aux;
}


void Materiales::setBrillo(double valor){
  brillo=valor;
}

//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D(Materiales::tipoMaterial m): material(m)
{
  b_normales_caras=false;
  b_normales_vertices=false;
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);	//GL_FILL
  glLineWidth(grosor);
  glColor3f(r,g,b);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
  glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);	//GL_FILL
  glColor3f(r,g,b);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
  glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
//int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (long unsigned int i=0;i<caras.size();i++){
  if(i%2==0)
    glColor3f(r1,g1,b1);

  else
    glColor3f(r2,g2,b2);

	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, bool selec)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
  case SOLID_ILLUMINATED_FLAT: draw_iluminacion_plana(selec); break;
  case SOLID_ILLUMINATED_GOURAUD: draw_iluminacion_suave(selec);break;
  case SELECT: draw_seleccion(r1, g1, b1); break;
	}
}

void _triangulos3D::draw_seleccion(int r, int g, int b){

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3ub(r, g, b);
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < caras.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}


void _triangulos3D::draw_iluminacion_plana(bool selec )
{
if (b_normales_caras==false) calcular_normales_caras();
//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
glEnable (GL_LIGHTING);
glShadeModel(GL_FLAT);  //GL_SMOOTH
glEnable(GL_NORMALIZE);

if(selec){
  Materiales aux(Materiales::GOMA);
glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *) &aux.getAmbiente());
glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *) &aux.getDifusa());
glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *) &aux.getEspecular());
glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,material.getBrillo());
}

else{
//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *) &material.getAmbiente());
glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *) &material.getAmbiente());
glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *) &material.getDifusa());
glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *) &material.getEspecular());
glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,material.getBrillo());
}

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (long unsigned int i=0;i<caras.size();i++){
  glNormal3fv((GLfloat *) &normales_caras[i]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
glDisable(GL_LIGHTING);
}


void _triangulos3D::calcular_normales_caras( ){
  _vertex3f a1, a2, n;
normales_caras.resize(caras.size());

for(long unsigned int i=0; i<caras.size(); i++){
	// obtener dos vectores en el triángulo y calcular el producto vectorial
	a1=vertices[caras[i]._1]-vertices[caras[i]._0];
       	a2=vertices[caras[i]._2]-vertices[caras[i]._0];
        n=a1.cross_product(a2);
	// modulo
	float m=sqrt(n.x*n.x+n.y*n.y+n.z*n.z);
	// normalización
    	normales_caras[i]= _vertex3f(n.x/m, n.y/m, n.z/m);
      
	}
  
b_normales_caras=true;
}

void _triangulos3D::calcular_normales_vertices(){
  for(long unsigned int i=0; i<vertices.size(); i++)
    normales_vertices.push_back(_vertex3f(0, 0, 0));

  for(long unsigned int i=0; i<caras.size(); i++){
    normales_vertices[caras[i]._0]+=normales_caras[i];
    normales_vertices[caras[i]._1]+=normales_caras[i];
    normales_vertices[caras[i]._2]+=normales_caras[i];
  }

    //normales_vertices[i]=_vertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    //normales_vertices[i]=vertices[i];
  for(auto it=normales_vertices.begin(); it!=normales_vertices.cend(); ++it)
    (*it)/=sqrt(it->x*it->x+it->y*it->y+it->z*it->z);


  b_normales_vertices=true;
}

void _triangulos3D::draw_iluminacion_suave(bool selec){
if (b_normales_vertices==false){
  if(!b_normales_caras)
    calcular_normales_caras();

  calcular_normales_vertices();
} 

glEnable (GL_LIGHTING);
glShadeModel(GL_SMOOTH);  //GL_SMOOTH
glEnable(GL_NORMALIZE);

if(selec){
Materiales aux(Materiales::GOMA);


glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *) &aux.getAmbiente());
glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *) &aux.getDifusa());
glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *) &aux.getEspecular());
glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,material.getBrillo());

}
else{
glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *) &material.getAmbiente());
glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *) &material.getDifusa());
glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *) &material.getEspecular());
glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,material.getBrillo());
}




glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
  for(long unsigned int i=0; i<caras.size(); i++){
    glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);

    glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
	  glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

    glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
	  glVertex3fv((GLfloat *) &vertices[caras[i]._2]);    
  }
glEnd();
glDisable(GL_LIGHTING);
}
//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam, Materiales::tipoMaterial tipo):_triangulos3D(tipo)
{
//vertices
vertices.resize(8); 
vertices[0].x=-tam/2;vertices[0].y=-tam/2;vertices[0].z=tam/2;
vertices[1].x=tam/2;vertices[1].y=-tam/2;vertices[1].z=tam/2;
vertices[2].x=tam/2;vertices[2].y=-tam/2;vertices[2].z=-tam/2;
vertices[3].x=-tam/2;vertices[3].y=-tam/2;vertices[3].z=-tam/2;
vertices[4].x=-tam/2;vertices[4].y=tam/2;vertices[4].z=tam/2;
vertices[5].x=tam/2;vertices[5].y=tam/2;vertices[5].z=tam/2;
vertices[6].x=tam/2;vertices[6].y=tam/2;vertices[6].z=-tam/2;
vertices[7].x=-tam/2;vertices[7].y=tam/2;vertices[7].z=-tam/2;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=2;caras[0]._2=1;
caras[1]._0=0;caras[1]._1=3;caras[1]._2=2;
caras[2]._0=0;caras[2]._1=1;caras[2]._2=4;
caras[3]._0=1;caras[3]._1=5;caras[3]._2=4;
caras[4]._0=1;caras[4]._1=2;caras[4]._2=5;
caras[5]._0=2;caras[5]._1=6;caras[5]._2=5;
caras[6]._0=3;caras[6]._1=6;caras[6]._2=2;
caras[7]._0=3;caras[7]._1=7;caras[7]._2=6;
caras[8]._0=0;caras[8]._1=7;caras[8]._2=3;
caras[9]._0=0;caras[9]._1=4;caras[9]._2=7;
caras[10]._0=5;caras[10]._1=7;caras[10]._2=4;
caras[11]._0=5;caras[11]._1=6;caras[11]._2=7;

/*
int c = 20;

color_pick[0] = 0.0;
color_pick[1] = 0.0;
color_pick[2] = 1.0;

triangulos=caras.size();

for (int i = 0; i < caras.size(); i++)
{
  activo.push_back(0);
  color_selec[0].push_back(c);
  color_selec[1].push_back(c);
  color_selec[2].push_back(c);

  c = c + 20; 
}
*/
color_pick[0] = 0.0;
color_pick[1] = 0.0;
color_pick[2] = 1.0;

triangulos=caras.size();

for (int i = 0; i < caras.size(); i++){
  activo.push_back(0);
  color_selec[0].push_back(0);
  color_selec[1].push_back(0);
  color_selec[2].push_back(0);  
}

int v[3]={0, 0, 1};

  recolorea(v, 1);
}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al, Materiales::tipoMaterial tipo):_triangulos3D(tipo)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
/*
int c = 20;

color_pick[0] = 0.0;
color_pick[1] = 0.0;
color_pick[2] = 1.0;

triangulos=caras.size();

for (int i = 0; i < caras.size(); i++)
{
  activo.push_back(0);
  color_selec[0].push_back(c);
  color_selec[1].push_back(c);
  color_selec[2].push_back(c);

  c = c + 20; 
}*/

color_pick[0] = 0.0;
color_pick[1] = 0.0;
color_pick[2] = 1.0;

triangulos=caras.size();

for (int i = 0; i < caras.size(); i++){
  activo.push_back(0);
  color_selec[0].push_back(0);
  color_selec[1].push_back(0);
  color_selec[2].push_back(0);  
}

int v[3]={0, 0, 1};

  recolorea(v, 1);
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);

for(int i=0; i<n_ver; i++){
  vertices[i].x=ver_ply[3*i];
  vertices[i].y=ver_ply[3*i+1];
  vertices[i].z=ver_ply[3*i+2];
}

caras.resize(n_car);

for (int i = 0; i < n_car; i++)
{
  caras[i]._0=car_ply[3*i];
  caras[i]._1=car_ply[3*i+1];
  caras[i]._2=car_ply[3*i+2];
}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion(Materiales::tipoMaterial tipo):_triangulos3D(tipo)
{
}

void _rotacion::parametros(vector<_vertex3f> perfil, int num, Eje axis)
{






  //int i,j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;
  int numVer0=0;

  // tratamiento de los vértice

  num_aux=perfil.size();
  //vertices.resize(num_aux*num);
  //Con el if else nos permite poner los puntos del perfil que no esten sobre el eje y
  //Tambien nos permite contar el numero de puntos que se encuentran sobre el eje y

  switch(axis){
    case x:{
      //Generacion de vertices
      for (int j=0;j<num;j++)
      {
          for (int i=0;i<num_aux;i++)
          {
            
            if(perfil[i].y!=0.0 or perfil[i].z!=0){
              vertice_aux.y=perfil[i].y*cos(2.0*M_PI*j/(1.0*num))+
                            perfil[i].z*sin(2.0*M_PI*j/(1.0*num));

              vertice_aux.z=-perfil[i].y*sin(2.0*M_PI*j/(1.0*num))+
                            perfil[i].z*cos(2.0*M_PI*j/(1.0*num));

/*
              vertice_aux.y=perfil[i].y*cos(2.0*M_PI*j/(1.0*num))-
                            perfil[i].z*sin(2.0*M_PI*j/(1.0*num));

              vertice_aux.z=perfil[i].y*sin(2.0*M_PI*j/(1.0*num))+
                            perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
*/


              vertice_aux.x=perfil[i].x;
            //vertices[i+j*num_aux]=vertice_aux;
              vertices.push_back(vertice_aux);             
            }

            else if(j==0){
              numVer0++;
            }
          }
      }

      //Independientemente de si el perfil tiene dos puntos sobre el eje y o no
      //Se le añaden al final del vector de vertices para que sea mas facil de trabajar
      //Al hacer las caras y al construir las tapas
      vertice_aux.x=perfil[0].x;
      vertice_aux.y=0;
      vertice_aux.z=0;
      vertices.push_back(vertice_aux);

      vertice_aux.x=perfil[perfil.size()-1].x;
      vertice_aux.y=0;
      vertice_aux.z=0;
      vertices.push_back(vertice_aux);      
      break;
    }

    case y:{
      //Generacion de vertices
      for (int j=0;j<num;j++)
      {
          for (int i=0;i<num_aux;i++)
          {
            if(perfil[i].x!=0.0 or perfil[i].z!=0.0){
              vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                            perfil[i].z*sin(2.0*M_PI*j/(1.0*num));

              vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                            perfil[i].z*cos(2.0*M_PI*j/(1.0*num));

              vertice_aux.y=perfil[i].y;
            //vertices[i+j*num_aux]=vertice_aux;
              vertices.push_back(vertice_aux);
            }

            else if(j==0){
              numVer0++;
            }
          }
      }

      //Independientemente de si el perfil tiene dos puntos sobre el eje y o no
      //Se le añaden al final del vector de vertices para que sea mas facil de trabajar
      //Al hacer las caras y al construir las tapas
      vertice_aux.x=0;
      vertice_aux.y=perfil[0].y;
      vertice_aux.z=0;
      vertices.push_back(vertice_aux);

      vertice_aux.x=0;
      vertice_aux.y=perfil[perfil.size()-1].y;
      vertice_aux.z=0;
      vertices.push_back(vertice_aux);    
      break;
    }

    case z:{
      //Generacion de vertices
      for (int j=0;j<num;j++)
      {
          for (int i=0;i<num_aux;i++)
          {
            if(perfil[i].x!=0.0 or perfil[i].y!=0.0){
/*              vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                            perfil[i].y*sin(2.0*M_PI*j/(1.0*num));

              vertice_aux.y=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                            perfil[i].y*cos(2.0*M_PI*j/(1.0*num));
*/
//VERSION MEJORADA PARA LA PRACTICA 4
              vertice_aux.x=-perfil[i].y*sin(2.0*M_PI*j/(1.0*num))+
                            perfil[i].x*cos(2.0*M_PI*j/(1.0*num));

              vertice_aux.y=perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                            perfil[i].y*cos(2.0*M_PI*j/(1.0*num));
              vertice_aux.z=perfil[i].z;
            //vertices[i+j*num_aux]=vertice_aux;
              vertices.push_back(vertice_aux);
            }

            else if(j==0){
              numVer0++;
            }
          }
      }

      //Independientemente de si el perfil tiene dos puntos sobre el eje y o no
      //Se le añaden al final del vector de vertices para que sea mas facil de trabajar
      //Al hacer las caras y al construir las tapas
      vertice_aux.x=0;
      vertice_aux.y=0;
      vertice_aux.z=perfil[0].z;
      vertices.push_back(vertice_aux);

      vertice_aux.x=0;
      vertice_aux.y=0;
      vertice_aux.z=perfil[perfil.size()-1].z;
      vertices.push_back(vertice_aux);
      break;      
    }
  }




  //Le restamos el numero de vertices que esten sobre el eje y para que se generen bien las caras
  num_aux-=numVer0;

  //Simplemente es para comprobar que lo hace bien
  //cout <<"numVer0: " <<numVer0 <<endl;

  // tratamiento de las caras 
  caras.resize((num*2*(num_aux-1))+2*(num));

  int c=0, num_ver=vertices.size()-2; //Suponemos que el perfil no tiene puntos sobre el eje generatriz
  //Cosa que hace que los calculos salgan bien y no toquen nunca los vertices de las tapas

  //Esto sirve para que figuras del tipo cono, que no tienen caras laterales, no dibujen esas caras
  if(num_aux>1){
    for (int j = 0; j < num; j++)
    {
      for (int i = 0; i < (num_aux - 1); i++)
      {
        caras[c]._0 = (i + j * num_aux) % num_ver;
        caras[c]._2 = ((j + 1) * num_aux + 1 + i) % num_ver;
        caras[c]._1 = ((j + 1) * num_aux + i) % num_ver;

        //cout <<(char)('A'+caras[c]._0) <<"\t " <<(char)('A'+caras[c]._1) <<"\t " <<(char)('A'+caras[c]._2) <<endl;

        c++;

        caras[c]._0 = (i + j * num_aux) % num_ver;
        caras[c]._2 = (1 + i + j * num_aux) % num_ver;
        caras[c]._1 = ((j + 1) * num_aux + 1 + i) % num_ver;

        //cout <<(char)('A'+caras[c]._0) <<"\t " <<(char)('A'+caras[c]._1) <<"\t " <<(char)('A'+caras[c]._2) <<endl;

        c++;
      }
    }
  }

  //cout <<"------------------------------------------" <<endl;
  //tapa inferior    
  for(int i=0; i<num; i++){
    caras[c]._0=((i+1)*num_aux) % num_ver;
    caras[c]._1=i*num_aux;
    caras[c]._2=vertices.size()-2;

    //cout <<(char)('A'+caras[c]._0) <<"\t " <<(char)('A'+caras[c]._1) <<"\t " <<(char)('A'+caras[c]._2) <<endl;

    c++;
  }
 //cout <<"------------------------------------------" <<endl;
 // tapa superior
  //El -1 lo que hace es que nos vamos al vertice mas alto del perfil anterior
  //(Con la formula sin -1 nos permite irnos a los vertices inferiores, como pasa mas arriba)
  for(int i=0; i<num; i++){
    caras[c]._0=(i+1)*num_aux-1;
    caras[c]._1=((i+2)*num_aux-1) % num_ver;
    caras[c]._2=vertices.size()-1;

    //cout <<(char)('A'+caras[c]._0) <<"\t " <<(char)('A'+caras[c]._1) <<"\t " <<(char)('A'+caras[c]._2) <<endl;
    c++;
  }
  



color_pick[0] = 0.0;
color_pick[1] = 0.0;
color_pick[2] = 1.0;

triangulos=caras.size();

for (int i = 0; i < caras.size(); i++){
  activo.push_back(0);
  color_selec[0].push_back(0);
  color_selec[1].push_back(0);
  color_selec[2].push_back(0);  
}

int v[3]={0, 0, 1};

  recolorea(v, 1);
}

//************************************************************************
// esfera
//************************************************************************
_esfera::_esfera(int radio, int num_puntos, int num_rot, Eje axis, Materiales::tipoMaterial tipo):
_rotacion(tipo)
{
  assert(radio>0.0 and num_puntos>2 and num_rot>2);
  num=num_rot;

  _vertex3f paux;

      double angulo=(M_PI)/(num_puntos-1);

  switch(axis){
    case x:
      paux.y=0;
      paux.x=radio;
      paux.z=0;

      perfil.push_back(paux);

      for(int i=1; i<num_puntos-1; i++){
        paux.y=perfil[i-1].y*cos(angulo)-perfil[i-1].x*sin(angulo);
        paux.x=perfil[i-1].y*sin(angulo)+perfil[i-1].x*cos(angulo);
        paux.z=0;
        perfil.push_back(paux);
      }

      //Hago el ultimo punto del perfil aqui porque luego no sale 0 exacto y 
      //tiene problemas en el metodo parametro.
      paux.y=0;
      paux.x=-radio;
      paux.z=0;
      perfil.push_back(paux);
      break;


    case y:
      paux.x=0;
      paux.y=-radio;
      paux.z=0;


      perfil.push_back(paux);

      for(int i=1; i<num_puntos-1; i++){
        paux.x=perfil[i-1].x*cos(angulo)-perfil[i-1].y*sin(angulo);
        paux.y=perfil[i-1].x*sin(angulo)+perfil[i-1].y*cos(angulo);
        paux.z=0;
        perfil.push_back(paux);
      }

      //Hago el ultimo punto del perfil aqui porque luego no sale 0 exacto y 
      //tiene problemas en el metodo parametro.
      paux.x=0;
      paux.y=radio;
      paux.z=0;
      perfil.push_back(paux);      
      break;

    case z:
      paux.x=0;
      paux.z=-radio;
      paux.y=0;


      perfil.push_back(paux);

      for(int i=1; i<num_puntos-1; i++){
        paux.x=perfil[i-1].x*cos(angulo)-perfil[i-1].z*sin(angulo);
        paux.z=perfil[i-1].x*sin(angulo)+perfil[i-1].z*cos(angulo);
        paux.y=0;
        perfil.push_back(paux);
      }

      //Hago el ultimo punto del perfil aqui porque luego no sale 0 exacto y 
      //tiene problemas en el metodo parametro.
      paux.x=0;
      paux.z=radio;
      paux.y=0;
      perfil.push_back(paux);      
      break;
  }


  //vertices=perfil;
  //Lo pongo en el constructor para simplificar las cosas
  //Pero es recomendable ponerlo en el main
  //cout<<"Esfera: ";
  parametros(perfil, num_rot, axis);

  //cout <<"\nNumero de caras: " <<caras.size() <<endl <<"Numero de vertices: " <<vertices.size() <<endl <<endl;
}


void _esfera::calcular_normales_vertices( ){
  cout <<"ESFERA OVERRIDE DE CALCULAR NORMALES" <<endl;
  /*
  for(long unsigned int i=0; i<vertices.size(); i++)
    normales_vertices.push_back(_vertex3f(0, 0, 0));
*/

  normales_vertices=vertices;

  for(long unsigned int i=0; i<vertices.size(); i++)
    normales_vertices[i]/=sqrt(normales_vertices[i].x*normales_vertices[i].x+normales_vertices[i].y*normales_vertices[i].y+normales_vertices[i].z*normales_vertices[i].z);

  b_normales_vertices=true;
}

//************************************************************************
// cono
//************************************************************************
_cono::_cono(double radio, double h, int num, Eje axis, Materiales::tipoMaterial tipo):
_rotacion(tipo)
{
  assert(radio>0.0 and h>0.0 and num>2);
  this->num=num;

  _vertex3f paux;

  //axis=x;
  switch(axis){
    case x:
    /*
      paux.y=0;
      paux.x=h/2;
      paux.z=0;

      perfil.push_back(paux);*/

      paux.y=radio;
      paux.x=h/2;
      paux.z=0;

      perfil.push_back(paux);

      paux.y=0;
      paux.x=-h/2;
      paux.z=0;  

      perfil.push_back(paux);
      break;

    case y:
    /*
      paux.x=0;
      paux.y=-h/2;
      paux.z=0;

      perfil.push_back(paux);*/

      paux.x=radio;
      paux.y=-h/2;
      paux.z=0;

      perfil.push_back(paux);

      paux.x=0;
      paux.y=h/2;
      paux.z=0;  

      perfil.push_back(paux);
      break;

    case z:
    /*
      paux.x=0;
      paux.z=-h/2;
      paux.y=0;

      perfil.push_back(paux);*/

      paux.x=radio;
      paux.z=-h/2;
      paux.y=0;

      perfil.push_back(paux);

      paux.x=0;
      paux.z=h/2;
      paux.y=0;  

      perfil.push_back(paux);
      break;
  }

  //vertices=perfil;
  //cout<<"Cono: ";
  parametros(perfil, num, axis);

  //cout <<"\nNumero de caras: " <<caras.size() <<endl <<"Numero de vertices: " <<vertices.size() <<endl <<endl;
}

//************************************************************************
// cilindro
//************************************************************************

_cilindro::_cilindro(double radio, double h, int num, Eje axis, Materiales::tipoMaterial tipo):_rotacion(tipo)
{
  assert(radio>0.0 and h>0.0 and num>2);
  _vertex3f paux;

  //axis=z;
  switch(axis){
    case x:
      paux.y=radio;
      paux.x=h/2;
      paux.z=0;

      perfil.push_back(paux);


      paux.y=radio;
      paux.x=-h/2;
      paux.z=0;

      perfil.push_back(paux);
      break;

    case y:
      paux.x=radio;
      paux.y=-h/2;
      paux.z=0;

      perfil.push_back(paux);
      

      paux.x=radio;
      paux.y=h/2;
      paux.z=0;

      perfil.push_back(paux);
      break;

    case z:
      paux.x=radio;
      paux.z=-h/2;
      paux.y=0;

      perfil.push_back(paux);

      paux.x=radio;
      paux.z=h/2;
      paux.y=0;

      perfil.push_back(paux);
        break;
  }
  //cout <<"CILINDRO---------------------------------" <<endl;
  parametros(perfil, num, axis);
  /*char cont='A';
  for(auto it=vertices.cbegin(); it!=vertices.cend(); ++it)
    cout <<cont++ <<": " <<it->_0 <<"\t" <<it->_1 <<"\t" <<it->_2 <<endl;*/

//cout <<"CILINDRO---------------------------------" <<endl;    
}


//************************************************************************
// clase ply_rot
//************************************************************************

_ply_rot::_ply_rot(const char *file, int rot, Eje axis, Materiales::tipoMaterial tipo):
material(tipo)
{
  
  int n_perfil,n_car;

  vector<float> ver_ply ;
  vector<int>   car_ply ;
  
  _file_ply::read(file, ver_ply, car_ply );

  n_perfil=ver_ply.size()/3;
  n_car=car_ply.size()/3;

  printf("Number of perfil=%d\nNumber of faces=%d\n", n_perfil, n_car);

  perfil.resize(n_perfil);

  for(int i=0; i<n_perfil; i++){
    perfil[i].x=ver_ply[3*i];
    perfil[i].y=ver_ply[3*i+1];
    perfil[i].z=ver_ply[3*i+2];
  }

  _rotacion aux;

  aux.parametros(perfil, rot, axis);

  vertices=aux.vertices;
  caras=aux.caras;


color_pick[0] = 0.0;
color_pick[1] = 0.0;
color_pick[2] = 1.0;

triangulos=caras.size();

for (int i = 0; i < caras.size(); i++){
  activo.push_back(0);
  color_selec[0].push_back(0);
  color_selec[1].push_back(0);
  color_selec[2].push_back(0);  
}

int v[3]={0, 0, 1};

  recolorea(v, 1); 
}

//************************************************************************
// caza
//************************************************************************

// Version centrada
void _cuerpo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
 float rf1=r1, gf1=g1, bf1=b1, rf2=r2, gf2=g2, bf2=b2;

 if(tipo==ESPECIAL){
   rf1=0;
   gf1=0.89;
   bf1=0.134;

   rf2=gf2=bf2=0.22;
 }
 //Air intakes
  if(tipo==NORMAL)
    base.push_back(_cubo(CUBO_TAM, material.mat));
  else
    base.push_back(_cubo(CUBO_TAM, Materiales::ALUMINIO));

  glPushMatrix();
  glTranslatef(-0.9218, 0.1132, 1.4685);
  glRotatef(3.59, 1, 0, 0);
  glScalef(0.432, 0.406, 1);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0.9218, 0.1132, 1.4685);
  glRotatef(3.59, 1, 0, 0);
  glScalef(0.432, 0.406, 1);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();


//Frame
  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, -0.2509, 1.5759);
  glScalef(0.59, 0.302, 3.62);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, 0.0721, 3.468);
  glRotatef(3.59, 1, 0, 0);
  glScalef(0.59, 0.116, 1.031);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, 0.1484, 0.8318);
  glRotatef(4.92, 1, 0, 0);
  glScalef(0.925, 0.406, 0.466);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();

  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, 0.1692, -0.4898);
  glScalef(0.925, 0.406, 1);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  


//Laterales del instake que se curvan hacia dentro
  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-0.9414, 0.1692, -0.4284);
  glRotatef(-8.05, 0, 1, 0);
  glScalef(0.270, 0.406, 0.976);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  

  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0.9414, 0.1692, -0.4284);
  glRotatef(8.05, 0, 1, 0);
  glScalef(0.270, 0.406, 0.976);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  

//Alisadores de curvas
  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0.5176, -0.3433, -0.0620);
  glRotatef(-13.9, 0, 1, 0);
  glScalef(0.270, 0.137, 1.061);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  

  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-0.5176, -0.3433, -0.0620);
  glRotatef(13.9, 0, 1, 0);
  glScalef(0.270, 0.137, 1.061);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  


//Sujeta alas, los que permite que se puedan plegar
  //1 izquierda y derecha
  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(1.2496, 0.323, -0.7854);
  glRotatef(-38.4, 0, 1, 0);
  glScalef(0.451, 0.209, 0.29);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  

  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-1.2496, 0.323, -0.7854);
  glRotatef(38.4, 0, 1, 0);
  glScalef(0.451, 0.209, 0.29);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();

  //2 izquierda y derecha
  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(1.4784, 0.323, -0.2166);
  glRotatef(9.56, 0, 1, 0);
  glScalef(0.381, 0.209, 0.46);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-1.4784, 0.323, -0.2166);
  glRotatef(-9.56, 0, 1, 0);
  glScalef(0.381, 0.209, 0.46);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  


  //3 izquierda y derecha
  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(1.3179, 0.323, 0.4604);
  glRotatef(-30.9, 0, 1, 0);
  glScalef(0.381, 0.209, 0.56);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();    


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-1.3179, 0.323, 0.4604);
  glRotatef(30.9, 0, 1, 0);
  glScalef(0.381, 0.209, 0.56);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();      


//Alisadores de curva cola
  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, -0.0379, -2.0821);
  glScalef(1.061, 0.24, 0.651);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();    


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, 0.0713, -3.3869);
  glScalef(1.061, 0.123, 0.651);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();    

  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, 0.0713, -4.6922);
  glScalef(1.061, 0.087, 0.651);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();      


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, -0.0844, -3.3869);
  glRotatef(6.37, 1, 0, 0);
  glScalef(1.061, 0.123, 0.651);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();    


//Estabilizador de cola
  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, 0.8568, -2.5387);
  glRotatef(-71.4, 1, 0, 0);
  glScalef(0.126, 1.08, 0.435);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();    

  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, 1.8809, -4.4713);
  glRotatef(-55.3, 1, 0, 0);
  glScalef(0.126, 1.96, 0.435);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();    


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, 1.6522, -4.8354);
  glRotatef(-37.5, 1, 0, 0);
  glScalef(0.126, 1.33, 0.435);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();    



  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, 0.578, -5.0584);
  glScalef(0.126, 0.247, 0.509);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();      


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, 2.8776, -6.2732);
  glScalef(0.126, 0.477, 0.435);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();    


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, 2.8706, -6.787);
  glRotatef(-33.3, 1, 0, 0);
  glScalef(0.126, 0.437, 0.195);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix(); 


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0, 3.198, -6.9019);
  glScalef(0.126, 0.157, 0.195);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();           

//Ahora la parte de los cilindros

//Parte de abajo del caza
  if(tipo==NORMAL)
    esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
  else
    esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, Materiales::ALUMINIO));

  glPushMatrix();
  glTranslatef(0, -0.524, 1.5759);
  glRotatef(270, 1, 0, 0);
  glScalef(0.595, 3.620, 0.279);
  esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();


  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(0.2268, -0.504, -0.2723);
  glRotatef(-13.9, 0, 1, 0);
  glRotatef(270, 1, 0, 0);
  glScalef(0.608, 0.899, 0.279);
  esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();


  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(-0.2268, -0.504, -0.2723);
  glRotatef(13.9, 0, 1, 0);
  glRotatef(270, 1, 0, 0);
  glScalef(0.608, 0.899, 0.279);
  esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();






  //Parte de arriba delantera
  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(0, 0.2058, 2.8629);
  glRotatef(93.2, 1, 0, 0);
  glScalef(0.595, 2.297, 0.279);
  esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();       


  //Cilindro de arriba que recorre media aeronave
  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(0, 0.6863, -1.3726);
  glRotatef(88.2, 1, 0, 0);
  glScalef(0.226, 2.951, 0.235);
  esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();    


  //Parte de la cola
  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(0, -0.3637, -1.58);
  glRotatef(271, 1, 0, 0);
  glScalef(1.059, 0.538, 0.422);
  esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();


  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(0, 0.171, -2.7727);
  glRotatef(270, 1, 0, 0);
  glScalef(1.059, 1.257, 0.422);
  esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();


  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(0, -0.2311, -3.0631);
  glRotatef(276, 1, 0, 0);
  glScalef(1.059, 0.990, 0.423);
  esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();


  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(0, 0.1517, -4.4509);
  glRotatef(269, 1, 0, 0);
  glScalef(1.059, 0.41, 0.422);
  esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();


  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(0, -0.0391, -4.6683);
  glRotatef(276, 1, 0, 0);
  glScalef(1.059, 0.632, 0.422);
  esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  


  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(0, 0.1189, -5.1279);
  glRotatef(266, 1, 0, 0);
  glScalef(1.059, 0.41, 0.422);
  esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  


//Escape del turbojet
if(tipo==NORMAL)
  esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
  else
  esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, Materiales::OBSIDIANA));

  glPushMatrix();
  glTranslatef(0.4586, 0.0771, -5.5719);
  glRotatef(270, 1, 0, 0);
  glScalef(0.321, 0.129, 0.321);
  if(tipo==NORMAL)
    esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  else
    esquinas[esquinas.size()-1].draw(modo, 0.43, 0.43, 0.43, 0.43, 0.43, 0.43, grosor, s);
  glPopMatrix();

  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(-0.4586, 0.0771, -5.5719);
  glRotatef(270, 1, 0, 0);
  glScalef(0.321, 0.129, 0.321);
  if(tipo==NORMAL)
    esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  else
    esquinas[esquinas.size()-1].draw(modo, 0.43, 0.43, 0.43, 0.43, 0.43, 0.43, grosor, s);
  glPopMatrix();



//Nariz
if(tipo==ESPECIAL){
  nariz.material.setValores(Materiales::ALUMINIO);
  nariz_curva.material.setValores(Materiales::ALUMINIO);
}
else{
  nariz.material.setValores(material.mat);
  nariz_curva.material.setValores(material.mat);  
}
  glPushMatrix();
  glTranslatef(0, -0.3454, 6.407);
  glRotatef(94.7, 1, 0, 0);
  glScalef(0.475, 0.73, 0.502);
  if(tipo==NORMAL)
    nariz.draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  else
    nariz.draw(modo, 0.2, 0.2, 0.2, 0.09, 0.09, 0.09, grosor, s);
  glPopMatrix();  


//Curva de la nariz
  glPushMatrix();
  glTranslatef(0, -0.2473, 5.201);
  glRotatef(4.72, 1, 0, 0);
  glScalef(0.557, 0.557, 1.112);
  if(tipo==NORMAL)
    nariz_curva.draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  else
    nariz_curva.draw(modo, 0.2, 0.2, 0.2, 0.09, 0.09, 0.09, grosor, s);
  glPopMatrix();  


//Filos del timon
  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
  if(tipo==NORMAL)
    esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
  else
    esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, Materiales::ALUMINIO));

  glPushMatrix();
  glTranslatef(0, 1.095, -2.1481);
  glRotatef(-71.4, 1, 0, 0);
  glScalef(0.12, 1.2, 0.232);
  esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();


  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(0, 2.3451, -4.5454);
  glRotatef(-55.3, 1, 0, 0);
  glScalef(0.12, 1.64, 0.232);
  esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();


  //esquinas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(0, 3.2411, -6.4318);
  glRotatef(90, 1, 0, 0);
  glScalef(0.12, 0.67, 0.232);
  esquinas[esquinas.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  
}


//************************************************************************
void _alas::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
  //Cubos con la forma primitiva de las alas
    //derecha
  base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-3.354, 2.1596, -1.5932);
  glRotatef(-15.9, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.38);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();     


  base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-3.3537, 2.1749, -1.1572);
  glRotatef(-23.5, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.3);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();     


  base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-5.7552, 1.9762, -2.4362);
  glRotatef(-15.9, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(0.1, 0.105, 0.23);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();    


  base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-5.8797, 1.9762, -2.7862);
  glRotatef(-15.9, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(0.16, 0.075, 0.11);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();    

  //izquierda
  base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(3.354, 2.1596, -1.5932);
  glRotatef(15.9, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.38);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();     


  base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(3.3537, 2.1749, -1.1572);
  glRotatef(23.5, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.3);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();    


  base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(5.7552, 1.9762, -2.4362);
  glRotatef(15.9, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(0.1, 0.105, 0.23);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();   


  base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(5.8797, 1.9762, -2.7862);
  glRotatef(15.9, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(0.16, 0.075, 0.11);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();  



//Cilindros para el filo de las alas
  //derecha
  filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(-3.6565, 2.1568, -1.0302);  
  glRotatef(-24.8, 0, 1, 0);
  glRotatef(94.6, 0, 0, 1);
  glScalef(0.12, 2.096, 0.366);
  filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();  


  filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(-5.8499, 1.9745, -2.315);
  glRotatef(90, 1, 0, 0);  
  glRotatef(-14.5, 0, 0, 1);
  glRotatef(-4.6, 0, 1, 0);
  glScalef(0.165, 0.465, 0.12);
  filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();  

  //izquierda       
  filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(3.6565, 2.1568, -1.0302);
  glRotatef(24.8, 0, 1, 0);
  glRotatef(-94.6, 0, 0, 1);
  glScalef(0.12, 2.096, 0.366);
  filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();  


  filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
  glPushMatrix();
  glTranslatef(5.8499, 1.9745, -2.315);
  glRotatef(90, 1, 0, 0);  
  glRotatef(14.5, 0, 0, 1);
  glRotatef(4.6, 0, 1, 0);
  glScalef(0.165, 0.465, 0.12);
  filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();  

  //Esferas para las esquinas
  //derecha
  esquinas.push_back(_esfera(ES_RADIO, NUM, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(-5.6556, 1.9831, -1.8168);
  glRotatef(4.6, 0, 0, 1);
  glScalef(0.237, 0.12, 0.237);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();    


  //izquierda
  esquinas.push_back(_esfera(ES_RADIO, NUM, NUM, eje, material.mat));

  glPushMatrix();
  glTranslatef(5.6556, 1.9831, -1.8168);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(0.237, 0.12, 0.237);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();      
}

//************************************************************************

void _ala_izda::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
 float rf1=r1, gf1=g1, bf1=b1, rf2=r2, gf2=g2, bf2=b2;

 if(tipo==ESPECIAL){
   rf1=0;
   gf1=0.89;
   bf1=0.134;

   rf2=gf2=bf2=0.22;
 }  
  
  //Cubos con la forma primitiva de las alas
  //izquierda
  if(tipo==NORMAL)
    base.push_back(_cubo(CUBO_TAM, material.mat));
  else
    base.push_back(_cubo(CUBO_TAM, Materiales::ALUMINIO));

  glPushMatrix();
  glTranslatef(3.354, 2.1596, -1.5932);
  glRotatef(15.9, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.38);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();     


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(3.3537, 2.1749, -1.1572);
  glRotatef(23.5, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.3);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();    


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(5.7552, 1.9762, -2.4362);
  glRotatef(15.9, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(0.1, 0.105, 0.23);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();   


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(5.8797, 1.9762, -2.7862);
  glRotatef(15.9, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(0.16, 0.075, 0.11);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  



//Cilindros para el filo de las alas
  //izquierda   
  if(tipo==NORMAL)
    filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
  else
    filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, Materiales::ALUMINIO));

  glPushMatrix();
  glTranslatef(3.6565, 2.1568, -1.0302);
  glRotatef(24.8, 0, 1, 0);
  glRotatef(-94.6, 0, 0, 1);
  glScalef(0.12, 2.096, 0.366);
  filos[filos.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  


  //filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
  glPushMatrix();
  glTranslatef(5.8499, 1.9745, -2.315);
  glRotatef(90, 1, 0, 0);  
  glRotatef(14.5, 0, 0, 1);
  glRotatef(4.6, 0, 1, 0);
  glScalef(0.165, 0.465, 0.12);
  filos[filos.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  

  //Esferas para las esquinas   
  //izquierda
  if(tipo==NORMAL)
    esquina.material.setValores(material.mat);
  else
    esquina.material.setValores(Materiales::ALUMINIO);

  glPushMatrix();
  glTranslatef(5.6556, 1.9831, -1.8168);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(0.237, 0.12, 0.237);
  esquina.draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();      
}

//************************************************************************
void _ala_dcha::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
 float rf1=r1, gf1=g1, bf1=b1, rf2=r2, gf2=g2, bf2=b2;

 if(tipo==ESPECIAL){
   rf1=0;
   gf1=0.89;
   bf1=0.134;

   rf2=gf2=bf2=0.22;
 }   
  
  //Cubos con la forma primitiva de las alas
    //derecha
    if(tipo==NORMAL)
      base.push_back(_cubo(CUBO_TAM, material.mat));
    else
      base.push_back(_cubo(CUBO_TAM, Materiales::ALUMINIO));

  glPushMatrix();
  glTranslatef(-3.354, 2.1596, -1.5932);
  glRotatef(-15.9, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.38);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();     


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-3.3537, 2.1749, -1.1572);
  glRotatef(-23.5, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.3);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();     


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-5.7552, 1.9762, -2.4362);
  glRotatef(-15.9, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(0.1, 0.105, 0.23);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();    


  //base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-5.8797, 1.9762, -2.7862);
  glRotatef(-15.9, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(0.16, 0.075, 0.11);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();    



//Cilindros para el filo de las alas
  //derecha
  if(tipo==NORMAL)
    filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
  else
    filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, Materiales::ALUMINIO));

  glPushMatrix();
  glTranslatef(-3.6565, 2.1568, -1.0302);  
  glRotatef(-24.8, 0, 1, 0);
  glRotatef(94.6, 0, 0, 1);
  glScalef(0.12, 2.096, 0.366);
  filos[filos.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  


  glPushMatrix();
  glTranslatef(-5.8499, 1.9745, -2.315);
  glRotatef(90, 1, 0, 0);  
  glRotatef(-14.5, 0, 0, 1);
  glRotatef(-4.6, 0, 1, 0);
  glScalef(0.165, 0.465, 0.12);
  filos[filos.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  

  //Esferas para las esquinas
  //derecha
  if(tipo==NORMAL)
    esquina.material.setValores(material.mat);
  else
    esquina.material.setValores(Materiales::ALUMINIO);

  glPushMatrix();
  glTranslatef(-5.6556, 1.9831, -1.8168);
  glRotatef(4.6, 0, 0, 1);
  glScalef(0.237, 0.12, 0.237);
  esquina.draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();        
}

//************************************************************************

void _ala_td::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
 float rf1=r1, gf1=g1, bf1=b1, rf2=r2, gf2=g2, bf2=b2;

 if(tipo==ESPECIAL){
   rf1=0;
   gf1=0.89;
   bf1=0.134;

   rf2=gf2=bf2=0.22;
 }  

  //Empiezo por la forma basica (los cubos)
    //derecha
    if(tipo==NORMAL)
      base.push_back(_cubo(CUBO_TAM, material.mat));
    else
      base.push_back(_cubo(CUBO_TAM, Materiales::ALUMINIO));

    glPushMatrix();
    glTranslatef(-1.0904, -0.035261, -0.61322);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(31.4, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.451, 0.045, 0.68);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix();      



    glPushMatrix();
    glTranslatef(-0.5252, -0.014561, 0.26328);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(35.2, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.451, 0.045, 0.4);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix(); 



    glPushMatrix();
    glTranslatef(-0.5423, -0.012661, -0.62752);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.32, 0.045, 0.411);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix(); 



    glPushMatrix();
    glTranslatef(-1.5295, -0.045961, -1.14682);
    glRotatef(1.19, 1, 0, 0);
    glRotatef(1.66, 0, 0, 1);
    glScalef(0.4, 0.045, 0.181);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix(); 



    glPushMatrix();
    glTranslatef(-0.4695, -0.017161, 0.73348);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(35.2, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.231, 0.045, 0.330);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix(); 



    glPushMatrix();
    glTranslatef(-0.3154, -0.016461, 1.14298);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(35.2, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.121, 0.045, 0.16);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix(); 


    glPushMatrix();
    glTranslatef(-0.1629, -0.001461, 0.29108);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.16, 0.045, 1.222);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix(); 



    glPushMatrix();
    glTranslatef(-0.8785, -0.020161, -1.18222);
    glRotatef(1.19, 1, 0, 0);
    glRotatef(-18, 0, 1, 0);
    glRotatef(1.66, 0, 0, 1);
    glScalef(1.06, 0.045, 0.181);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix(); 


//Ahora los cilindros que hacen que los filos sean redondeados
  //derecha
    if(tipo==NORMAL)
      filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
    else
      filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, Materiales::ALUMINIO));

    glPushMatrix();
    glTranslatef(-1.0211, -0.034261, 0.33208);
    glRotatef(35.2, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glRotatef(88.9, 1, 0, 0);       
    glScalef(0.15, 1.56, 0.04);
    filos[filos.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix();   



    glPushMatrix();
    glTranslatef(-1.9383, -0.049661, -1.32752);
    glRotatef(1.19, 0, 0, 1);
    glRotatef(91.7, 1, 0, 0);       
    glScalef(0.15, 0.34, 0.04);
    filos[filos.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix();   


//Esferas de las esquinas
  //derecha
    if(tipo==NORMAL)
      esquina.material.setValores(material.mat);
    else
      esquina.material.setValores(Materiales::ALUMINIO);

    glPushMatrix();
    glTranslatef(-1.9503, -0.058461, -0.95252);
    glRotatef(3.9, 1, 0, 0);       
    glRotatef(5.9, 0, 0, 1);
    glScalef(0.135, 0.035, 0.125);
    esquina.draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix();                
}


void _ala_ti::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
 float rf1=r1, gf1=g1, bf1=b1, rf2=r2, gf2=g2, bf2=b2;

 if(tipo==ESPECIAL){
   rf1=0;
   gf1=0.89;
   bf1=0.134;

   rf2=gf2=bf2=0.22;
 }  
 
  //Empiezo por la forma basica (los cubos)
    //izquierda
    if(tipo==NORMAL)
      base.push_back(_cubo(CUBO_TAM, material.mat));
    else
      base.push_back(_cubo(CUBO_TAM, Materiales::ALUMINIO));

    glPushMatrix();
    glTranslatef(1.0904, -0.035261, -0.61322);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(-31.4, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.451, 0.045, 0.68);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix();     


    glPushMatrix();
    glTranslatef(0.5252, -0.014561, 0.26328);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(-35.2, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.451, 0.045, 0.4);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.5423, -0.012661, -0.62752);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.32, 0.045, 0.411);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix();          



    glPushMatrix();
    glTranslatef(1.5295, -0.045961, -1.14682);
    glRotatef(1.19, 1, 0, 0);
    glRotatef(-1.66, 0, 0, 1);
    glScalef(0.4, 0.045, 0.181);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix();     



    glPushMatrix();
    glTranslatef(0.4695, -0.017161, 0.73348);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(-35.2, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.231, 0.045, 0.330);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix();     



    glPushMatrix();
    glTranslatef(0.3154, -0.016461, 1.14298);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(-35.2, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.121, 0.045, 0.16);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix();     



    glPushMatrix();
    glTranslatef(0.1629, -0.001461, 0.29108);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.16, 0.045, 1.222);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix();     



    glPushMatrix();
    glTranslatef(0.8785, -0.020161, -1.18222);
    glRotatef(1.19, 1, 0, 0);
    glRotatef(18, 0, 1, 0);
    glRotatef(-1.66, 0, 0, 1);
    glScalef(1.06, 0.045, 0.181);
    base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix(); 


//Ahora los cilindros que hacen que los filos sean redondeados
  //izquierda

    if(tipo==NORMAL)
      filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
    else
      filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, Materiales::ALUMINIO));

    glPushMatrix();
    glTranslatef(1.0211, -0.034261, 0.33208);
    glRotatef(-35.2, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glRotatef(88.9, 1, 0, 0);       
    glScalef(0.15, 1.56, 0.04);
    filos[filos.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix();   


    glPushMatrix();
    glTranslatef(1.9383, -0.049661, -1.32752);
    glRotatef(-1.19, 0, 0, 1);
    glRotatef(91.7, 1, 0, 0);       
    glScalef(0.15, 0.34, 0.04);
    filos[filos.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix();   


//Esferas de las esquinas
  //izquierda
    if(tipo==NORMAL)
      esquina.material.setValores(material.mat);
    else
      esquina.material.setValores(Materiales::ALUMINIO);


    glPushMatrix();
    glTranslatef(1.9503, -0.058461, -0.95252);
    glRotatef(3.9, 1, 0, 0);
    glRotatef(-5.9, 0, 0, 1);
    glScalef(0.135, 0.035, 0.125);
    esquina.draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
    glPopMatrix();                 
}



//************************************************************************

//Version centrada
void _ventana_movil::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
  //Primero los cubos
  if(tipo==NORMAL)
    base.push_back(_cubo(CUBO_TAM, material.mat));
  else
    base.push_back(_cubo(CUBO_TAM, Materiales::CRISTAL));

  glPushMatrix();
  glTranslatef(0, -0.64416, 1.204);
  glRotatef(1.1, 1, 0, 0);
  glScalef(0.324, 0.064, 1.21);
  if(tipo==NORMAL)
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  else
    base[base.size()-1].draw(modo, 0.35, 0.35, 0.35, 0.2, 0.2, 0.2, grosor, s);
  glPopMatrix(); 

  //derecha

  glPushMatrix();
  glTranslatef(-0.2509, -0.44495, 1.1041);
  glRotatef(-11.3, 0, 0, 1);
  glScalef(0.05, 0.16, 1.11);
  //base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);

  if(tipo==NORMAL)
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  else
    base[base.size()-1].draw(modo, 0, 0.56, 0.68, 0, 0.82, 1, grosor, s);  
  glPopMatrix(); 


  //izquierda

  glPushMatrix();
  glTranslatef(0.2509, -0.44495, 1.1041);
  glRotatef(11.3, 0, 0, 1);
  glScalef(0.05, 0.16, 1.11);
  //base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);

  if(tipo==NORMAL)
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  else
    base[base.size()-1].draw(modo, 0, 0.56, 0.68, 0, 0.82, 1, grosor, s);  
  glPopMatrix(); 



  //Ahora los cilindros
  if(tipo==NORMAL)
    filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
  else
    filos.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, Materiales::CRISTAL));

  glPushMatrix();
  glTranslatef(0, -0.26732, 0.97712);
  glRotatef(90, 1, 0, 0);
  glScalef(0.265, 0.985, 0.265);
  if(tipo==NORMAL)
    filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  else
    filos[filos.size()-1].draw(modo, 0, 0.56, 0.68, 0, 0.82, 1, grosor, s);
  glPopMatrix();     




  glPushMatrix();
  glTranslatef(0, -0.28891, 2.0103);
  glRotatef(104, 1, 0, 0);
  glScalef(0.265, 0.115, 0.265);
  if(tipo==NORMAL)
    filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  else
    filos[filos.size()-1].draw(modo, 0, 0.56, 0.68, 0, 0.82, 1, grosor, s);
  glPopMatrix(); 
}


//************************************************************************
//Version centrado
void _ventana_fija::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){

  if(tipo==NORMAL)
    base.push_back(_cubo(CUBO_TAM, material.mat));
  else
    base.push_back(_cubo(CUBO_TAM, Materiales::CRISTAL));

  glPushMatrix();
  glTranslatef(-0.2208, -0.47467, 2.4468);
  glRotatef(-14.5, 0, 0, 1);
  glRotatef(12.1, 0, 1, 0);
  glRotatef(7.47, 1, 0, 0);
  glScalef(0.05, 0.16, 0.26);
  //base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);

  if(tipo==NORMAL)
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  else
    base[base.size()-1].draw(modo, 0, 0.56, 0.68, 0, 0.82, 1, grosor, s);  
  glPopMatrix();   



  glPushMatrix();
  glTranslatef(0.2208, -0.47467, 2.4468);
  glRotatef(14.5, 0, 0, 1);
  glRotatef(-12.1, 0, 1, 0);
  glRotatef(7.47, 1, 0, 0);
  glScalef(0.05, 0.16, 0.26);
  //base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);

  if(tipo==NORMAL)
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  else
    base[base.size()-1].draw(modo, 0, 0.56, 0.68, 0, 0.82, 1, grosor, s);  
  glPopMatrix();   


  //cilindro
  if(tipo==NORMAL)
    filos.material.setValores(material.mat);
  else
    filos.material.setValores(Materiales::CRISTAL);

  glPushMatrix();
  glTranslatef(0, -0.403, 2.26);
  glRotatef(117, 1, 0, 0);
  glScalef(0.265, 0.225, 0.265);
  //filos.draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);

  if(tipo==NORMAL)
    filos.draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  else
    filos.draw(modo, 0, 0.56, 0.68, 0, 0.82, 1, grosor, s);
  
  glPopMatrix(); 


  //Cono
  if(tipo==NORMAL)
    pico.material.setValores(material.mat);
  else
    pico.material.setValores(Materiales::CRISTAL);

  glPushMatrix();
  glTranslatef(0, -0.60895, 2.9173);
  glRotatef(106, 1, 0, 0);
  glScalef(0.249, 0.429, 0.249);
  //pico.draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);

  if(tipo==NORMAL)
    pico.draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  else
    pico.draw(modo, 0, 0.56, 0.68, 0, 0.82, 1, grosor, s);  
  glPopMatrix();

}


//************************************************************************

//************************************************************************

void _flaps::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
  //derecho
  flaps.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-3.5797, 2.1596, -2.0297);
  glRotatef(-14.6, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(2.23, 0.08, 0.26);
  flaps[flaps.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();

  //izquierdo
  flaps.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(3.5797, 2.1596, -2.0297);
  glRotatef(14.6, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(2.23, 0.08, 0.26);
  flaps[flaps.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();
}


//************************************************************************

//************************************************************************

void _flap::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
  float rf1=r1, gf1=g1, bf1=b1, rf2=r2, gf2=g2, bf2=b2;

  if(tipo==ESPECIAL){
    rf1=0;
    gf1=1;
    bf1=0;

    rf2=0;
    gf2=0.4;
    bf2=0;
  }

  if(tipo==NORMAL){
    flap.material.setValores(material.mat);
  }
  else
  {
    flap.material.setValores(Materiales::ALUMINIO);
  }

  //izquierdo
  glPushMatrix();
  glScalef(2.23, 0.08, 0.26);
  flap.draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();
}

//************************************************************************


void _frenos_delanteros::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
  //derecho
  base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-3.4478, 2.2518, -1.7708);
  glRotatef(-15.9, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(1.29, 0.02, 0.18);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();  

  //izquierdo
  base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(3.4478, 2.2518, -1.7708);
  glRotatef(15.9, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(1.29, 0.02, 0.18);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();    
}

//************************************************************************

void _freno_individual::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
  float rf1=r1, gf1=g1, bf1=b1, rf2=r2, gf2=g2, bf2=b2;

  if(tipo==ESPECIAL){
    rf1=0;
    gf1=1;
    bf1=0;

    rf2=0;
    gf2=0.4;
    bf2=0;
  }

  if(tipo==NORMAL)
    base.material.setValores(material.mat);
  else
    base.material.setValores(Materiales::ALUMINIO);

  glPushMatrix();
  glTranslatef(0, 0, -0.18);
  glScalef(1.29, 0.02, 0.18);
  base.draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  
}

//************************************************************************

//Version centrado
void _timon::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
  float rf1=r1, gf1=g1, bf1=b1, rf2=r2, gf2=g2, bf2=b2;

  if(tipo==ESPECIAL){
    rf1=0;
    gf1=1;
    bf1=0;

    rf2=0;
    gf2=0.4;
    bf2=0;
  }  
  
  //Marco exterior
  if(tipo==NORMAL)
    base.push_back(_cubo(CUBO_TAM, material.mat));  
  else
    base.push_back(_cubo(CUBO_TAM, Materiales::ALUMINIO));  
      
  

  glPushMatrix();
  glTranslatef(0, -0.735068, 0.57972);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.48, 0.05);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix(); 



  glPushMatrix();
  glTranslatef(0, -0.013668, -0.35948);
  glRotatef(-33.5, 1, 0, 0);
  glScalef(0.126, 0.9, 0.05);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();   



  glPushMatrix();
  glTranslatef(0, 0.725832, -0.52188);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.34, 0.05);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix(); 



  glPushMatrix();
  glTranslatef(0, -0.006568, 0.36032);
  glRotatef(-37.8, 1, 0, 0);
  glScalef(0.126, 0.95, 0.05);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();     

  //Relleno del marco (de arriba a abajo)

  glPushMatrix();
  glTranslatef(0, 0.635032, -0.49598);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.28, 0.08);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();     



  glPushMatrix();
  glTranslatef(0, 0.507032, -0.41638);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.28, 0.08);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();  



  glPushMatrix();
  glTranslatef(0, -0.000268, 0.00522);
  glRotatef(-35.6, 1, 0, 0);
  glScalef(0.126, 0.71, 0.29);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();            



  glPushMatrix();
  glTranslatef(0, -0.499868, 0.43822);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.3, 0.08);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();       



  glPushMatrix();
  glTranslatef(0, -0.658968, 0.55672);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.3, 0.08);
  base[base.size()-1].draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();       
}

//************************************************************************
void _frenos_traseros::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
  //derecho
  base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(-0.7922, 2.3859, -3.6341);
  glRotatef(23.5, 0, 0, 1);
  glScalef(0.26, 0.02, 0.64);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();         


  //izquierdo
  base.push_back(_cubo(CUBO_TAM, material.mat));

  glPushMatrix();
  glTranslatef(0.7922, 2.3859, -3.6341);
  glRotatef(-23.5, 0, 0, 1);
  glScalef(0.26, 0.02, 0.64);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  glPopMatrix();           
}


//************************************************************************
void _freno_trasero_individual::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
  float rf1=r1, gf1=g1, bf1=b1, rf2=r2, gf2=g2, bf2=b2;

  if(tipo==ESPECIAL){
    rf1=0;
    gf1=1;
    bf1=0;

    rf2=0;
    gf2=0.4;
    bf2=0;
  }  

  if(tipo==NORMAL)
    base.material.setValores(material.mat);
  else
    base.material.setValores(Materiales::ALUMINIO);

  //izquierdo
  glPushMatrix();
  glTranslatef(0, 0, -0.64);
  glScalef(0.26, 0.02, 0.64);
  base.draw(modo, rf1, gf1, bf1, rf2, gf2, bf2, grosor, s);
  glPopMatrix();           
}


//************************************************************************


void _tren_trasero::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
  //Brazo
  /*
  if(tipo==NORMAL)
    piezas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
  else
    piezas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, Materiales::PLATA));
*/

if(tipo==NORMAL){
  piezas[0].material=material.mat;
  piezas[1].material=material.mat;
}
else{
  piezas[0].material=Materiales::PLATA;
  piezas[1].material=Materiales::GOMA;  
}


  glPushMatrix();
  glTranslatef(0, -0.6, 0);
  glScalef(0.05, 0.57, 0.05);

  if(tipo==NORMAL)
    piezas[0].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  else
    piezas[0].draw(modo, 0.7, 0.7, 0.7, 0.4, 0.4, 0.4, grosor, s);  
  glPopMatrix();

  //Rueda

/*
  if(tipo==ESPECIAL)
    piezas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, Materiales::GOMA));
*/


  glPushMatrix();
  glTranslatef(-0.1262, -1.1462, 0);
  glRotatef(90, 0, 0, 1);
  glScalef(0.34, 0.16, 0.34);
  if(tipo==NORMAL)
    piezas[1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  else
    piezas[1].draw(modo, 0.24, 0.24, 0.24, 0.12, 0.12, 0.12, grosor, s);  
  glPopMatrix();
}

//************************************************************************

void _tren_delantero::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){    //QUIZAS HAGA FALTA PONER UN BUCLE PARA CICLAR POR CADA PIEZA
  //Brazo 0.7 0.4
  /*
  if(tipo==NORMAL)
    piezas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, material.mat));
  else
    piezas.push_back(_cilindro(CIL_RAD, CIL_H, NUM, eje, Materiales::PLATA));
*/

if(tipo==ESPECIAL){
  piezas[0].material=Materiales::PLATA;
  piezas[1].material=piezas[2].material=Materiales::GOMA;
  
}
else{
  piezas[0].material=piezas[1].material=piezas[2].material=material.mat;
}


  glPushMatrix();
  glTranslatef(0, -0.55, 0);
  glScalef(0.05, 0.57, 0.05);
  if(tipo==NORMAL){
    piezas[0].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  }
  else
    piezas[0].draw(modo, 0.7, 0.7, 0.7, 0.4, 0.4, 0.4, grosor, s);
  glPopMatrix();

  //Ruedas 0.24 0.12
  //Izquierda


  glPushMatrix();
  glTranslatef(-0.1543, -1.1262, -0.006611);
  glRotatef(90, 0, 0, 1);
  glScalef(0.2, 0.12, 0.2);
  if(tipo==NORMAL)
    piezas[1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  else
    piezas[1].draw(modo, 0.24, 0.24, 0.24, 0.12, 0.12, 0.12, grosor, s);
  glPopMatrix();

  //Derecha

  glPushMatrix();
  glTranslatef(0.1543, -1.1262, -0.006611);
  glRotatef(90, 0, 0, 1);
  glScalef(0.2, 0.12, 0.2);
  if(tipo==NORMAL)
    piezas[2].draw(modo, r1, g1, b1, r2, g2, b2, grosor, s);
  else
    piezas[2].draw(modo, 0.24, 0.24, 0.24, 0.12, 0.12, 0.12, grosor, s);
  glPopMatrix();
}  



//************************************************************************

void _tornado::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Tipo tipo, bool s){
float r_p,g_p,b_p;

r_p=color_pick[0];
g_p=color_pick[1];
b_p=color_pick[2];
  
  glPushMatrix();
    //Cuerpo de la aeronave

    //Animacion de la aeronave
    glTranslatef(0, cuerpo.y, 0);
    glRotatef(giro_aeronave_x, 1, 0, 0);
    glRotatef(giro_aeronave_y, 0, 1, 0);
    glRotatef(giro_aeronave_z, 0, 0, 1);  

    //Pintado del cuerpo de la aeronave
    if(activo[0]==1)
      cuerpo.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
    else
      cuerpo.draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);

    //****************************************Animacion del ala izquierda
    glPushMatrix();
      glTranslatef(ala_izda.x, 0, 0);
      glRotatef(angulo_alas, 0, 1, 0);
      glTranslatef(-ala_izda.x, 0, 0);

      //Pintado del ala izquierda
      glPushMatrix();
        glTranslatef(0, -cuerpo.y, 0); 
        if(activo[1]==1)
          ala_izda.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
        else
          ala_izda.draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);        
      glPopMatrix();

      //Freno aereo delantero Izquierda
      glPushMatrix();
        glTranslatef(3.4478, frenos[0].y-cuerpo.y, -1.7708);  //La movemos al punto intermedio donde movemos toda la aeronave
        glRotatef(-frenos[0].freno_delantero_angulo_y, 0, 1, 0);  //LO mismo
        glRotatef(-frenos[0].freno_delantero_angulo_z, 0, 0, 1);    //Hacemos las rotaciones para que se encuentre encima del ala
        glTranslatef(0, 0, 0.18);   //Movemos la pieza al origen de coordenadas
        glRotatef(giro_frenos_l, 1, 0, 0);    //Realizamos la animacion
        if(activo[2]==1 or frenos[0].algunoActivo())
          frenos[0].draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
        else
          frenos[0].draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);
      glPopMatrix();  


      //FLAP Izquierdo
      glPushMatrix();
        glTranslatef(-flap[0].mover_centro_x_r, -flap[0].mover_centro_y-cuerpo.y, -flap[0].mover_centro_z+flap[0].z);
        glRotatef(flap[0].angulo_y_r, 0, 1, 0);
        glRotatef(flap[0].angulo_z_r, 0, 0, 1);
        glTranslatef(0, 0, flap[0].mover_centro_z-flap_trans);  //Ahora lo movemos al centro de verdad y realizamos la animacion de translacion
        glRotatef(-flap_giro, 1, 0, 0);
        glTranslatef(0, 0, -flap[0].mover_centro_z);
        if(activo[3]==1 or flap[0].algunoActivo())
          flap[0].draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
        else
          flap[0].draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);        
      glPopMatrix();           
    glPopMatrix();


    //****************************************Animacion del ala derecha
    glPushMatrix();
      glTranslatef(ala_dcha.x, 0, 0); 
      glRotatef(-angulo_alas, 0, 1, 0);
      glTranslatef(-ala_dcha.x, 0, 0); 

      //Pintado del ala derecha
      glPushMatrix();
        glTranslatef(0, -cuerpo.y, 0); 
        if(activo[4]==1)
          ala_dcha.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
        else
          ala_dcha.draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);        
      glPopMatrix();


     //Freno aereo delantero Derecha
      glPushMatrix();
        glTranslatef(-3.4478, frenos[1].y-cuerpo.y, -1.7708);  //La movemos al punto intermedio donde movemos toda la aeronave
        glRotatef(frenos[1].freno_delantero_angulo_y, 0, 1, 0);  //LO mismo
        glRotatef(frenos[1].freno_delantero_angulo_z, 0, 0, 1);    //Hacemos las rotaciones para que se encuentre encima del ala
        glTranslatef(0, 0, 0.18);   //Movemos la pieza al origen de coordenadas
        glRotatef(giro_frenos_r, 1, 0, 0);    //Realizamos la animacion

        if(activo[5]==1 or frenos[1].algunoActivo())
          frenos[1].draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
        else
          frenos[1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);        
      glPopMatrix();     

      //FLAP Derecho
      glPushMatrix();   
        glTranslatef(flap[1].mover_centro_x_r, -flap[1].mover_centro_y-cuerpo.y, -flap[1].mover_centro_z+flap[1].z);
        glRotatef(-flap[1].angulo_y_r, 0, 1, 0);
        glRotatef(-flap[1].angulo_z_r, 0, 0, 1);
        glTranslatef(0, 0, flap[1].mover_centro_z-flap_trans);  //Ahora lo movemos al centro de verdad y realizamos la animacion de translacion
        glRotatef(-flap_giro, 1, 0, 0);
        glTranslatef(0, 0, -flap[1].mover_centro_z);
        if(activo[6]==1 or flap[1].algunoActivo())
          flap[1].draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
        else
          flap[1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);
      glPopMatrix();      
    glPopMatrix();


    //Ventana de la aeronave
    glPushMatrix();
      glTranslatef(ventana_movil.x, ventana_movil.y-cuerpo.y, ventana_movil.z);  //Movemos la pieza a su sitio, pero mas abajo para poder realizar la animacion propia de la aeronave
      if(activo[7]==1)
        ventana_fija.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
      else
        ventana_fija.draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);      
      glRotatef(-giro_ventana, 1, 0, 0);
      if(activo[8]==1)
        ventana_movil.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
      else
        ventana_movil.draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);
    glPopMatrix();


    //Timon
    glPushMatrix();
      glTranslatef(0, timon.y-cuerpo.y, timon.z);  
      glRotatef(-37.8, 1, 0, 0);   //Deshacemos el cambio
      glTranslatef(0, 0, 0.340424); //LO movemos para poder hacer el propio giro
      glRotatef(timon_giro, 0, 1, 0);   //Hacemos el propio giro
      glTranslatef(0, 0, -0.340424); //LO movemos para poder hacer el propio giro
      glRotatef(37.8, 1, 0, 0);   //Lo ponemos recto
      if(activo[9]==1)
        timon.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
      else
        timon.draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);      
    glPopMatrix();



    //Ala trasera izquierda
    glPushMatrix(); 
      glTranslatef(ti.x, ti.y-cuerpo.y, ti.z);
      glRotatef(angulo_trasero_l, 1, 0, 0);
      if(activo[10]==1)
        ti.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
      else
        ti.draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);      
    glPopMatrix();



    //Ala trasera derecha
    glPushMatrix();
      glTranslatef(td.x, td.y-cuerpo.y, td.z);
      glRotatef(angulo_trasero_r, 1, 0, 0);
      if(activo[11]==1)
        td.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
      else
        td.draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);
    glPopMatrix();


    //SPD BRK Traseros
    //Izquierda
    glPushMatrix();
      glTranslatef(ft.x, ft.y-cuerpo.y, -ft.centro_z+ft.z);
      glRotatef(ft.angulo_z_l, 0, 0, 1);
      glTranslatef(0, 0, ft.centro_z);  //La movemos al centro
      glRotatef(ft_giro, 1, 0, 0);    //Animacion
      if(activo[12]==1)
        ft.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
      else
        ft.draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);
    glPopMatrix();



    //Derecha
    glPushMatrix();
      glTranslatef(-ft.x, ft.y-cuerpo.y, -ft.centro_z+ft.z);
      glRotatef(-ft.angulo_z_l, 0, 0, 1);
      glTranslatef(0, 0, ft.centro_z);  //La movemos al centro
      glRotatef(ft_giro, 1, 0, 0);    //Animacion
      if(activo[13]==1)
        ft.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
      else
        ft.draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);
    glPopMatrix();



    //Tren de aterrizaje trasero
    //Derecha
    glPushMatrix();
      glTranslatef(tt[0].x_r, tt[0].y_r-cuerpo.y, tt[0].z_r);
      glRotatef(tt_giro_y, 0, 1, 0);  //Realizamos la animacion
      glRotatef(-tt_giro_x, 1, 0, 0);  //Realizamos la animacion
      if(activo[14]==1 or tt[0].algunoActivo())
        tt[0].draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
      else
        tt[0].draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);
    glPopMatrix();



    //Izquierda
    glPushMatrix();
      glTranslatef(-tt[1].x_r, tt[1].y_r-cuerpo.y, tt[1].z_r);
      glRotatef(-tt_giro_y+180, 0, 1, 0);  //Realizamos la animacion
      glRotatef(tt_giro_x, 1, 0, 0);  //Realizamos la animacion
      if(activo[15]==1 or tt[1].algunoActivo())
        tt[1].draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
      else
        tt[1].draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);
    glPopMatrix();


    //Tren de aterrizaje delantero
    glPushMatrix();
      glTranslatef(0, tren_d.y-cuerpo.y, tren_d.z);  
      glRotatef(-giro_tren_d, 1, 0, 0);
      if(activo[16]==1 or tren_d.algunoActivo())
        //tren_d.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo, true);
        tren_d.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, tipo);
      else
        tren_d.draw(modo, r1, g1, b1, r2, g2, b2, grosor, tipo);
    glPopMatrix();

  glPopMatrix();
}

void _tornado::seleccion(){
int c[3];
  //cuerpo.seleccion();
  glPushMatrix();
    //Cuerpo de la aeronave

    //Animacion de la aeronave
    c[0]=color_selec[0][0];
    c[1]=color_selec[1][0];
    c[2]=color_selec[2][0];
    glTranslatef(0, cuerpo.y, 0);
    glRotatef(giro_aeronave_x, 1, 0, 0);
    glRotatef(giro_aeronave_y, 0, 1, 0);
    glRotatef(giro_aeronave_z, 0, 0, 1);  

    //Pintado del cuerpo de la aeronave
    cuerpo.draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);

    //****************************************Animacion del ala izquierda
    glPushMatrix();
      glTranslatef(ala_izda.x, 0, 0);
      glRotatef(angulo_alas, 0, 1, 0);
      glTranslatef(-ala_izda.x, 0, 0);

      //Pintado del ala izquierda
      glPushMatrix();
        glTranslatef(0, -cuerpo.y, 0); 
    c[0]=color_selec[0][1];
    c[1]=color_selec[1][1];
    c[2]=color_selec[2][1];
        ala_izda.draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);
      glPopMatrix();

      //Freno aereo delantero Izquierda
      glPushMatrix();
        glTranslatef(3.4478, frenos[0].y-cuerpo.y, -1.7708);  //La movemos al punto intermedio donde movemos toda la aeronave
        glRotatef(-frenos[0].freno_delantero_angulo_y, 0, 1, 0);  //LO mismo
        glRotatef(-frenos[0].freno_delantero_angulo_z, 0, 0, 1);    //Hacemos las rotaciones para que se encuentre encima del ala
        glTranslatef(0, 0, 0.18);   //Movemos la pieza al origen de coordenadas
        glRotatef(giro_frenos_l, 1, 0, 0);    //Realizamos la animacion
    /*c[0]=color_selec[0][2];
    c[1]=color_selec[1][2];
    c[2]=color_selec[2][2];
        frenos[0].draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);*/

        frenos[0].seleccion();
      glPopMatrix();  


      //FLAP Izquierdo
      glPushMatrix();
        glTranslatef(-flap[0].mover_centro_x_r, -flap[0].mover_centro_y-cuerpo.y, -flap[0].mover_centro_z+flap[0].z);
        glRotatef(flap[0].angulo_y_r, 0, 1, 0);
        glRotatef(flap[0].angulo_z_r, 0, 0, 1);
        glTranslatef(0, 0, flap[0].mover_centro_z-flap_trans);  //Ahora lo movemos al centro de verdad y realizamos la animacion de translacion
        glRotatef(-flap_giro, 1, 0, 0);
        glTranslatef(0, 0, -flap[0].mover_centro_z);
   /* c[0]=color_selec[0][3];
    c[1]=color_selec[1][3];
    c[2]=color_selec[2][3];
        flap.draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);*/

        flap[0].seleccion();

      glPopMatrix();           
    glPopMatrix();


    //****************************************Animacion del ala derecha
    glPushMatrix();
      glTranslatef(ala_dcha.x, 0, 0); 
      glRotatef(-angulo_alas, 0, 1, 0);
      glTranslatef(-ala_dcha.x, 0, 0); 

      //Pintado del ala derecha
      glPushMatrix();
        glTranslatef(0, -cuerpo.y, 0); 
    c[0]=color_selec[0][4];
    c[1]=color_selec[1][4];
    c[2]=color_selec[2][4];
        ala_dcha.draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);
      glPopMatrix();


     //Freno aereo delantero Derecha
      glPushMatrix();
        glTranslatef(-3.4478, frenos[1].y-cuerpo.y, -1.7708);  //La movemos al punto intermedio donde movemos toda la aeronave
        glRotatef(frenos[1].freno_delantero_angulo_y, 0, 1, 0);  //LO mismo
        glRotatef(frenos[1].freno_delantero_angulo_z, 0, 0, 1);    //Hacemos las rotaciones para que se encuentre encima del ala
        glTranslatef(0, 0, 0.18);   //Movemos la pieza al origen de coordenadas
        glRotatef(giro_frenos_r, 1, 0, 0);    //Realizamos la animacion
    /*c[0]=color_selec[0][5];
    c[1]=color_selec[1][5];
    c[2]=color_selec[2][5];
        frenos[1].draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);*/

        frenos[1].seleccion();
      glPopMatrix();     

      //FLAP Derecho
      glPushMatrix();   
        glTranslatef(flap[1].mover_centro_x_r, -flap[1].mover_centro_y-cuerpo.y, -flap[1].mover_centro_z+flap[1].z);
        glRotatef(-flap[1].angulo_y_r, 0, 1, 0);
        glRotatef(-flap[1].angulo_z_r, 0, 0, 1);
        glTranslatef(0, 0, flap[1].mover_centro_z-flap_trans);  //Ahora lo movemos al centro de verdad y realizamos la animacion de translacion
        glRotatef(-flap_giro, 1, 0, 0);
        glTranslatef(0, 0, -flap[1].mover_centro_z);
    /*c[0]=color_selec[0][6];
    c[1]=color_selec[1][6];
    c[2]=color_selec[2][6];*/
        //flap.draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);
        flap[1].seleccion();
      glPopMatrix();      
    glPopMatrix();


    //Ventana de la aeronave
    glPushMatrix();
    c[0]=color_selec[0][7];
    c[0]=color_selec[1][7];
    c[0]=color_selec[2][7];
      glTranslatef(ventana_movil.x, ventana_movil.y-cuerpo.y, ventana_movil.z);  //Movemos la pieza a su sitio, pero mas abajo para poder realizar la animacion propia de la aeronave
      ventana_fija.draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);
      glRotatef(-giro_ventana, 1, 0, 0);
    c[0]=color_selec[0][8];
    c[1]=color_selec[1][8];
    c[2]=color_selec[2][8];
      ventana_movil.draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);
    glPopMatrix();


    //Timon
    glPushMatrix();
      glTranslatef(0, timon.y-cuerpo.y, timon.z);  
      glRotatef(-37.8, 1, 0, 0);   //Deshacemos el cambio
      glTranslatef(0, 0, 0.340424); //LO movemos para poder hacer el propio giro
      glRotatef(timon_giro, 0, 1, 0);   //Hacemos el propio giro
      glTranslatef(0, 0, -0.340424); //LO movemos para poder hacer el propio giro
      glRotatef(37.8, 1, 0, 0);   //Lo ponemos recto
    c[0]=color_selec[0][9];
    c[1]=color_selec[1][9];
    c[2]=color_selec[2][9];
      timon.draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);
    glPopMatrix();



    //Ala trasera izquierda
    glPushMatrix(); 
      glTranslatef(ti.x, ti.y-cuerpo.y, ti.z);
      glRotatef(angulo_trasero_l, 1, 0, 0);
    c[0]=color_selec[0][10];
    c[1]=color_selec[1][10];
    c[2]=color_selec[2][10];
      ti.draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);
    glPopMatrix();



    //Ala trasera derecha
    glPushMatrix();
      glTranslatef(td.x, td.y-cuerpo.y, td.z);
      glRotatef(angulo_trasero_r, 1, 0, 0);
    c[0]=color_selec[0][11];
    c[1]=color_selec[1][11];
    c[2]=color_selec[2][11];
      td.draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);
    glPopMatrix();


    //SPD BRK Traseros
    //Izquierda
    glPushMatrix();
      glTranslatef(ft.x, ft.y-cuerpo.y, -ft.centro_z+ft.z);
      glRotatef(ft.angulo_z_l, 0, 0, 1);
      glTranslatef(0, 0, ft.centro_z);  //La movemos al centro
      glRotatef(ft_giro, 1, 0, 0);    //Animacion
    c[0]=color_selec[0][12];
    c[1]=color_selec[1][12];
    c[2]=color_selec[2][12];
      //ft.draw(SELECT, c, c, c, c, c, c, 1, NORMAL);
      ft.draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);
    glPopMatrix();



    //Derecha
    glPushMatrix();
      glTranslatef(-ft.x, ft.y-cuerpo.y, -ft.centro_z+ft.z);
      glRotatef(-ft.angulo_z_l, 0, 0, 1);
      glTranslatef(0, 0, ft.centro_z);  //La movemos al centro
      glRotatef(ft_giro, 1, 0, 0);    //Animacion

    c[0]=color_selec[0][13];
    c[1]=color_selec[1][13];
    c[2]=color_selec[2][13];
      ft.draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);
    glPopMatrix();



    //Tren de aterrizaje trasero
    //Derecha
    glPushMatrix();
      glTranslatef(tt[0].x_r, tt[0].y_r-cuerpo.y, tt[0].z_r);
      glRotatef(tt_giro_y, 0, 1, 0);  //Realizamos la animacion
      glRotatef(-tt_giro_x, 1, 0, 0);  //Realizamos la animacion

      //c=color_selec[0][14];
      //tt.draw(SELECT, c, c, c, c, c, c, 1, NORMAL);
      tt[0].seleccion();
    glPopMatrix();



    //Izquierda
    glPushMatrix();
      glTranslatef(-tt[1].x_r, tt[1].y_r-cuerpo.y, tt[1].z_r);
      glRotatef(-tt_giro_y+180, 0, 1, 0);  //Realizamos la animacion
      glRotatef(tt_giro_x, 1, 0, 0);  //Realizamos la animacion

      //c=color_selec[0][15];
      //tt[1].draw(SELECT, c[0], c[1], c[2], c[0], c[1], c[2], 1, NORMAL);
      tt[1].seleccion();
    glPopMatrix();


    //Tren de aterrizaje delantero
    glPushMatrix();
      glTranslatef(0, tren_d.y-cuerpo.y, tren_d.z);  
      glRotatef(-giro_tren_d, 1, 0, 0);

      //c=color_selec[0][16];
      //tren_d.draw(SELECT, c, c, c, c, c, c, 1, NORMAL);
      tren_d.seleccion();
    glPopMatrix();

  glPopMatrix();
}