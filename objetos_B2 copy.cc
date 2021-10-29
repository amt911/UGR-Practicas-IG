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
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//glLineWidth(grosor);
//glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
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

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
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
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
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

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

  vertice_aux.x=0;
  vertice_aux.y=perfil[0].y;
  vertice_aux.z=0;
  vertices.push_back(vertice_aux);

  vertice_aux.x=0;
  vertice_aux.y=perfil[perfil.size()-1].y;
  vertice_aux.z=0;
  vertices.push_back(vertice_aux);



// tratamiento de las caras 
caras.resize((num*2*(num_aux-1))+2*(num));

//caras[0]._0=0;  caras[0]._1=num_aux+1;  caras[0]._2=num_aux;
//caras[1]._0=0;  caras[1]._1=1;  caras[0]._2=num_aux+1

int c=0, num_ver=vertices.size()-2;
for (int j = 0; j < num; j++)
{
  for (int i = 0; i < (num_aux - 1); i++)
  {
    caras[c]._0 = (i + j * num_aux) % num_ver;
    caras[c]._1 = ((j + 1) * num_aux + 1 + i) % num_ver;
    caras[c]._2 = ((j + 1) * num_aux + i) % num_ver;

    c++;

    caras[c]._0 = (i + j * num_aux) % num_ver;
    caras[c]._1 = (1 + i + j * num_aux) % num_ver;
    caras[c]._2 = ((j + 1) * num_aux + 1 + i) % num_ver;

    c++;
  }
}
/*
 // tapa inferior
if (fabs(perfil[0].x)>0.0)
  {
    
    for(int i=0; i<num; i++){
      caras[c]._0=((i+1)*perfil.size()) % num_ver;
      caras[c]._1=i*perfil.size();
      caras[c]._2=vertices.size()-2;
      c++;
    }    
  }
 
 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
  {
    for(int i=0; i<num; i++){
      caras[c]._0=(i+1)*perfil.size()-1;
      caras[c]._1=((i+2)*perfil.size()-1) % num_ver;
      caras[c]._2=vertices.size()-1;
      c++;
    }    
*/
    //caras[c]._0=caras[c]._1=caras[c]._2=0;


if (fabs(perfil[0].x)>0.0)
  {
    
    for(int i=0; i<num; i++){
      caras[c]._0=((i+1)*num_aux) % num_ver;
      caras[c]._1=i*num_aux;
      caras[c]._2=vertices.size()-2;
      c++;
    }    
  }
 
 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
  {
    for(int i=0; i<num; i++){
      caras[c]._0=(i+1)*num_aux-1;
      caras[c]._1=((i+2)*num_aux-1) % num_ver;
      caras[c]._2=vertices.size()-1;
      c++;
    }      
}
}

//************************************************************************
// esfera
//************************************************************************
/*
void _esfera::parametros(vector<_vertex3f> perfil, int num)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();

//vertices.resize(num_aux*num);
for (j=0;j<(num);j++)
  {for (i=0;i<num_aux;i++)
     {
      if(perfil[i].x!=0.0){
        vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                      perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
        vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                      perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
        vertice_aux.y=perfil[i].y;
        vertices.push_back(vertice_aux);
      }
     }
  }

  //Le añadimos los picos manualmente
  vertice_aux.x=0;
  vertice_aux.y=perfil[0].y;
  vertice_aux.z=0;
  vertices.push_back(vertice_aux);

  vertice_aux.x=0;
  vertice_aux.y=perfil[perfil.size()-1].y;
  vertice_aux.z=0;
  vertices.push_back(vertice_aux);

  //if(perfil[0].x==0.0 and perfil[perfil.size()-1].x==0.0)
    num_aux-=2; //Le restamos 2 para no tener en cuenta las tapas ya que si no seria mas dificil hacer los calculos

// tratamiento de las caras 
caras.resize((num*2*(num_aux-1))+2*(num));


//caras[0]._0=0;  caras[0]._1=num_aux+1;  caras[0]._2=num_aux;
//caras[1]._0=0;  caras[1]._1=1;  caras[0]._2=num_aux+1

int c=0, num_ver=vertices.size()-2; //Se le resta 2 porque los picos son los ultimos
for (int j = 0; j < num; j++)
{
  for (int i = 0; i < (num_aux - 1); i++)
  {
    caras[c]._0 = (i + j * num_aux) % num_ver;
    caras[c]._1 = ((j + 1) * num_aux + 1 + i) % num_ver;
    caras[c]._2 = ((j + 1) * num_aux + i) % num_ver;

    c++;

    caras[c]._0 = (i + j * num_aux) % num_ver;
    caras[c]._1 = (1 + i + j * num_aux) % num_ver;
    caras[c]._2 = ((j + 1) * num_aux + 1 + i) % num_ver;

    c++;
  }
}
/*
  //Tapa inferior, no es necesario hacer comprobaciones
    for(int i=0; i<num; i++){
      caras[c]._0=((i+1)*(perfil.size()-2)) % num_ver;
      caras[c]._1=i*(perfil.size()-2);  //Nota: hay que restarle 2 para suponer un perfil como los correctos
      caras[c]._2=vertices.size()-2;
      c++;
    } 
 
 // tapa superior
    for(int i=0; i<num; i++){
      caras[c]._0=(i+1)*(perfil.size()-2)-1;
      caras[c]._1=((i+2)*(perfil.size()-2)-1) % num_ver;
      caras[c]._2=vertices.size()-1;
      c++;
    }    
    */

  //Tapa inferior, no es necesario hacer comprobaciones
    for(int i=0; i<num; i++){
      caras[c]._0=((i+1)*num_aux) % num_ver;
      caras[c]._1=i*num_aux;  //Nota: hay que restarle 2 para suponer un perfil como los correctos
      caras[c]._2=vertices.size()-2;
      c++;
    } 
 
 // tapa superior
    for(int i=0; i<num; i++){
      caras[c]._0=(i+1)*num_aux-1;
      caras[c]._1=((i+2)*num_aux-1) % num_ver;
      caras[c]._2=vertices.size()-1;
      c++;
    }    
}



_esfera::_esfera(int radio, int num_puntos, int num_rot){
  _vertex3f paux;

  paux.x=0;
  paux.y=-radio;
  paux.z=0;
  double angulo=(M_PI)/(num_puntos-1);

  perfil.push_back(paux);

  for(int i=1; i<num_puntos-1; i++){
    paux.x=perfil[i-1].x*cos(angulo)-perfil[i-1].y*sin(angulo);
    paux.y=perfil[i-1].x*sin(angulo)+perfil[i-1].y*cos(angulo);
    paux.z=0;
    perfil.push_back(paux);
  }

  paux.x=0;
  paux.y=radio;
  paux.z=0;
  perfil.push_back(paux);

  //vertices=perfil;
  cerr<<"PEERFIL: " <<perfil.size()<<endl;
  cerr<<"xddddd: " <<perfil[perfil.size()-1].x<<endl;
  parametros(perfil, num_rot);
}

//************************************************************************
// cono
//************************************************************************
_cono::_cono(double radio, double h, int num){
  _vertex3f paux;
  paux.x=0;
  paux.y=-h/2;
  paux.z=0;

  perfil.push_back(paux);

  paux.x=radio;
  paux.y=-h/2;
  paux.z=0;

  perfil.push_back(paux);

  paux.x=0;
  paux.y=h/2;
  paux.z=0;  

  perfil.push_back(paux);

  //vertices=perfil;

  parametros(perfil, num);
}


void _cono::parametros(vector<_vertex3f> perfil, int num){
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;

// tratamiento de los vértice
for (j=0;j<(num);j++)
{
  vertice_aux.x=perfil[1].x*cos(2.0*M_PI*j/(1.0*num))+
                perfil[1].z*sin(2.0*M_PI*j/(1.0*num));
  vertice_aux.z=-perfil[1].x*sin(2.0*M_PI*j/(1.0*num))+
                perfil[1].z*cos(2.0*M_PI*j/(1.0*num));
  vertice_aux.y=perfil[1].y;
  vertices.push_back(vertice_aux);
}

  //Le añadimos los picos manualmente
  vertice_aux.x=0;
  vertice_aux.y=perfil[0].y;
  vertice_aux.z=0;
  vertices.push_back(vertice_aux);

  vertice_aux.x=0;
  vertice_aux.y=perfil[perfil.size()-1].y;
  vertice_aux.z=0;
  vertices.push_back(vertice_aux);

// tratamiento de las caras 
caras.resize(2*num);

int c=0, num_ver=vertices.size()-2; //Se le resta 2 porque solo tiene dos bases
for (int j = 0; j < num; j++)
{
    caras[c]._0 = j % num_ver;
    caras[c]._1 = (j+ 1) % num_ver;
    caras[c]._2 = vertices.size()-1;

    c++;
}

  //Tapa inferior
    for(int i=0; i<num; i++){
      caras[c]._0=(i+1) % num_ver;
      caras[c]._1=i;  //Nota: hay que restarle 2 para suponer un perfil como los correctos
      caras[c]._2=vertices.size()-2;
      c++;
    }
}

//************************************************************************
// cilindro
//************************************************************************

_cilindro::_cilindro(double radio, double h, int num){
  _vertex3f paux;
  paux.x=radio;
  paux.y=-h/2;
  paux.z=0;

  perfil.push_back(paux);

  paux.x=radio;
  paux.y=h/2;
  paux.z=0;

  perfil.push_back(paux);

  //vertices=perfil;

  parametros(perfil, num);
}