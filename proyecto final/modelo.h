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

=======================================================

	 modelo.h
*/

#include <vector>
#include "file_ply_stl.h"
#include "lector-jpg.h"
#include <GL/glut.h>
using namespace std;


/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja (void);

/**
	Funcion de fondo
**/
void idle (int v);

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel ();




//void procesarSeleccion(int pixelseleccionado);

/**
  Funcion de dibujado
**/
void dibujoEscena(/*bool seleccion*/);

void ColorSeleccion( int i);

void giros_planetas();

void detectarColisiones();

void configurarLuzGlobal();

int pick(int x,int y);

class Material{
    public:
        GLuint texId;        
        float r_difusa[4] = {1,1,1,1};
        float r_especular[4] ={1,1,1,1};
        float r_ambiental[4] = {0.2,0.2,0.2,1};
        float r_emision[4] = {0, 0, 0, 0}; //Es para que el sol sea emisor
        float shininess=0;
    
    Material();
    void aniadirTextura(const char *nombre_arch);
    void setRDifusa(float r,float g, float b, float o);
    void setREspecular(float r,float g,float b, float o);
    void setRAmbiental(float r,float g,float b,float o);
    void setREmision(float r, float g, float b, float o);
    void setShininess(float shininess);
    void aplicarMaterial();
};


class Cubo {
protected:
    float lado;
    float x, y, z;
    GLfloat color[4];
       

public:
    
    Material *material;
    Cubo();
    Cubo(float _lado);
    Cubo(float _lado, float _x, float _y, float _z);

    void cambiarColor(float r, float g, float b, float a);
    float getLado();
    float getX();
    float getY();
    float getZ();

    void draw();
    
};


class Transformacion{
    protected:
    float x,y,z;
   
    public:
    Transformacion();
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    
    float getX();
    float getY();
    float getZ();
    virtual void draw()=0;
    
};

class Rotacion : public Transformacion {
private:
    float angulo;
    
public:
    Rotacion();
    Rotacion(float angulo, float x, float y, float z);
    void setAngulo(float angulo);
    float getAngulo();

    void draw() override;
};

class Traslacion: public Transformacion {    

public:
	
	Traslacion();
    Traslacion(float x, float y, float z);
	void setTraslacion(float x,float y,float z);

    void draw() override;
};

class Escalado: public Transformacion {
public:

	Escalado();
    Escalado(float x, float y, float z);
	void setEscalado(float x,float y,float z);
    void draw() override;
};

class Normal{
    public:
    float x,y,z;

    Normal();
    Normal(float x,float y,float z);
    void normalizar();
    void sumarNormal(Normal n1);

};

struct Vertice{
    float x,y,z;
    Normal normal;
    Vertice();
    Vertice(float x,float y,float z,Normal normal);
};

struct Triangulo{
    Vertice v1,v2,v3;
    Normal normal;
    vector<int>indice_vertice;

    Triangulo();
    Triangulo(Vertice v1,Vertice v2,Vertice v3,Normal normal,vector<int> indice_vertice);
    Triangulo& operator=(const Triangulo& otro);
};

class Malla {
    protected:
        //Centro y limites de la malla
        Vertice centro;
        float width,height,depth,dim_max;
        float x_min,x_max,y_min,y_max,z_min,z_max;
        vector<Vertice> vert;
        vector<Triangulo> tri;
        vector<pair<float,float>> coordenadas_tex;
        
    public:
        
        Material *material;
        Malla(vector<Vertice>&,vector<Triangulo>&);
        void setVertice(Vertice v);
        void setTriangulo(Triangulo t);
        Malla(string archivoply);
        void calcularNormal();
        void drawIluminacionPorCaras();
        void drawIluminacionPorVertices();
        void draw();
        void calcularCentroyCaja();
        void calcularCoordTex();

};

class Esfera {
    private:
        float radio;
        int divis;
        int capas;
        float distancia_centro;
        float radioIntAnillo;
        float radioExtAnillo;
        int segAnillo;
        Vertice velocidad;
    
    public:

        Material *material;
        Material *material_anillo;

        Esfera(float radio, int divis, int capas,float distancia_centro);
        //Para inicializar la esferas que tengan anillo
        Esfera(float radio, int divis, int capas,float distancia_centro,float radioIntAnillo,float radioExtAnillo,float segAnillo);      
        float getRadio();
        int getDivis();
        int getCapas();
        float getDistancia();
        void setV(float vx,float vy,float vz);
        float getVx();
        float getVz();

        void draw_anillo();
        void draw();   
        void draw_textura();    
};

class Objeto3D 
{ 
public: 
    int id_color;
    vector<Objeto3D*> hijos;
    Malla *malla;
    Cubo *cubo;
    Esfera *esfera;
    Rotacion rotar;
    Traslacion trasladar;
    Escalado escalar;
    vector<Transformacion*> movimientos;
    bool anillo=false;
    
    

    //virtual void draw( ) = 0; // Dibuja el objeto
    Objeto3D();
    Objeto3D(int id);
    void draw();
    void addHijo(Objeto3D* hijo);
    void addMovimientos(Transformacion *hijo);
} ; 