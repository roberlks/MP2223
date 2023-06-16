#include "PoliReg.h"
#include "Punto2D.h"
#include "Asteroide.h"
#include <iostream>

/////////////////////////////////////////
//                                     //
//  NECESARIO METER PROTECCION A TODO  //
//                                     //
/////////////////////////////////////////

using namespace std;

Asteroide::Asteroide() : roca(random() % 8,Punto2D(),random() % 60){
    veloc.setXY(2,2); //por tomar una trayectoria con una velocidad ajustada; 
    giro = 0.1; //por ser un estandar de velocidad
}
    
Asteroide::Asteroide(const PoliReg & pol){
    veloc.setXY(2,2);
    roca = pol;
    giro = 0; //por considerar un estandar para el minimo radianes de giro;
}

//IMPORTANTE :: DAR VALORES DEFAULT AL RADS DA PROBLEMA NO SE MUY BIEN PORQUE
Asteroide::Asteroide(const PoliReg & pol, const Punto2D & vel, float rads /*=10*/) : roca(pol), veloc(vel), giro(rads){ //cabecera del maestro da fallos
}

Asteroide::Asteroide(const Asteroide & otro){
    giro = otro.getGiro();
    veloc = otro.getVeloc();
    roca =otro.getRoca();
}

void Asteroide::eliminaVertice(){
    roca.eliminaVertice();
}

//void Asteroide::moverLater(bool lado){ DE MOMENTO SOLO SE VA A MOVER DE FORMA NORMAL
//    if (lado){	
//        roca.mover(veloc.getX(),veloc.getY()); 
//    }
//    else{
//    	roca.mover(-veloc.getX(),-veloc.getY());
//    }
//}
//
//void Asteroide::moverVerti(bool direccion){
//    if (direccion){	
//        roca.mover(veloc.getY(),veloc.getX()); 
//    }
//    else{
//    	roca.mover(-veloc.getY(),-veloc.getX());
//    }
//
//}

void Asteroide::mover(bool direccion){
    if (direccion){
        roca.mover(veloc.getX(),veloc.getY());
    }
    else{
        roca.mover(-veloc.getX(),-veloc.getY());
    }
}

void Asteroide::rotar(){
    roca.rotar(giro);
}

bool Asteroide::colisiona(const Asteroide & otro) const{
    return (roca.colision(otro.getRoca()));
}

Asteroide& Asteroide::operator=(const Asteroide & rhs){
    roca = rhs.getRoca(); //esto se puede hacer porque esta sobrecargado el operador de la clase PoliReg.
    giro = rhs.getGiro();
    veloc = rhs.getVeloc(); 
    
    return (*this);
}
