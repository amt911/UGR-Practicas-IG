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
  /*
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
*/

//**** usando vertex_array ****
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
  /*
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
*/

//**** usando vertex_array ****
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
              vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                            perfil[i].y*sin(2.0*M_PI*j/(1.0*num));

              vertice_aux.y=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
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
  cout <<"numVer0: " <<numVer0 <<endl;

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
        caras[c]._1 = ((j + 1) * num_aux + 1 + i) % num_ver;
        caras[c]._2 = ((j + 1) * num_aux + i) % num_ver;

        c++;

        caras[c]._0 = (i + j * num_aux) % num_ver;
        caras[c]._1 = (1 + i + j * num_aux) % num_ver;
        caras[c]._2 = ((j + 1) * num_aux + 1 + i) % num_ver;

        c++;
      }
    }
  }

  //tapa inferior    
  for(int i=0; i<num; i++){
    caras[c]._0=((i+1)*num_aux) % num_ver;
    caras[c]._1=i*num_aux;
    caras[c]._2=vertices.size()-2;
    c++;
  }
 
 // tapa superior
  //El -1 lo que hace es que nos vamos al vertice mas alto del perfil anterior
  //(Con la formula sin -1 nos permite irnos a los vertices inferiores, como pasa mas arriba)
  for(int i=0; i<num; i++){
    caras[c]._0=(i+1)*num_aux-1;
    caras[c]._1=((i+2)*num_aux-1) % num_ver;
    caras[c]._2=vertices.size()-1;
    c++;
  }
  
}

//************************************************************************
// esfera
//************************************************************************
_esfera::_esfera(int radio, int num_puntos, int num_rot, Eje axis){
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
  cout<<"Esfera: ";
  parametros(perfil, num_rot, axis);

  cout <<"\nNumero de caras: " <<caras.size() <<endl <<"Numero de vertices: " <<vertices.size() <<endl <<endl;
}

//************************************************************************
// cono
//************************************************************************
_cono::_cono(double radio, double h, int num, Eje axis){
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
  cout<<"Cono: ";
  parametros(perfil, num, axis);

  cout <<"\nNumero de caras: " <<caras.size() <<endl <<"Numero de vertices: " <<vertices.size() <<endl <<endl;
}

//************************************************************************
// cilindro
//************************************************************************

_cilindro::_cilindro(double radio, double h, int num, Eje axis){
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

  //vertices=perfil;
  cout<<"Cilindro: ";
  parametros(perfil, num, axis);

  cout <<"\nNumero de caras: " <<caras.size() <<endl <<"Numero de vertices: " <<vertices.size() <<endl <<endl;
}


//************************************************************************
// clase ply_rot
//************************************************************************

_ply_rot::_ply_rot(char *file, int rot, Eje axis){
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
}

//************************************************************************
// caza
//************************************************************************

_cuerpo::_cuerpo(){

}
/* Version en su sitio
void _cuerpo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
 
 //Air intakes
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-0.9218, 2.0717, 1.4685);
  glRotatef(3.59, 1, 0, 0);
  glScalef(0.432, 0.406, 1);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0.9218, 2.0717, 1.4685);
  glRotatef(3.59, 1, 0, 0);
  glScalef(0.432, 0.406, 1);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


//Frame
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 1.7076, 1.5759);
  glScalef(-0.59, 0.302, 3.62);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 2.0306, 3.468);
  glRotatef(3.59, 1, 0, 0);
  glScalef(0.59, 0.116, 1.031);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 2.1069, 0.8318);
  glRotatef(4.92, 1, 0, 0);
  glScalef(0.925, 0.406, 0.466);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 2.1277, -0.4898);
  glScalef(0.925, 0.406, 1);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


//Laterales del instake que se curvan hacia dentro
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-0.9414, 2.1277, -0.4284);
  glRotatef(-8.05, 0, 1, 0);
  glScalef(0.270, 0.406, 0.976);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  

  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0.9414, 2.1277, -0.4284);
  glRotatef(8.05, 0, 1, 0);
  glScalef(0.270, 0.406, 0.976);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  

//Alisadores de curvas
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0.5176, 1.6152, -0.0620);
  glRotatef(-13.9, 0, 1, 0);
  glScalef(0.270, 0.137, 1.061);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  

  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-0.5176, 1.6152, -0.0620);
  glRotatef(13.9, 0, 1, 0);
  glScalef(0.270, 0.137, 1.061);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


//Sujeta alas, los que permite que se puedan plegar
  //1 izquierda y derecha
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(1.2496, 2.2815, -0.7854);
  glRotatef(-38.4, 0, 1, 0);
  glScalef(0.451, 0.209, 0.29);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  

  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-1.2496, 2.2815, -0.7854);
  glRotatef(38.4, 0, 1, 0);
  glScalef(0.451, 0.209, 0.29);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  //2 izquierda y derecha
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(1.4784, 2.2815, -0.2166);
  glRotatef(9.56, 0, 1, 0);
  glScalef(0.381, 0.209, 0.46);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-1.4784, 2.2815, -0.2166);
  glRotatef(-9.56, 0, 1, 0);
  glScalef(0.381, 0.209, 0.46);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


  //3 izquierda y derecha
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(1.3179, 2.2815, 0.4604);
  glRotatef(-30.9, 0, 1, 0);
  glScalef(0.381, 0.209, 0.56);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-1.3179, 2.2815, 0.4604);
  glRotatef(30.9, 0, 1, 0);
  glScalef(0.381, 0.209, 0.56);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();      


//Alisadores de curva cola
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 1.9206, -2.0821);
  glScalef(1.061, 0.24, 0.651);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 2.0298, -3.3869);
  glScalef(1.061, 0.123, 0.651);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    

  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 2.0298, -4.6922);
  glScalef(1.061, 0.087, 0.651);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();      


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 1.8741, -3.3869);
  glRotatef(6.37, 1, 0, 0);
  glScalef(1.061, 0.123, 0.651);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


//Estabilizador de cola
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 2.8153, -2.5387);
  glRotatef(-71.4, 1, 0, 0);
  glScalef(0.126, 1.08, 0.435);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    

  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 3.8394, -4.4713);
  glRotatef(-55.3, 1, 0, 0);
  glScalef(0.126, 1.96, 0.435);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 3.6107, -4.8354);
  glRotatef(-37.5, 1, 0, 0);
  glScalef(0.126, 1.33, 0.435);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    



  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 2.5365, -5.0584);
  glScalef(0.126, 0.247, 0.509);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();      


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 4.8361, -6.2732);
  glScalef(0.126, 0.477, 0.435);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 4.8291, -6.787);
  glRotatef(-33.3, 1, 0, 0);
  glScalef(0.126, 0.437, 0.195);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 5.1565, -6.9019);
  glScalef(0.126, 0.157, 0.195);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();           

//Ahora la parte de los cilindros

//Parte de abajo del caza
  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 1.4345, 1.5759);
  glRotatef(270, 1, 0, 0);
  glScalef(0.595, 3.620, 0.279);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0.2268, 1.4545, -0.2723);
  glRotatef(-13.9, 0, 1, 0);
  glRotatef(270, 1, 0, 0);
  glScalef(0.608, 0.899, 0.279);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(-0.2268, 1.4545, -0.2723);
  glRotatef(13.9, 0, 1, 0);
  glRotatef(270, 1, 0, 0);
  glScalef(0.608, 0.899, 0.279);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();






  //Parte de arriba delantera
  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 2.1643, 2.8629);
  glRotatef(93.2, 1, 0, 0);
  glScalef(0.595, 2.297, 0.279);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();       


  //Cilindro de arriba que recorre media aeronave
  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 2.6448, -1.3726);
  glRotatef(88.2, 1, 0, 0);
  glScalef(0.226, 2.951, 0.235);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


  //Parte de la cola
  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 1.5948, -1.58);
  glRotatef(271, 1, 0, 0);
  glScalef(1.059, 0.538, 0.422);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 2.1295, -2.7727);
  glRotatef(270, 1, 0, 0);
  glScalef(1.059, 1.257, 0.422);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 1.7274, -3.0631);
  glRotatef(276, 1, 0, 0);
  glScalef(1.059, 0.990, 0.423);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 2.1102, -4.4509);
  glRotatef(269, 1, 0, 0);
  glScalef(1.059, 0.41, 0.422);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 1.9194, -4.6683);
  glRotatef(276, 1, 0, 0);
  glScalef(1.059, 0.632, 0.422);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 2.0774, -5.1279);
  glRotatef(266, 1, 0, 0);
  glScalef(1.059, 0.41, 0.422);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


//Escape del turbojet
  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0.4586, 2.0356, -5.5719);
  glRotatef(270, 1, 0, 0);
  glScalef(0.321, 0.129, 0.321);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(-0.4586, 2.0356, -5.5719);
  glRotatef(270, 1, 0, 0);
  glScalef(0.321, 0.129, 0.321);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();



//Nariz provisional
  glPushMatrix();
  glTranslatef(0, 1.6131, 6.407);
  glRotatef(94.7, 1, 0, 0);
  glScalef(0.475, 0.73, 0.502);
  nariz.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


//Curva de la nariz
  glPushMatrix();
  glTranslatef(0, 1.7112, 5.201);
  glRotatef(4.72, 1, 0, 0);
  glScalef(0.557, 0.557, 1.112);
  nariz_curva.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


//Filos del timon
  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 3.0535, -2.1481);
  glRotatef(-71.4, 1, 0, 0);
  glScalef(0.12, 1.2, 0.232);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 4.3036, -4.5454);
  glRotatef(-55.3, 1, 0, 0);
  glScalef(0.12, 1.64, 0.232);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 5.1996, -6.4318);
  glRotatef(90, 1, 0, 0);
  glScalef(0.12, 0.67, 0.232);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  
}

*/


// Version centrada
void _cuerpo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
 
 //Air intakes
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-0.9218, 0.1132, 1.4685);
  glRotatef(3.59, 1, 0, 0);
  glScalef(0.432, 0.406, 1);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0.9218, 0.1132, 1.4685);
  glRotatef(3.59, 1, 0, 0);
  glScalef(0.432, 0.406, 1);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


//Frame
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, -0.2509, 1.5759);
  glScalef(-0.59, 0.302, 3.62);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 0.0721, 3.468);
  glRotatef(3.59, 1, 0, 0);
  glScalef(0.59, 0.116, 1.031);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 0.1484, 0.8318);
  glRotatef(4.92, 1, 0, 0);
  glScalef(0.925, 0.406, 0.466);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 0.1692, -0.4898);
  glScalef(0.925, 0.406, 1);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


//Laterales del instake que se curvan hacia dentro
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-0.9414, 0.1692, -0.4284);
  glRotatef(-8.05, 0, 1, 0);
  glScalef(0.270, 0.406, 0.976);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  

  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0.9414, 0.1692, -0.4284);
  glRotatef(8.05, 0, 1, 0);
  glScalef(0.270, 0.406, 0.976);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  

//Alisadores de curvas
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0.5176, -0.3433, -0.0620);
  glRotatef(-13.9, 0, 1, 0);
  glScalef(0.270, 0.137, 1.061);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  

  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-0.5176, -0.3433, -0.0620);
  glRotatef(13.9, 0, 1, 0);
  glScalef(0.270, 0.137, 1.061);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


//Sujeta alas, los que permite que se puedan plegar
  //1 izquierda y derecha
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(1.2496, 0.323, -0.7854);
  glRotatef(-38.4, 0, 1, 0);
  glScalef(0.451, 0.209, 0.29);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  

  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-1.2496, 0.323, -0.7854);
  glRotatef(38.4, 0, 1, 0);
  glScalef(0.451, 0.209, 0.29);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  //2 izquierda y derecha
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(1.4784, 0.323, -0.2166);
  glRotatef(9.56, 0, 1, 0);
  glScalef(0.381, 0.209, 0.46);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-1.4784, 0.323, -0.2166);
  glRotatef(-9.56, 0, 1, 0);
  glScalef(0.381, 0.209, 0.46);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


  //3 izquierda y derecha
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(1.3179, 0.323, 0.4604);
  glRotatef(-30.9, 0, 1, 0);
  glScalef(0.381, 0.209, 0.56);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-1.3179, 0.323, 0.4604);
  glRotatef(30.9, 0, 1, 0);
  glScalef(0.381, 0.209, 0.56);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();      


//Alisadores de curva cola
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, -0.0379, -2.0821);
  glScalef(1.061, 0.24, 0.651);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 0.0713, -3.3869);
  glScalef(1.061, 0.123, 0.651);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    

  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 0.0713, -4.6922);
  glScalef(1.061, 0.087, 0.651);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();      


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, -0.0844, -3.3869);
  glRotatef(6.37, 1, 0, 0);
  glScalef(1.061, 0.123, 0.651);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


//Estabilizador de cola
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 0.8568, -2.5387);
  glRotatef(-71.4, 1, 0, 0);
  glScalef(0.126, 1.08, 0.435);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    

  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 1.8809, -4.4713);
  glRotatef(-55.3, 1, 0, 0);
  glScalef(0.126, 1.96, 0.435);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 1.6522, -4.8354);
  glRotatef(-37.5, 1, 0, 0);
  glScalef(0.126, 1.33, 0.435);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    



  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 0.578, -5.0584);
  glScalef(0.126, 0.247, 0.509);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();      


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 2.8776, -6.2732);
  glScalef(0.126, 0.477, 0.435);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 2.8706, -6.787);
  glRotatef(-33.3, 1, 0, 0);
  glScalef(0.126, 0.437, 0.195);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 3.198, -6.9019);
  glScalef(0.126, 0.157, 0.195);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();           

//Ahora la parte de los cilindros

//Parte de abajo del caza
  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, -0.524, 1.5759);
  glRotatef(270, 1, 0, 0);
  glScalef(0.595, 3.620, 0.279);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0.2268, -0.504, -0.2723);
  glRotatef(-13.9, 0, 1, 0);
  glRotatef(270, 1, 0, 0);
  glScalef(0.608, 0.899, 0.279);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(-0.2268, -0.504, -0.2723);
  glRotatef(13.9, 0, 1, 0);
  glRotatef(270, 1, 0, 0);
  glScalef(0.608, 0.899, 0.279);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();






  //Parte de arriba delantera
  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 0.2058, 2.8629);
  glRotatef(93.2, 1, 0, 0);
  glScalef(0.595, 2.297, 0.279);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();       


  //Cilindro de arriba que recorre media aeronave
  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 0.6863, -1.3726);
  glRotatef(88.2, 1, 0, 0);
  glScalef(0.226, 2.951, 0.235);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


  //Parte de la cola
  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, -0.3637, -1.58);
  glRotatef(271, 1, 0, 0);
  glScalef(1.059, 0.538, 0.422);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 0.171, -2.7727);
  glRotatef(270, 1, 0, 0);
  glScalef(1.059, 1.257, 0.422);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, -0.2311, -3.0631);
  glRotatef(276, 1, 0, 0);
  glScalef(1.059, 0.990, 0.423);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 0.1517, -4.4509);
  glRotatef(269, 1, 0, 0);
  glScalef(1.059, 0.41, 0.422);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, -0.0391, -4.6683);
  glRotatef(276, 1, 0, 0);
  glScalef(1.059, 0.632, 0.422);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 0.1189, -5.1279);
  glRotatef(266, 1, 0, 0);
  glScalef(1.059, 0.41, 0.422);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


//Escape del turbojet
  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0.4586, 0.0771, -5.5719);
  glRotatef(270, 1, 0, 0);
  glScalef(0.321, 0.129, 0.321);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(-0.4586, 0.0771, -5.5719);
  glRotatef(270, 1, 0, 0);
  glScalef(0.321, 0.129, 0.321);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();



//Nariz
  glPushMatrix();
  glTranslatef(0, -0.3454, 6.407);
  glRotatef(94.7, 1, 0, 0);
  glScalef(0.475, 0.73, 0.502);
  nariz.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


//Curva de la nariz
  glPushMatrix();
  glTranslatef(0, -0.2473, 5.201);
  glRotatef(4.72, 1, 0, 0);
  glScalef(0.557, 0.557, 1.112);
  nariz_curva.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


//Filos del timon
  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 1.095, -2.1481);
  glRotatef(-71.4, 1, 0, 0);
  glScalef(0.12, 1.2, 0.232);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 2.3451, -4.5454);
  glRotatef(-55.3, 1, 0, 0);
  glScalef(0.12, 1.64, 0.232);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  esquinas.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 3.2411, -6.4318);
  glRotatef(90, 1, 0, 0);
  glScalef(0.12, 0.67, 0.232);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  
}


//************************************************************************
_alas::_alas(){

}


void _alas::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  //Cubos con la forma primitiva de las alas
    //derecha
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-3.354, 2.1596, -1.5932);
  glRotatef(-15.9, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.38);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();     


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-3.3537, 2.1749, -1.1572);
  glRotatef(-23.5, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.3);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();     


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-5.7552, 1.9762, -2.4362);
  glRotatef(-15.9, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(0.1, 0.105, 0.23);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-5.8797, 1.9762, -2.7862);
  glRotatef(-15.9, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(0.16, 0.075, 0.11);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    

  //izquierda
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(3.354, 2.1596, -1.5932);
  glRotatef(15.9, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.38);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();     


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(3.3537, 2.1749, -1.1572);
  glRotatef(23.5, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(2.45, 0.12, 0.3);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(5.7552, 1.9762, -2.4362);
  glRotatef(15.9, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(0.1, 0.105, 0.23);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();   


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(5.8797, 1.9762, -2.7862);
  glRotatef(15.9, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(0.16, 0.075, 0.11);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  



//Cilindros para el filo de las alas
  //derecha
  filos.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(-3.6565, 2.1568, -1.0302);  
  glRotatef(-24.8, 0, 1, 0);
  glRotatef(94.6, 0, 0, 1);
  glScalef(0.12, 2.096, 0.366);
  filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


  filos.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(-5.8499, 1.9745, -2.315);
  glRotatef(90, 1, 0, 0);  
  glRotatef(-14.5, 0, 0, 1);
  glRotatef(-4.6, 0, 1, 0);
  glScalef(0.165, 0.465, 0.12);
  filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  

  //izquierda       
  filos.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(3.6565, 2.1568, -1.0302);
  glRotatef(24.8, 0, 1, 0);
  glRotatef(-94.6, 0, 0, 1);
  glScalef(0.12, 2.096, 0.366);
  filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


  filos.push_back(_cilindro());
//tal cual
  glPushMatrix();
  glTranslatef(5.8499, 1.9745, -2.315);
  glRotatef(90, 1, 0, 0);  
  glRotatef(14.5, 0, 0, 1);
  glRotatef(4.6, 0, 1, 0);
  glScalef(0.165, 0.465, 0.12);
  filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  

  //Esferas para las esquinas
  //derecha
  esquinas.push_back(_esfera());

  glPushMatrix();
  glTranslatef(-5.6556, 1.9831, -1.8168);
  glRotatef(4.6, 0, 0, 1);
  glScalef(0.237, 0.12, 0.237);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    


  //izquierda
  esquinas.push_back(_esfera());

  glPushMatrix();
  glTranslatef(5.6556, 1.9831, -1.8168);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(0.237, 0.12, 0.237);
  esquinas[esquinas.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();      
}

//************************************************************************

void _ala_td::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){

  //Empiezo por la forma basica (los cubos)
    //derecha
    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(-2.1507-x, 1.949-y, -5.2809-z);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(31.4, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.451, 0.045, 0.68);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();      


    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(-1.5855-x, 1.9697-y, -4.4044-z);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(35.2, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.451, 0.045, 0.4);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix(); 


    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(-1.6026-x, 1.9716-y, -5.2952-z);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.32, 0.045, 0.411);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix(); 


    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(-2.5898-x, 1.9383-y, -5.8145-z);
    glRotatef(1.19, 1, 0, 0);
    glRotatef(1.66, 0, 0, 1);
    glScalef(0.4, 0.045, 0.181);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix(); 


    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(-1.5298-x, 1.9671-y, -3.9342-z);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(35.2, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.231, 0.045, 0.330);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix(); 


    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(-1.3757-x, 1.9678-y, -3.5247-z);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(35.2, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.121, 0.045, 0.16);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix(); 


    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(-1.2232-x, 1.9828-y, -4.3766-z);
    glRotatef(2.75, 0, 0, 1);
    glScalef(0.16, 0.045, 1.222);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix(); 


    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(-1.9388-x, 1.9641-y, -5.8499-z);
    glRotatef(1.19, 1, 0, 0);
    glRotatef(-18, 0, 1, 0);
    glRotatef(1.66, 0, 0, 1);
    glScalef(1.06, 0.045, 0.181);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix(); 


//Ahora los cilindros que hacen que los filos sean redondeados
  //derecha
    filos.push_back(_cilindro());

    glPushMatrix();
    glTranslatef(-2.0814-x, 1.95-y, -4.3356-z);
    glRotatef(35.2, 0, 1, 0);
    glRotatef(2.75, 0, 0, 1);
    glRotatef(88.9, 1, 0, 0);       //XQ ES ASI???
    glScalef(0.15, 1.56, 0.04);
    filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();   


    filos.push_back(_cilindro());

    glPushMatrix();
    glTranslatef(-2.9986-x, 1.9346-y, -5.9952-z);
    //glRotatef(35.2, 0, 0, 1);
    glRotatef(1.19, 0, 0, 1);
    glRotatef(91.7, 1, 0, 0);       //XQ ES ASI???
    glScalef(0.15, 0.34, 0.04);
    filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();   


//Esferas de las esquinas
  //derecha
    glPushMatrix();
    glTranslatef(-3.0106-x, 1.9258-y, -5.6202-z);
    glRotatef(3.9, 1, 0, 0);       //XQ ES ASI???
    glRotatef(5.9, 0, 0, 1);
    glScalef(0.135, 0.035, 0.125);
    esquina.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();                
}


void _ala_ti::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){

  //Empiezo por la forma basica (los cubos)
    //izquierda
    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(2.1507-x, 1.949-y, -5.2809-z);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(-31.4, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.451, 0.045, 0.68);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();     

    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(1.5855-x, 1.9697-y, -4.4044-z);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(-35.2, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.451, 0.045, 0.4);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(1.6026-x, 1.9716-y, -5.2952-z);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.32, 0.045, 0.411);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();          


    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(2.5898-x, 1.9383-y, -5.8145-z);
    glRotatef(1.19, 1, 0, 0);
    glRotatef(-1.66, 0, 0, 1);
    glScalef(0.4, 0.045, 0.181);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();     


    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(1.5298-x, 1.9671-y, -3.9342-z);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(-35.2, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.231, 0.045, 0.330);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();     


    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(1.3757-x, 1.9678-y, -3.5247-z);
    glRotatef(-1.1, 1, 0, 0);
    glRotatef(-35.2, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.121, 0.045, 0.16);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();     


    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(1.2232-x, 1.9828-y, -4.3766-z);
    glRotatef(-2.75, 0, 0, 1);
    glScalef(0.16, 0.045, 1.222);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();     


    base.push_back(_cubo());

    glPushMatrix();
    glTranslatef(1.9388-x, 1.9641-y, -5.8499-z);
    glRotatef(1.19, 1, 0, 0);
    glRotatef(18, 0, 1, 0);
    glRotatef(-1.66, 0, 0, 1);
    glScalef(1.06, 0.045, 0.181);
    base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix(); 


//Ahora los cilindros que hacen que los filos sean redondeados
  //izquierda

    filos.push_back(_cilindro());

    glPushMatrix();
    glTranslatef(2.0814-x, 1.95-y, -4.3356-z);
    glRotatef(-35.2, 0, 1, 0);
    glRotatef(-2.75, 0, 0, 1);
    glRotatef(88.9, 1, 0, 0);       //XQ ES ASI???
    glScalef(0.15, 1.56, 0.04);
    filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();   

    filos.push_back(_cilindro());

    glPushMatrix();
    glTranslatef(2.9986-x, 1.9346-y, -5.9952-z);
    //glRotatef(35.2, 0, 0, 1);
    glRotatef(-1.19, 0, 0, 1);
    glRotatef(91.7, 1, 0, 0);       //XQ ES ASI???
    glScalef(0.15, 0.34, 0.04);
    filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();   


//Esferas de las esquinas
  //izquierda
    glPushMatrix();
    glTranslatef(3.0106-x, 1.9258-y, -5.6202-z);
    glRotatef(3.9, 1, 0, 0);
    glRotatef(-5.9, 0, 0, 1);
    glScalef(0.135, 0.035, 0.125);
    esquina.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();                 
}



//************************************************************************
/*
//Version en su sitio
void _ventana_movil::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  //Primero los cubos
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 2.3459, 2.807);
  glRotatef(1.1, 1, 0, 0);
  glScalef(0.324, 0.064, 1.21);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 

  //derecha
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-0.2509, 2.5451, 2.707);
  glRotatef(-11.3, 0, 0, 1);
  glScalef(0.05, 0.16, 1.11);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 


  //izquierda
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0.2509, 2.5451, 2.707);
  glRotatef(11.3, 0, 0, 1);
  glScalef(0.05, 0.16, 1.11);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 



  //Ahora los cilindros
  filos.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 2.7227, 2.58);
  glRotatef(90, 1, 0, 0);
  glScalef(0.265, 0.985, 0.265);
  filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();     



  filos.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, 2.7011, 3.6135);
  glRotatef(104, 1, 0, 0);
  glScalef(0.265, 0.115, 0.265);
  filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 
}
*/

//Version centrada
void _ventana_movil::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  //Primero los cubos
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, -0.64416, 1.204);
  glRotatef(1.1, 1, 0, 0);
  glScalef(0.324, 0.064, 1.21);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 

  //derecha
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-0.2509, -0.44495, 1.1041);
  glRotatef(-11.3, 0, 0, 1);
  glScalef(0.05, 0.16, 1.11);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 


  //izquierda
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0.2509, -0.44495, 1.1041);
  glRotatef(11.3, 0, 0, 1);
  glScalef(0.05, 0.16, 1.11);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 



  //Ahora los cilindros
  filos.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, -0.26732, 0.97712);
  glRotatef(90, 1, 0, 0);
  glScalef(0.265, 0.985, 0.265);
  filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();     



  filos.push_back(_cilindro());

  glPushMatrix();
  glTranslatef(0, -0.28891, 2.0103);
  glRotatef(104, 1, 0, 0);
  glScalef(0.265, 0.115, 0.265);
  filos[filos.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 
}


//************************************************************************
/*
void _ventana_fija::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-0.2208, 2.5154, 4.05);
  glRotatef(-14.5, 0, 0, 1);
  glRotatef(12.1, 0, 1, 0);
  glRotatef(7.47, 1, 0, 0);
  glScalef(0.05, 0.16, 0.26);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();   



  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0.2208, 2.5154, 4.05);
  glRotatef(14.5, 0, 0, 1);
  glRotatef(-12.1, 0, 1, 0);
  glRotatef(7.47, 1, 0, 0);
  glScalef(0.05, 0.16, 0.26);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();   


  //cilindro
  glPushMatrix();
  glTranslatef(0, 2.587, 3.863);
  glRotatef(117, 1, 0, 0);
  glScalef(0.265, 0.225, 0.265);
  filos.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 


  //Cono
  glPushMatrix();
  glTranslatef(0, 2.3811, 4.52);
  glRotatef(106, 1, 0, 0);
  glScalef(0.249, 0.429, 0.249);
  pico.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

}

*/
//Version centrado
void _ventana_fija::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-0.2208, -0.47467, 2.4468);
  glRotatef(-14.5, 0, 0, 1);
  glRotatef(12.1, 0, 1, 0);
  glRotatef(7.47, 1, 0, 0);
  glScalef(0.05, 0.16, 0.26);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();   



  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0.2208, -0.47467, 2.4468);
  glRotatef(14.5, 0, 0, 1);
  glRotatef(-12.1, 0, 1, 0);
  glRotatef(7.47, 1, 0, 0);
  glScalef(0.05, 0.16, 0.26);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();   


  //cilindro
  glPushMatrix();
  glTranslatef(0, -0.403, 2.26);
  glRotatef(117, 1, 0, 0);
  glScalef(0.265, 0.225, 0.265);
  filos.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 


  //Cono
  glPushMatrix();
  glTranslatef(0, -0.60895, 2.9173);
  glRotatef(106, 1, 0, 0);
  glScalef(0.249, 0.429, 0.249);
  pico.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

}


//************************************************************************

//************************************************************************

void _flaps::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  //derecho
  flaps.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-3.5797, 2.1596, -2.0297);
  glRotatef(-14.6, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(2.23, 0.08, 0.26);
  flaps[flaps.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  //izquierdo
  flaps.push_back(_cubo());

  glPushMatrix();
  glTranslatef(3.5797, 2.1596, -2.0297);
  glRotatef(14.6, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(2.23, 0.08, 0.26);
  flaps[flaps.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}


//************************************************************************

void _frenos_delanteros::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  //derecho
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(-3.4478, 2.2518, -1.7708);
  glRotatef(-15.9, 0, 1, 0);
  glRotatef(4.6, 0, 0, 1);
  glScalef(1.29, 0.02, 0.18);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  

  //izquierdo
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(3.4478, 2.2518, -1.7708);
  glRotatef(15.9, 0, 1, 0);
  glRotatef(-4.6, 0, 0, 1);
  glScalef(1.29, 0.02, 0.18);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();    
}

//************************************************************************
/*
//Version en su sitio
void _timon::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  //Marco exterior
  base.push_back(_cubo());

  glPushMatrix();
  //glTranslatef(0, 5.2054, 2.8443);
  glTranslatef(0, 2.8443, -5.2054);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.48, 0.05);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 3.5657, -6.1446);
  glRotatef(-33.5, 1, 0, 0);
  glScalef(0.126, 0.9, 0.05);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();   


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 4.3052, -6.307);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.34, 0.05);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 3.5728, -5.4248);
  glRotatef(-37.8, 1, 0, 0);
  glScalef(0.126, 0.95, 0.05);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();     

  //Relleno del marco (de arriba a abajo)
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 4.2144, -6.2811);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.28, 0.08);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();     


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 4.0864, -6.2015);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.28, 0.08);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 3.5791, -5.7799);
  glRotatef(-35.6, 1, 0, 0);
  glScalef(0.126, 0.71, 0.29);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();            


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 3.0795, -5.3469);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.3, 0.08);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();       


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 2.9204, -5.2284);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.3, 0.08);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();       
}
*/

//Version centrado
void _timon::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  //Marco exterior
  base.push_back(_cubo());

  glPushMatrix();
  //glTranslatef(0, 5.2054, 2.8443);
  glTranslatef(0, -0.735068, 0.57972);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.48, 0.05);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, -0.013668, -0.35948);
  glRotatef(-33.5, 1, 0, 0);
  glScalef(0.126, 0.9, 0.05);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();   


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 0.725832, -0.52188);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.34, 0.05);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix(); 


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, -0.006568, 0.36032);
  glRotatef(-37.8, 1, 0, 0);
  glScalef(0.126, 0.95, 0.05);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();     

  //Relleno del marco (de arriba a abajo)
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 0.635032, -0.49598);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.28, 0.08);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();     


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, 0.507032, -0.41638);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.28, 0.08);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();  


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, -0.000268, 0.00522);
  glRotatef(-35.6, 1, 0, 0);
  glScalef(0.126, 0.71, 0.29);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();            


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, -0.499868, 0.43822);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.3, 0.08);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();       


  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0, -0.658968, 0.55672);
  glRotatef(90, 1, 0, 0);
  glScalef(0.126, 0.3, 0.08);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();       
}

//************************************************************************
void _frenos_traseros::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  //derecho
  base.push_back(_cubo());

  glPushMatrix();
  //glTranslatef(-0.7922, 3.6341, 2.3859);
  glTranslatef(-0.7922, 2.3859, -3.6341);
  glRotatef(23.5, 0, 0, 1);
  //glScalef(0.26, 0.64, 0.02);
  glScalef(0.26, 0.02, 0.64);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();         


  //izquierdo
  base.push_back(_cubo());

  glPushMatrix();
  glTranslatef(0.7922, 2.3859, -3.6341);
  glRotatef(-23.5, 0, 0, 1);
  glScalef(0.26, 0.02, 0.64);
  base[base.size()-1].draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();           
}



void _tornado::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){

  
  glPushMatrix();

  glPushMatrix();
  glTranslatef(0, cuerpo.y, 0);
  glRotatef(giro_aeronave_x, 1, 0, 0);
  glRotatef(giro_aeronave_y, 0, 1, 0);
  glRotatef(giro_aeronave_z, 0, 0, 1);  
  cuerpo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, ventana_movil.y_i_f, 0);  
  glRotatef(giro_aeronave_x, 1, 0, 0);
  glRotatef(giro_aeronave_y, 0, 1, 0);
  glRotatef(giro_aeronave_z, 0, 0, 1);  
  glTranslatef(ventana_movil.x, ventana_movil.intermedio_y, ventana_movil.z);  
  
  ventana_fija.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glRotatef(-giro_ventana, 1, 0, 0);
  ventana_movil.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, timon.y_i_f, 0);  

  glRotatef(giro_aeronave_x, 1, 0, 0);
  glRotatef(giro_aeronave_y, 0, 1, 0);
  glRotatef(giro_aeronave_z, 0, 0, 1);    
  glTranslatef(0, timon.intermedio_y, timon.z);  

  glRotatef(-angulo_timon, 1, 0, 0);   //Deshacemos el cambio
  glTranslatef(0, 0, -timon_trans_giro_z); //LO movemos para poder hacer el propio giro
  glRotatef(timon_giro, 0, 1, 0);   //Hacemos el propio giro
  glTranslatef(0, 0, timon_trans_giro_z); //LO movemos para poder hacer el propio giro
  glRotatef(angulo_timon, 1, 0, 0);   //Lo ponemos recto
  timon.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();

  glTranslatef(0, ti.y_i_f, 0);

  glRotatef(giro_aeronave_x, 1, 0, 0);
  glRotatef(giro_aeronave_y, 0, 1, 0);
  glRotatef(giro_aeronave_z, 0, 0, 1);    

  glTranslatef(ti.x, ti.intermedio_y, ti.z);
  glRotatef(angulo_trasero, 1, 0, 0);
  ti.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();

  glTranslatef(0, td.y_i_f, 0);

  glRotatef(giro_aeronave_x, 1, 0, 0);
  glRotatef(giro_aeronave_y, 0, 1, 0);
  glRotatef(giro_aeronave_z, 0, 0, 1);    

  glTranslatef(td.x, td.intermedio_y, td.z);
  glRotatef(angulo_trasero, 1, 0, 0);
  td.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();


  glPopMatrix();
}