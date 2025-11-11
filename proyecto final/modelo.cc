/*	Prácticas de Informática Gráfica

	Grupos C y D				Curso 2023-24
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: 

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informticos
	(Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================/
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include "vector"



using namespace std;

  Objeto3D Sol(9);
  Objeto3D Mercurio(1);
  Objeto3D Venus(2);
  Objeto3D Tierra(3);
  Objeto3D Marte(4);
  Objeto3D Jupiter(5);
  Objeto3D Saturno(6);
  Objeto3D Urano(7);
  Objeto3D Neptuno(8);

 vector<Objeto3D*> sistema_solar={
    &Sol,&Mercurio,&Venus,
    &Tierra,&Marte,&Jupiter,
    &Saturno,&Urano,&Neptuno
  };

  vector<float> velocidad_orbital = {
    0,     //Sol
    4.787, //Mercurio
    3.502, //Venus
    2.978, //Tierra
    2.407, //Marte
    1.307, //Jupiter
    0.969, //Saturno
    0.681, //Urano
    0.543  //Neptuno
  };

extern int pixelseleccionado;
extern bool stop_giro;
extern bool cambiar_mov;
bool seleccion_cubo=false;


/**	void initModel()

Inicializa el modelo y de las variables globales


**/
void
initModel ()
{
  //ULTIMO PARAMETRO ES LA SOMBRA PARA APLICARLO EN aplicarMaterial()
  //Cambiar distancias y tamaños
  
  Sol.esfera = new Esfera(1.0, 40, 40, 0);         // Sol
  Mercurio.esfera = new Esfera(0.02, 40, 40, 1.2); // Mercurio
  Venus.esfera = new Esfera(0.05, 40, 40, 1.4);    // Venus
  Tierra.esfera = new Esfera(0.06, 40, 40, 1.6);   // Tierra
  Marte.esfera = new Esfera(0.03, 40, 40, 1.8);    // Marte
  Jupiter.esfera = new Esfera(0.3, 40, 40, 2.5);   // Júpiter
  Saturno.esfera = new Esfera(0.25, 40, 40, 3.5, 0.3, 0.4, 200);  // Saturno
  Urano.esfera = new Esfera(0.1, 40, 40, 4.4);     // Urano
  Neptuno.esfera = new Esfera(0.1, 40, 40, 4.7);   // Neptuno


  //El vector no funciona si no esta inicializado correctamente

  vector<vector<float>> r_ambientales = {
    {1.0, 0.9, 0.6, 1.0},   // Sol
    {0.2, 0.2, 0.2, 0.6},   // Mercurio
    {0.3, 0.3, 0.3, 0.8},   // Venus
    {0.3, 0.3, 0.3, 0.9},   // Tierra
    {0.2, 0.1, 0.1, 0.5},   // Marte
    {0.3, 0.3, 0.5, 1.0},   // Júpiter
    {0.2, 0.2, 0.4, 0.7},   // Saturno
    {0.2, 0.3, 0.5, 1.0},   // Urano
    {0.3, 0.3, 0.5, 1.0}    // Neptuno
  };

  vector<vector<float>> r_difusas = {
      {1.0, 0.8, 0.4, 1.0},   // Sol
      {0.6, 0.6, 0.6, 0.6},   // Mercurio
      {0.8, 0.7, 0.6, 0.8},   // Venus
      {0.6, 0.7, 0.5, 0.9},   // Tierra
      {0.8, 0.4, 0.4, 0.5},   // Marte
      {0.5, 0.5, 0.8, 1.0},   // Júpiter
      {0.6, 0.5, 0.8, 0.7},   // Saturno
      {0.5, 0.6, 0.8, 1.0},   // Urano
      {0.5, 0.5, 0.9, 1.0}    // Neptuno
  };

  vector<vector<float>> r_especulares = {
      {0.8, 0.6, 0.3, 1.0},   // Sol
      {0.1, 0.1, 0.1, 0.6},   // Mercurio
      {0.2, 0.2, 0.2, 0.8},   // Venus
      {0.4, 0.4, 0.4, 0.9},   // Tierra
      {0.1, 0.1, 0.1, 0.5},   // Marte
      {0.5, 0.5, 0.5, 1.0},   // Júpiter
      {0.4, 0.4, 0.4, 0.7},   // Saturno
      {0.3, 0.3, 0.3, 1.0},   // Urano
      {0.5, 0.5, 0.6, 1.0}    // Neptuno
  };


  vector<float> sombras = {
      90.0,   // Sol
      10.0,  // Mercurio
      20.0,  // Venus
      50.0,  // Tierra
      10.0,  // Marte
      40.0,  // Júpiter
      35.0,  // Saturno
      30.0,  // Urano
      50.0  // Neptuno
  };

  vector<const char*> texturas = {
      "textura_sol.jpg", //Sol
      "mercurio.jpg",    //Mercurio
      "venus.jpg",       //Venus
      "tierra.jpg",      //Tierra
      "marte.jpg",       //Marte
      "jupiter.jpg",     //Jupiter
      "saturno.jpg",     //Saturno
      "urano.jpg",       //Urano
      "neptuno.jpg",     //Neptuno
  };

  
  
  for (int i = 0; i < sistema_solar.size(); i++) {
    if (sistema_solar[i]->esfera != nullptr) {
        
        sistema_solar[i]->esfera->material = new Material();
        if (sistema_solar[i]->esfera->material != nullptr) {
            sistema_solar[i]->esfera->material->setRAmbiental(r_ambientales[i][0], r_ambientales[i][1], r_ambientales[i][2], r_ambientales[i][3]);
            sistema_solar[i]->esfera->material->setRDifusa(r_difusas[i][0], r_difusas[i][1], r_difusas[i][2], r_difusas[i][3]);
            sistema_solar[i]->esfera->material->setREspecular(r_especulares[i][0], r_especulares[i][1], r_especulares[i][2], r_especulares[i][3]);
            if(i==0){
              sistema_solar[i]->esfera->material->setREmision(1, 1, 0.8, 1); //Para que así emita luz a los demás planetas
            }
            sistema_solar[i]->esfera->material->setShininess(sombras[i]);
            sistema_solar[i]->esfera->material->aniadirTextura(texturas[i]);
            if(i==6){
              sistema_solar[i]->esfera->material_anillo = new Material(); 
              if(sistema_solar[i]->esfera->material_anillo!=nullptr){
                sistema_solar[i]->esfera->material_anillo->setRAmbiental(0.2, 0.2, 0.2, 1);
                sistema_solar[i]->esfera->material_anillo->setRDifusa(0.8, 0.8, 0.8, 1);
                sistema_solar[i]->esfera->material_anillo->setREspecular(1, 1, 1, 1);
                sistema_solar[i]->esfera->material_anillo->setShininess(50);
                sistema_solar[i]->esfera->material_anillo->aniadirTextura("anillo_saturno.jpg");
              }         
            }
        }
        float aleatorio1 = (rand() / (float)RAND_MAX) / 10;
        sistema_solar[i]->esfera->setV(aleatorio1,0,aleatorio1);
       
    } 
  } 
}

#include <GL/gl.h>


  void giros_planetas(){
    if(!cambiar_mov){
      //Movimiento órbital
      //Traslacion planetas
      for(int i=0;i<sistema_solar.size();i++){
          float distancia = sistema_solar[i]->esfera->getDistancia();
          float angulo = sistema_solar[i]->rotar.getAngulo();

          float anguloRad = sistema_solar[i]->rotar.getAngulo() * (M_PI / 180);

          sistema_solar[i]->trasladar.setX(distancia*cos(anguloRad));
          sistema_solar[i]->trasladar.setZ(distancia*sin(anguloRad));

      }
      //Rotacion planetas
      for(int i=0;i<sistema_solar.size();i++){
          sistema_solar[i]->rotar.setAngulo(sistema_solar[i]->rotar.getAngulo()+velocidad_orbital[i]);
          if(sistema_solar[i]->rotar.getAngulo()>360){
            sistema_solar[i]->rotar.setAngulo(sistema_solar[i]->rotar.getAngulo()-360);
          }
      }
    }
    else{
      //Movimiento lineal para que así puedan colisionar
      for(int i=0;i<sistema_solar.size();i++){
      
        float vx = sistema_solar[i]->esfera->getVx();
        float vz = sistema_solar[i]->esfera->getVz();
        //Actualizar posición
        sistema_solar[i]->trasladar.setX(sistema_solar[i]->trasladar.getX()+vx);
        sistema_solar[i]->trasladar.setZ(sistema_solar[i]->trasladar.getZ()+vz);

        //Límites o paredes invisibles
        float limite = 5;
        if(sistema_solar[i]->trasladar.getX()>limite || sistema_solar[i]->trasladar.getX()< -limite){
          vx*=-1;
          sistema_solar[i]->esfera->setV(vx,0,vz);
        }
        if(sistema_solar[i]->trasladar.getZ()>limite || sistema_solar[i]->trasladar.getZ()< -limite){
          vz*=-1;
          sistema_solar[i]->esfera->setV(vx,0,vz);
        }
        //Actualizar velocidad
        sistema_solar[i]->esfera->setV(vx, 0, vz);
      }
    }
  }


  void detectarColisiones(){
    for (int i = 0; i < sistema_solar.size(); i++) {
        for (int j = i + 1; j < sistema_solar.size(); j++) {
            float dx = sistema_solar[i]->trasladar.getX() - sistema_solar[j]->trasladar.getX();
            float dz = sistema_solar[i]->trasladar.getZ() - sistema_solar[j]->trasladar.getZ();
            float distancia = sqrt(dx * dx + dz * dz);

            if (distancia < sistema_solar[i]->esfera->getRadio() + sistema_solar[j]->esfera->getRadio()) {
                // Invierte la dirección del ángulo de ambos planetas para simular rebote
                float vx1 = sistema_solar[i]->esfera->getVx();
                float vz1 = sistema_solar[i]->esfera->getVz();
                float vx2 = sistema_solar[j]->esfera->getVx();
                float vz2 = sistema_solar[j]->esfera->getVz();

                // Intercambia las velocidades en el eje X y Z para simular un rebote
                sistema_solar[i]->esfera->setV(vx2, 0, vz2); 
                sistema_solar[j]->esfera->setV(vx1, 0, vz1); 

            }
        }
    }
  }

  //Añadir luz al sol para que ilumine a los demás planetas
  void configurarLuzGlobal(){
    GLfloat luz_ambiental[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat luz_difusa[] = {1.0, 1.0, 0.8, 1.0};
    GLfloat luz_especular[] = {1.0, 1.0, 0.8, 1.0};
    GLfloat posicion_luz[] = {sistema_solar[0]->trasladar.getX(),sistema_solar[0]->trasladar.getY(),sistema_solar[0]->trasladar.getZ(),1};

    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiental);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicion_luz);

    glEnable(GL_LIGHT0); 
  }

  Objeto3D::Objeto3D(int id){
    this->id_color=id;  
    this->malla=nullptr;
    this->cubo = nullptr;  
    this->esfera = nullptr; 
    
  }

  Objeto3D::Objeto3D(){
    this->id_color=0;
    this->malla=nullptr;
    this->cubo = nullptr;   
    this->esfera = nullptr;
    
    
  }

  void Objeto3D::addHijo(Objeto3D* hijo){
      hijos.push_back(hijo);
  }


  void Objeto3D::addMovimientos(Transformacion* hijo){
    movimientos.push_back(hijo);
  }
 

  void Objeto3D::draw() {
    glPushMatrix();
    {
        
        ColorSeleccion(id_color);


        glPushMatrix();
        trasladar.draw(); 
        

        glPushMatrix();
        rotar.draw(); 
        
     
        for (Transformacion* hijo : movimientos) {
          
          hijo->draw();
              
        }
    
        /*if (malla != nullptr) {
          
            malla->draw(); 
        }*/

        if (esfera != nullptr) {
          esfera->draw_textura();
          esfera->draw_anillo();
        }
        
        
        /*glPushMatrix();
        {
            for (Transformacion* hijo : movimientos) {
                hijo->draw(); 
            }        
        }
        glPopMatrix(); */
        glPopMatrix();
        glPopMatrix();
    }
    glPopMatrix(); 
  }

  Material::Material(){
    texId=0;
  }

  void Material::aniadirTextura(const char *nombre_arch){

    unsigned ancho,alto;

    //Cargar imagen
    unsigned char* imagen;
    imagen=LeerArchivoJPEG(nombre_arch,ancho,alto);

    //Generar un identificador de textura
    glGenTextures(1,&texId);

    
    //Configurar y cargar la textura
    glBindTexture(GL_TEXTURE_2D, texId);

    //Establecer los parametros
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    //Construir el mipmaps
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,ancho,alto,0,GL_RGB,GL_UNSIGNED_BYTE,imagen);

  }

  void Material::setRDifusa(float r,float g,float b,float o){
    this->r_difusa[0]=r;
    this->r_difusa[1]=g;
    this->r_difusa[2]=b;
    this->r_difusa[3]=o;
  }

  void Material::setREspecular(float r,float g,float b,float o){
    this->r_difusa[0]=r;
    this->r_difusa[1]=g;
    this->r_difusa[2]=b;
    this->r_difusa[3]=o;
  }

  void Material::setRAmbiental(float r,float g,float b,float o){
    this->r_difusa[0]=r;
    this->r_difusa[1]=g;
    this->r_difusa[2]=b;
    this->r_difusa[3]=o;
  }

  void Material::setREmision(float r, float g, float b, float o){
    this->r_emision[0]=r;
    this->r_emision[1]=g;
    this->r_emision[2]=b;
    this->r_emision[3]=o;
  }

  void Material::setShininess(float shininess){
    this->shininess=shininess;
  }

  void Material::aplicarMaterial(){

    if (r_ambiental[0] == 0.0f && r_ambiental[1] == 0.0f && r_ambiental[2] == 0.0f) {
        this->r_ambiental[0] = r_difusa[0];
        this->r_ambiental[1] = r_difusa[1];
        this->r_ambiental[2] = r_difusa[2];
    }

    glMaterialfv(GL_FRONT, GL_AMBIENT, this->r_ambiental);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, this->r_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->r_especular);
    glMaterialfv(GL_FRONT, GL_EMISSION, this->r_emision);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->shininess);
  }

  Cubo::Cubo(){
      x=1;
      y=1;
      z=1;
      lado=1;
      
  }

  Cubo::Cubo(float _lado) {
    lado=_lado;
    x=-lado / 2;
    y=-lado / 2;
    z=-lado / 2;
    this->material = new Material();
    
  }


  Cubo::Cubo(float _lado,float _x,float _y,float _z){
    lado=_lado;
    x=_x;
    y=_y;
    z=_z;
    material = new Material();
    color[0] = 1;
    color[1] = 1;
    color[2] = 1;
    color[3] = 1;
  }

  void Cubo::cambiarColor(float r, float g, float b, float a) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
        color[3] = a;
  }

  float Cubo::getLado(){
    return lado;
  }
  float Cubo::getX(){
    return x;
  }
  float Cubo::getY(){
    return y;
  }
  float Cubo::getZ(){
    return z;
  }

  //Dibujar el cubo

  void Cubo::draw(){
    //if(material->texId!=0){
      if(glIsEnabled(GL_LIGHTING) ){
        if(!seleccion_cubo){
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D, material->texId);
          cambiarColor(1,1,1,1);
          glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
          //glEnable(GL_LIGHTING);
          
          //Crear cada cara del cubo
          glBegin(GL_QUADS);
          {
            glNormal3f(1.0, 0.0, 0.0);//Cara derecha
            glTexCoord2f(0.75,0.5); glVertex3f(x+lado, y, z);
            glTexCoord2f(1,0.5); glVertex3f(x+lado, y+lado, z);
            glTexCoord2f(1,0.75); glVertex3f(x+lado, y+lado, z+lado);
            glTexCoord2f(0.75,0.75); glVertex3f(x+lado, y, z+lado);

            glNormal3f(-1.0, 0.0, 0.0);//Cara izquierda
            glTexCoord2f(0.5,0.75);glVertex3f(x, y, z+lado);
            glTexCoord2f(0.25,0.75);glVertex3f(x, y+lado, z+lado);
            glTexCoord2f(0.25,0.5);glVertex3f(x, y+lado, z);
            glTexCoord2f(0.5,0.5);glVertex3f(x, y, z);

            glNormal3f(0.0, 0.0, -1.0);//Cara de atrás
            glTexCoord2f(0.5,0.25);glVertex3f(x, y+lado, z);
            glTexCoord2f(0.75,0.25);glVertex3f(x+lado, y+lado, z);
            glTexCoord2f(0.75,0.5);glVertex3f(x+lado, y, z);
            glTexCoord2f(0.5,0.5);glVertex3f(x, y, z);
            
            glNormal3f(0.0, 0.0, 1.0);//Cara de delante
            glTexCoord2f(0.5,1);glVertex3f(x, y+lado, z+lado);
            glTexCoord2f(0.5,0.75);glVertex3f(x, y, z+lado);
            glTexCoord2f(0.75,0.75);glVertex3f(x+lado, y, z+lado);
            glTexCoord2f(0.75,1);glVertex3f(x+lado, y+lado, z+lado);

            glNormal3f(0.0, 1.0, 0.0);//Cara de arriba
            glTexCoord2f(0.25,0.5);glVertex3f(x, y+lado, z);
            glTexCoord2f(0.25,0.75);glVertex3f(x, y+lado, z+lado);
            glTexCoord2f(0,0.75);glVertex3f(x+lado, y+lado, z+lado);
            glTexCoord2f(0,0.5);glVertex3f(x+lado, y+lado, z);

            glNormal3f(0.0, -1.0, 0.0);//Cara de abajo
            glTexCoord2f(0.5,0.5);glVertex3f(x, y, z);
            glTexCoord2f(0.75,0.5);glVertex3f(x+lado, y, z);
            glTexCoord2f(0.75,0.75);glVertex3f(x+lado, y, z+lado);
            glTexCoord2f(0.5,0.75);glVertex3f(x, y, z+lado);
          }
          glEnd();

          glDisable(GL_TEXTURE_2D);
        }
        else{
          glDisable(GL_TEXTURE_2D);     
          glBegin(GL_QUADS);
          {
            glNormal3f(1.0, 0.0, 0.0);//Cara derecha
            glTexCoord2f(0.75,0.5); glVertex3f(x+lado, y, z);
            glTexCoord2f(1,0.5); glVertex3f(x+lado, y+lado, z);
            glTexCoord2f(1,0.75); glVertex3f(x+lado, y+lado, z+lado);
            glTexCoord2f(0.75,0.75); glVertex3f(x+lado, y, z+lado);

            glNormal3f(-1.0, 0.0, 0.0);//Cara izquierda
            glTexCoord2f(0.5,0.75);glVertex3f(x, y, z+lado);
            glTexCoord2f(0.25,0.75);glVertex3f(x, y+lado, z+lado);
            glTexCoord2f(0.25,0.5);glVertex3f(x, y+lado, z);
            glTexCoord2f(0.5,0.5);glVertex3f(x, y, z);

            glNormal3f(0.0, 0.0, -1.0);//Cara de atrás
            glTexCoord2f(0.5,0.25);glVertex3f(x, y+lado, z);
            glTexCoord2f(0.75,0.25);glVertex3f(x+lado, y+lado, z);
            glTexCoord2f(0.75,0.5);glVertex3f(x+lado, y, z);
            glTexCoord2f(0.5,0.5);glVertex3f(x, y, z);
            
            glNormal3f(0.0, 0.0, 1.0);//Cara de delante
            glTexCoord2f(0.5,1);glVertex3f(x, y+lado, z+lado);
            glTexCoord2f(0.5,0.75);glVertex3f(x, y, z+lado);
            glTexCoord2f(0.75,0.75);glVertex3f(x+lado, y, z+lado);
            glTexCoord2f(0.75,1);glVertex3f(x+lado, y+lado, z+lado);

            glNormal3f(0.0, 1.0, 0.0);//Cara de arriba
            glTexCoord2f(0.25,0.5);glVertex3f(x, y+lado, z);
            glTexCoord2f(0.25,0.75);glVertex3f(x, y+lado, z+lado);
            glTexCoord2f(0,0.75);glVertex3f(x+lado, y+lado, z+lado);
            glTexCoord2f(0,0.5);glVertex3f(x+lado, y+lado, z);

            glNormal3f(0.0, -1.0, 0.0);//Cara de abajo
            glTexCoord2f(0.5,0.5);glVertex3f(x, y, z);
            glTexCoord2f(0.75,0.5);glVertex3f(x+lado, y, z);
            glTexCoord2f(0.75,0.75);glVertex3f(x+lado, y, z+lado);
            glTexCoord2f(0.5,0.75);glVertex3f(x, y, z+lado);
          }
          glEnd();
        }
      }        
      else{
        glDisable(GL_TEXTURE_2D);     
        glBegin(GL_QUADS);
        {
          glNormal3f(1.0, 0.0, 0.0);//Cara derecha
          glTexCoord2f(0.75,0.5); glVertex3f(x+lado, y, z);
          glTexCoord2f(1,0.5); glVertex3f(x+lado, y+lado, z);
          glTexCoord2f(1,0.75); glVertex3f(x+lado, y+lado, z+lado);
          glTexCoord2f(0.75,0.75); glVertex3f(x+lado, y, z+lado);

          glNormal3f(-1.0, 0.0, 0.0);//Cara izquierda
          glTexCoord2f(0.5,0.75);glVertex3f(x, y, z+lado);
          glTexCoord2f(0.25,0.75);glVertex3f(x, y+lado, z+lado);
          glTexCoord2f(0.25,0.5);glVertex3f(x, y+lado, z);
          glTexCoord2f(0.5,0.5);glVertex3f(x, y, z);

          glNormal3f(0.0, 0.0, -1.0);//Cara de atrás
          glTexCoord2f(0.5,0.25);glVertex3f(x, y+lado, z);
          glTexCoord2f(0.75,0.25);glVertex3f(x+lado, y+lado, z);
          glTexCoord2f(0.75,0.5);glVertex3f(x+lado, y, z);
          glTexCoord2f(0.5,0.5);glVertex3f(x, y, z);
          
          glNormal3f(0.0, 0.0, 1.0);//Cara de delante
          glTexCoord2f(0.5,1);glVertex3f(x, y+lado, z+lado);
          glTexCoord2f(0.5,0.75);glVertex3f(x, y, z+lado);
          glTexCoord2f(0.75,0.75);glVertex3f(x+lado, y, z+lado);
          glTexCoord2f(0.75,1);glVertex3f(x+lado, y+lado, z+lado);

          glNormal3f(0.0, 1.0, 0.0);//Cara de arriba
          glTexCoord2f(0.25,0.5);glVertex3f(x, y+lado, z);
          glTexCoord2f(0.25,0.75);glVertex3f(x, y+lado, z+lado);
          glTexCoord2f(0,0.75);glVertex3f(x+lado, y+lado, z+lado);
          glTexCoord2f(0,0.5);glVertex3f(x+lado, y+lado, z);

          glNormal3f(0.0, -1.0, 0.0);//Cara de abajo
          glTexCoord2f(0.5,0.5);glVertex3f(x, y, z);
          glTexCoord2f(0.75,0.5);glVertex3f(x+lado, y, z);
          glTexCoord2f(0.75,0.75);glVertex3f(x+lado, y, z+lado);
          glTexCoord2f(0.5,0.75);glVertex3f(x, y, z+lado);
        }
        glEnd();
      }
  }

  Esfera::Esfera(float radio, int divis, int capas, float distancia_centro){
      material = nullptr;
      material_anillo = nullptr;
      this->radio=radio;
      this->divis=divis;
      this->capas=capas;
      this->distancia_centro=distancia_centro;
      this->radioIntAnillo=0;
      this->radioExtAnillo=0;
      this->segAnillo=0;
      this->velocidad=Vertice();
  }

  Esfera::Esfera(float radio, int divis, int capas,float distancia_centro,float radioIntAnillo,float radioExtAnillo,float segAnillo){
    material = nullptr;
    material_anillo = nullptr;
    this->radio=radio;
    this->divis=divis;
    this->capas=capas;
    this->distancia_centro=distancia_centro;
    this->radioIntAnillo=radioIntAnillo;
    this->radioExtAnillo=radioExtAnillo;
    this->segAnillo=segAnillo;
    this->velocidad=Vertice();
  }

  float Esfera::getRadio(){
    return this->radio;
  }

  int Esfera::getDivis(){
    return this->divis;
  }

  int Esfera::getCapas(){
    return this->capas;
  }

  float Esfera::getDistancia(){
    return this->distancia_centro;
  }

  void Esfera::setV(float vx,float vy,float vz){
    this->velocidad.x=vx;
    this->velocidad.y=vy;
    this->velocidad.z=vz;

  }

  float Esfera::getVx(){
    return this->velocidad.x;
  }

  float Esfera::getVz(){
    return this->velocidad.z;
  }

  void Esfera::draw_anillo(){
  
    glBegin(GL_TRIANGLE_STRIP); // Usamos una tira de triángulos para el anillo
    
    for (int i = 0; i <= segAnillo; i++) {
        float theta = 2 * M_PI * i / segAnillo; // Ángulo en radianes

        //Coordenadas de textura, en este caso no se calcula v debido
        //a que el anillo no tiene altura

        float u =(float)i / segAnillo;

        // Coordenadas para el radio interno
        float xInterno = radioIntAnillo * cos(theta);
        float zInterno = radioIntAnillo * sin(theta);

        // Coordenadas para el radio externo
        float xExterno = radioExtAnillo * cos(theta);
        float zExterno = radioExtAnillo * sin(theta);

        glTexCoord2f(u,0);glVertex3f(xInterno, 0, zInterno); // Vértice en el radio interno 
        glTexCoord2f(u,1);glVertex3f(xExterno, 0, zExterno); // Vértice en el radio externo
    }

    glEnd();
    
  }

  void Esfera::draw() {
    for (int i = 0; i < capas; i++) {
        float phi1 = M_PI * i / capas;           // Ángulo para la capa superior
        float phi2 = M_PI * (i + 1) / capas;     // Ángulo para la capa inferior

        // Iteración sobre los segmentos alrededor del eje Y
        for (int j = 0; j <= divis; j++) { 
            float theta1 = 2 * M_PI * j / divis;       // Ángulo para la división actual
            float theta2 = 2 * M_PI * (j + 1) / divis; // Ángulo para la siguiente división

            // Coordenadas para los vértices de la capa superior
            float x1 = radio * sin(phi1) * cos(theta1);
            float y1 = radio * sin(phi1) * sin(theta1);
            float z1 = radio * cos(phi1);

            float x2 = radio * sin(phi1) * cos(theta2);
            float y2 = radio * sin(phi1) * sin(theta2);
            float z2 = radio * cos(phi1);

            // Coordenadas para los vértices de la capa inferior
            float x3 = radio * sin(phi2) * cos(theta1);
            float y3 = radio * sin(phi2) * sin(theta1);
            float z3 = radio * cos(phi2);

            float x4 = radio * sin(phi2) * cos(theta2);
            float y4 = radio * sin(phi2) * sin(theta2);
            float z4 = radio * cos(phi2);

            //Coordenadas de textura para 1º,2º,3º y 4º vertice

            float u1 = (float)j / (float)divis;
            float v1 = (float)i / (float)capas;

            float u2 = (float)(j + 1) / (float)divis;
            float v2 = (float)i / (float)capas;

            float u3 = (float)j / (float)divis;
            float v3 = (float)(i + 1) / (float)capas;

            float u4 = (float)(j + 1) / (float)divis;
            float v4 = (float)(i + 1) / (float)capas;

            // Primer triángulo (vértices 1, 3, 2)
            glBegin(GL_TRIANGLES);
            {
            
            glNormal3f(x1 / radio, y1 / radio, z1 / radio);
            glTexCoord2d(u1,v1);glVertex3f(x1, y1, z1);

            glNormal3f(x3 / radio, y3 / radio, z3 / radio);
            glTexCoord2d(u3,v3);glVertex3f(x3, y3, z3);

            glNormal3f(x2 / radio, y2 / radio, z2 / radio);
            glTexCoord2d(u2,v2);glVertex3f(x2, y2, z2);
            glEnd();

            

            // Segundo triángulo (vértices 2, 3, 4)
            glBegin(GL_TRIANGLES);
            glNormal3f(x2 / radio, y2 / radio, z2 / radio);
            glTexCoord2d(u2,v2);glVertex3f(x2, y2, z2);

            glNormal3f(x3 / radio, y3 / radio, z3 / radio);
            glTexCoord2d(u3,v3);glVertex3f(x3, y3, z3);

            glNormal3f(x4 / radio, y4 / radio, z4 / radio);
            glTexCoord2d(u4,v4);glVertex3f(x4, y4, z4);
            }
            glEnd();

            
        }
    } 
  }

  void Esfera::draw_textura(){
    if (glIsEnabled(GL_LIGHTING)) {
      if(material!=nullptr){
        material->aplicarMaterial();  // Aplica el material al objeto

        if(material->texId!=0){
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D,material->texId);
        }

        draw();
      }
     
      if(material_anillo!=nullptr){
        material_anillo->aplicarMaterial(); //Aplica el material del anillo

        if(material_anillo->texId!=0){
          glBindTexture(GL_TEXTURE_2D,material_anillo->texId);
        }
          
          draw_anillo();
      }
        
      glDisable(GL_TEXTURE_2D);
    }
    else{
      glDisable(GL_TEXTURE_2D);
      draw();
      draw_anillo();
    } 
  } 

  Normal::Normal(){
    x=y=z=0;
  }

  Normal::Normal(float x,float y,float z){
    this->x=x;
    this->y=y;
    this->z=z;
  }

  void Normal::normalizar(){
    float modulo = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
    if(modulo>0){
      this->x/=modulo;
      this->y/=modulo;
      this->z/=modulo;
    }
  }

  void Normal::sumarNormal(Normal n1){
    this->x+=n1.x;
    this->y+=n1.y;
    this->z+=n1.z;
  }

  Vertice::Vertice(){
    x=y=z=0;
  }

  Vertice::Vertice(float x,float y,float z,Normal normal){
    this->x=x;
    this->y=y;
    this->z=z;
    this->normal=normal;
  }

  Triangulo::Triangulo(){
    Vertice v1,v2,v3;
    Normal normal;
  }

  Triangulo::Triangulo(Vertice v1,Vertice v2,Vertice v3,Normal normal,vector<int> indice_vertice){
    this->normal=normal;
    this->v1=v1;
    this->v2=v2;
    this->v3=v3;
    this->indice_vertice=indice_vertice;

  }

  Triangulo& Triangulo::operator=(const Triangulo& otro){
    if(this != &otro){
            v1=otro.v1;
            v2=otro.v2;
            v3=otro.v3;
            normal=otro.normal;
            indice_vertice=otro.indice_vertice;
          }
          return *this;
  }

  Malla::Malla(vector<Vertice> &vert,vector<Triangulo> &tri){
    this->vert=vert;
    this->tri=tri;
  }

  void Malla::setVertice(Vertice v){
    vert.push_back(v);
    
  }

  void Malla::setTriangulo(Triangulo t){
    tri.push_back(t);

  }

  Malla::Malla(string archivoply){
    vector<float> vertices_ply;
    vector<int> caras_ply;

    ply::read(archivoply.c_str(),vertices_ply,caras_ply);

    //Añadir el vertice al conjuntos de vertices
    for(int i=0;i<vertices_ply.size();i+=3){
      Vertice v;
      v.x=vertices_ply[i];
      v.y=vertices_ply[i+1];
      v.z=vertices_ply[i+2];
      setVertice(v);
    }

    //Añadir las caras al conjunto de triangulos
    for(int i=0;i<caras_ply.size();i+=3){
      Triangulo tri;
      tri.v1=vert[caras_ply[i]];
      tri.v2=vert[caras_ply[i+1]];
      tri.v3=vert[caras_ply[i+2]];
      
      tri.indice_vertice.push_back(caras_ply[i]);
      tri.indice_vertice.push_back(caras_ply[i+1]);
      tri.indice_vertice.push_back(caras_ply[i+2]);

      setTriangulo(tri);
    }
    this->material = new Material();
    
  }

  void Malla::calcularNormal(){

    //Normales de los vertices a 0
    for(int i=0;i<vert.size();i++){
      vert[i].normal=Normal();
    }

    //Calular las normales de las caras
    for(int i=0;i<tri.size();i++){
      //Calculo dos vectores en el plano de la cara
      Vertice vct1,vct2;
      vct1.x=tri[i].v2.x-tri[i].v1.x;
      vct1.y=tri[i].v2.y-tri[i].v1.y;
      vct1.z=tri[i].v2.z-tri[i].v1.z;

      vct2.x=tri[i].v3.x-tri[i].v1.x;
      vct2.y=tri[i].v3.y-tri[i].v1.y;
      vct2.z=tri[i].v3.z-tri[i].v1.z;

      //Producto cartesiano de los vectores para hallar la normal
      tri[i].normal.x = vct1.y * vct2.z - vct1.z * vct2.y;
      tri[i].normal.y = vct1.z * vct2.x - vct1.x * vct2.z;
      tri[i].normal.z = vct1.x * vct2.y - vct1.y * vct2.x;

      //Normalizar la normal obtenida
      tri[i].normal.normalizar();

      //Sumar la normal de la cara a los vertices de esa cara y normalizar
      //cada suma obtenida
      vert[tri[i].indice_vertice[0]].normal.sumarNormal(tri[i].normal);
      vert[tri[i].indice_vertice[0]].normal.normalizar();

      vert[tri[i].indice_vertice[1]].normal.sumarNormal(tri[i].normal);
      vert[tri[i].indice_vertice[1]].normal.normalizar();

      vert[tri[i].indice_vertice[2]].normal.sumarNormal(tri[i].normal);
      vert[tri[i].indice_vertice[2]].normal.normalizar();
      
    }
  }

  void Malla::drawIluminacionPorCaras(){
    glShadeModel(GL_FLAT);
    //ColorSeleccion(objeto.id_color);

      glBegin(GL_TRIANGLES);
      {
        for(int i=0;i<tri.size();i++){
          
          glNormal3f(tri[i].normal.x,tri[i].normal.y,tri[i].normal.z);
          glTexCoord2f(coordenadas_tex[tri[i].indice_vertice[0]].first,coordenadas_tex[tri[i].indice_vertice[0]].second);
          glVertex3d(vert[tri[i].indice_vertice[0]].x,vert[tri[i].indice_vertice[0]].y,vert[tri[i].indice_vertice[0]].z);
          glTexCoord2f(coordenadas_tex[tri[i].indice_vertice[1]].first,coordenadas_tex[tri[i].indice_vertice[1]].second);
          glVertex3d(vert[tri[i].indice_vertice[1]].x,vert[tri[i].indice_vertice[1]].y,vert[tri[i].indice_vertice[1]].z);
          glTexCoord2f(coordenadas_tex[tri[i].indice_vertice[2]].first,coordenadas_tex[tri[i].indice_vertice[2]].second);
          glVertex3d(vert[tri[i].indice_vertice[2]].x,vert[tri[i].indice_vertice[2]].y,vert[tri[i].indice_vertice[2]].z);
          
        }
      }
      glEnd();
  }

  void Malla::drawIluminacionPorVertices(){
    glShadeModel(GL_SMOOTH);

      glBegin(GL_TRIANGLES);
        {
        for(int i=0;i<tri.size();i++){
          
            glNormal3f(vert[tri[i].indice_vertice[0]].normal.x,vert[tri[i].indice_vertice[0]].y,vert[tri[i].indice_vertice[0]].normal.z);
            glVertex3d(vert[tri[i].indice_vertice[0]].x,vert[tri[i].indice_vertice[0]].y,vert[tri[i].indice_vertice[0]].z);
            
            glNormal3f(vert[tri[i].indice_vertice[1]].normal.x,vert[tri[i].indice_vertice[1]].normal.y,vert[tri[i].indice_vertice[1]].normal.z);
            glVertex3d(vert[tri[i].indice_vertice[1]].x,vert[tri[i].indice_vertice[1]].y,vert[tri[i].indice_vertice[1]].z);

            glNormal3f(vert[tri[i].indice_vertice[2]].normal.x,vert[tri[i].indice_vertice[2]].normal.y,vert[tri[i].indice_vertice[2]].normal.z);
            glVertex3d(vert[tri[i].indice_vertice[2]].x,vert[tri[i].indice_vertice[2]].y,vert[tri[i].indice_vertice[2]].z);
        }
      }
      glEnd();
  }

  

  void Malla::draw(){
    
    if(glIsEnabled(GL_LIGHTING)){
      material->aplicarMaterial();
      if(material->texId!=0){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,material->texId);
        drawIluminacionPorCaras();
        glDisable(GL_TEXTURE_2D);
      }
      else{
        drawIluminacionPorVertices();
      }
    }
    else{
      glDisable(GL_TEXTURE_2D);
      drawIluminacionPorCaras();
    }
    
    
  }

  void Malla::calcularCentroyCaja(){
    float x_min = std::numeric_limits<float>::infinity();
    float y_min = std::numeric_limits<float>::infinity();
    float z_min = std::numeric_limits<float>::infinity();
    float x_max = -std::numeric_limits<float>::infinity();
    float y_max = -std::numeric_limits<float>::infinity();
    float z_max = -std::numeric_limits<float>::infinity();

    Vertice centro;

    for(int i=0;i<vert.size();i++){
      if(vert[i].x<x_min) x_min=vert[i].x;
      if(vert[i].y<y_min) y_min=vert[i].y;
      if(vert[i].z<z_min) z_min=vert[i].z;
      if(vert[i].x>x_max) x_max=vert[i].x;
      if(vert[i].y>y_max) y_max=vert[i].y;
      if(vert[i].z>z_max) z_max=vert[i].z;

      centro.x+=vert[i].x;
      centro.y+=vert[i].y;
      centro.z+=vert[i].z;
    }

    width = x_max - x_min;
    height = y_max - y_min;
    depth = z_max - z_min;

    dim_max=max(width,max(height,depth));

    for(auto& vertice:vert){
      float norm_x=(vertice.x-x_min-width/2)/dim_max;
      float norm_y=(vertice.y-y_min-height/2)/dim_max;
      float norm_z=(vertice.z-z_min-depth/2)/dim_max;
      vertice.normal.x=norm_x;
      vertice.normal.y=norm_y;
      vertice.normal.z=norm_z;
      vertice.normal.normalizar();
    }

    centro.x/=vert.size();
    centro.y/=vert.size();
    centro.z/=vert.size();
  }

    void Malla::calcularCoordTex(){
      //coordenadas_tex.clear();

      for(auto vertice:vert){
        float u,v;
        //Calculo del angulo 
        u = 0.5 + (0.5 / M_PI) * atan2(vertice.y, vertice.x);

        //Calcular la distancia radial
        v=(vertice.z-z_min)/(z_max-z_min);

        coordenadas_tex.emplace_back(u,v);
      }
    }

    

  Transformacion::Transformacion(){
      x=y=z=0;
  }

  float Transformacion::getX(){
    return this->x;
  }

  float Transformacion::getY(){
    return this->y;
  }

  float Transformacion::getZ(){
    return this->z;
  }

  void Transformacion::setX(float x){
    this->x=x;
  }

  void Transformacion::setY(float y){
    this->y=y;
  }

  void Transformacion::setZ(float z){
    this->z=z;
  }

  Rotacion::Rotacion(){
    this->angulo=0;
    this->x=0;
    this->y=0;
    this->z=0;
  }

  Rotacion::Rotacion(float angulo,float x,float y,float z){
    this->angulo=angulo;
    this->x=x;
    this->y=y;
    this->z=z;

  }

  void Rotacion::setAngulo(float angulo){
    
    this->angulo=angulo;
  }

  float Rotacion::getAngulo(){
    return this->angulo;
  }

  void Rotacion::draw() {
      glRotatef(angulo,x,y,z);
  }

  Traslacion::Traslacion(){
    x=0,y=0,z=0;
  }

  Traslacion::Traslacion(float x,float y,float z){
    this->x=x;
    this->y=y;
    this->z=z;
  }

  void Traslacion::setTraslacion(float x,float y,float z){
    this->x=x;
    this->y=y;
    this->z=z;
  }

  void Traslacion::draw() {
   
     glTranslatef(x,y,z);
      
  }

  Escalado::Escalado(){
    x=0,y=0,z=0;
  }

  Escalado::Escalado(float x,float y,float z){
    this->x=x;
    this->y=y;
    this->z=z;
  }

  void Escalado::setEscalado(float x,float y,float z){
    this->x=x;
    this->y=y;
    this->z=z;
  }

  void Escalado::draw() {
    
      glScalef(x,y,z);
    

  }

  class Ejes:Objeto3D 
  { 
  public: 
      float longitud = 30;
  // Dibuja el objeto
  void draw( )
  {
    glDisable (GL_LIGHTING);
    glBegin (GL_LINES);
    {
      glColor3f (0, 1, 0);
      glVertex3f (0, 0, 0);
      glVertex3f (0, longitud, 0);

      glColor3f (1, 0, 0);
      glVertex3f (0, 0, 0);
      glVertex3f (longitud, 0, 0);

      glColor3f (0, 0, 1);
      glVertex3f (0, 0, 0);
      glVertex3f (0, 0, longitud);
    }
    glEnd ();
    glEnable (GL_LIGHTING);

  }
  } ; 

  Ejes ejesCoordenadas;

  void ColorSeleccion( int i)
  {
    unsigned char r = (i & 0xFF);
    unsigned char g = 0;
    //(componente & 0xFF);
    glColor3ub(r,g,0);  
  }

  void dibujoEscena(/*bool seleccion*/){

  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

        float  color[4] = { 0.8, 0.0, 1, 1 };

        glPushMatrix ();		// Apila la transformacion geometrica actual

        glClearColor (0.0, 0.0, 0.1, 1.0);	// Fija el color de fondo a negro

        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

        transformacionVisualizacion ();	// Carga transformacion de visualizacion

        glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

        /*if(glIsEnabled(GL_LIGHTING)){
          ejesCoordenadas.draw();			// Dibuja los ejes

          glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
        }*/

        configurarLuzGlobal();
      
        for(int i=0;i<sistema_solar.size();i++){
          sistema_solar[i]->draw();
        }

        glPopMatrix ();		// Desapila la transformacion geometrica 
  }

  int pick(int x,int y){
    GLint viewport[4];
    unsigned char data[4];
    glGetIntegerv (GL_VIEWPORT, viewport);
    glDisable(GL_DITHER);
    glDisable(GL_LIGHTING);
    dibujoEscena(/*seleccion*/);
    glEnable(GL_LIGHTING);
    glEnable(GL_DITHER);
    glFlush();
    glFinish();
    glReadPixels(x,viewport[3]-y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,data);
    
    
    glutPostRedisplay();
    return data[0];
  }


  /**	void Dibuja( void )

  Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

  **/


  void Dibuja(void){
    
    if(!stop_giro)
    giros_planetas();
    detectarColisiones();
    dibujoEscena(/*seleccion*/);
    glutSwapBuffers();
  }


  /**	void idle()

  Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

  **/
  void idle (int v)
  {
    glutPostRedisplay ();		
    glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
  }
