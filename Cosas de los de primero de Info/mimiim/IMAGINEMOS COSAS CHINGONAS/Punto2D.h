/*
Jorge López Molina
DNI: 78114273V
Marino Fernández Pérez
DNI: 75941131F
1ºA grupo 2
*/

#ifndef _PUNTO2D_
#define _PUNTO2D_

#include <iostream>
#include <string>

using namespace std;

//const int MAX_VEL = 6;
const int MIN_DIM = 750;
const float UMBRAL = 0.1;
//const float PI = 3.141592;    

class Punto2D {
private:
    float x, y;
    void AjustarPosicion(int ancho, int alto); 
    
public:
    Punto2D();

    // constructor con parámetros
    Punto2D(float _x, float _y) : x(_x), y(_y){
    };

    // Setters / Getters
    float getX() const;
    float getY() const;
    
    void setXY(float, float);
    
    // calcula distancia euclidea entre dos puntos
    float distancia(const Punto2D & otro) const; 
    
    // detecta si hay colisión entre dos puntos
    // la distancia tiene que ser menor que la suma de sus radios
    bool colision(const Punto2D & otro) const; 
    

    // cambia la posicion, sumándole la velocidad
    void mover(float dx, float dy);
    
    
    // rota la partícula sobre el punto (posX, posY) rads radianes
    // Si quiere transformar grados a radianes debe hacer 
    // rads = grados * (M PI / 180.0). La constanteM_PI esta definida en cmath.
    void rotar(const Punto2D & pivot, float rads);
    
    // transforma el contenido de la particula en un string
    std::string toString() const;

    void moverHacia(const Punto2D & destino, float speed);
    
    friend ostream& operator<<(ostream &flujo, const Punto2D &punto);
    
    friend istream& operator>>(istream &flujo, Punto2D &punto);
    
    bool operator==(const Punto2D & otro);
};

#endif
