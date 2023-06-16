#ifndef ASTEROIDE_H
#define ASTEROIDE_H

#include "PoliReg.h"
#include "Punto2D.h"
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Asteroide{
private:
    PoliReg roca;
    Punto2D veloc;
    float giro;
    
public:
    //lo genera con una forma aleatoria dependiendo de una serie de limites
    
    Asteroide();
    
    Asteroide(const PoliReg & pol);
    
    Asteroide(const PoliReg & pol,const Punto2D & vel,float rads/* = 10*/);
    
    Asteroide(const Asteroide & otro);
    
    //~Asteroide();
    
    void setGiro(float rads){
        giro = rads;
    }
    
    void setVeloc(const Punto2D & trayectoria){
       veloc = trayectoria; 
    }
    
    void setPosicion(const Punto2D & nuevo){
    	roca.setCentro(nuevo);
    }
    
    Punto2D getVeloc() const{
        return veloc;
    }
    
    float getGiro() const{
        return giro;
    }
    
    PoliReg getRoca() const{
        return roca;
    }
    
    void setRoca(const PoliReg & otra){
    	roca = otra;
    }
    
    void eliminaVertice();
    
    Punto2D getPosicion() const{
        return roca.getCentro(); 
    }
    
//    void moverLater(bool lado);
//    void moverVerti(bool direccion);
    void mover(bool direccion);
    
    void rotar();
    
    /*
    - se tiene que hacer un colisiona distinto en funcion si colisiona con otro asteroide o con un disparo?
    - puede tener una condicion que no cambie la velocidad si otro esta en el array de distparos
    - tiene que sobrecargarse el operador == entre asteroides llamando por ejemplo al == de PoliReg
    - array de asteroides y de disparos se hacen en el main o se tendria que elaborar otra clase?
    */
    bool colisiona(const Asteroide & otro) const;
    
    Asteroide& operator=(const Asteroide & rhs);
};

#endif
