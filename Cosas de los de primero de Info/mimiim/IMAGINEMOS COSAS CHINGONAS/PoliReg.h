/*
Jorge López Molina
DNI: 78114273V
Marino Fernández Pérez
DNI: 75941131F
1ºA grupo 2
*/

#ifndef POLIREG_H
#define POLIREG_H

#include <iostream>
#include "Punto2D.h"

using namespace std;

class PoliReg {
private:
    Punto2D *vertices;
    int N;
    Punto2D centro;
    float radio;

    void _reservaMemoria(int tam);

    void _liberaMemoria();

    void _generaVertices();
    
    void _copia(const PoliReg & copia);
    
public:
    
    static const int MAX_PTOS;
    static const float MAX_RADIO;
    static const int MIN_PTOS;
    static const float MIN_RADIO;
    
    PoliReg();

    PoliReg(int nro_ptos,const Punto2D & centro,float radio);

    PoliReg(const PoliReg & copia);

    //destructor

    ~PoliReg();
    
    void agregaVertice();

    void eliminaVertice();

    Punto2D getVertice(int ident) const{
        return vertices[ident];
    }

    Punto2D getCentro() const{
        return centro;
    }

    int getNroPtos() const{
        return N;
    }

    float getRadio() const{
        return radio;
    }

    int getLados() const{
        return N;
    }
    
    void setCentro(const Punto2D & nuevo){
    	centro = nuevo;
    	
    	_generaVertices();
    }
    
    void expande(float delta);

    void contrae(float delta);

    float perimetro() const;

    void rotar(float rads);

    bool colision(const PoliReg & otro) const;

    void mover(float dx, float dy);
    
    PoliReg& operator=(const PoliReg & rhs);
    
    friend ostream& operator<<(ostream &flujo, const PoliReg &poli);
    
    friend istream& operator>>(istream &flujo, PoliReg &poli);
    
    bool operator==(const PoliReg& otro) const;
    
    bool operator<(const PoliReg& b) const;
};

#endif

