#ifndef CONJUNTOASTEROIDE_H
#define CONJUNTOASTEROIDE_H

#include "PoliReg.h"
#include "Punto2D.h"
#include "Asteroide.h"
#include <iostream>

class ConjuntoAsteroides{
private:    
    Asteroide conjunto[40];
    int util;
    
    void _borrado(int ind);
public:
    
    ConjuntoAsteroides();
    
    Asteroide& getElemento(int ind){ //creo que deberia ser const
        return conjunto[ind];
    }
    
    int getUtil() const{ //creo que deberia ser const
        return util;
    }
    
    Punto2D getPosicion(int ind) const{
        return conjunto[ind].getPosicion();
    }
    
    void aniade(const Punto2D & posicion, bool ast_o_disp);
    void contrae();
    bool colisionaPropio();
    bool colisionaOtro(ConjuntoAsteroides & otro);
    
    void eliminaLado(int ind);
    
    ConjuntoAsteroides &operator=(ConjuntoAsteroides & otro);
    
    Punto2D getPosicion(int ind);
};

#endif
