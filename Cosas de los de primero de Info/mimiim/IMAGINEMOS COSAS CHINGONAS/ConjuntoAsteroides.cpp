#include "PoliReg.h"
#include "Punto2D.h"
#include "Asteroide.h"
#include "ConjuntoAsteroides.h"
#include <iostream>

using namespace std;

void ConjuntoAsteroides::_borrado(int ind){
    if (ind == util-1){
        contrae();
    }
    else{
        for (int i = ind ; i < util ; i++){
            conjunto[i] = conjunto[i+1];
        }
        contrae();
    }
}

ConjuntoAsteroides::ConjuntoAsteroides(){
    util = 0;
}

void ConjuntoAsteroides::aniade(const Punto2D & posicion ,bool ast_o_disp){ //aniade en la ultima posicion
	if (ast_o_disp){
	    if ((util + 1) <= 40){
    	        Asteroide nuevo;
   	
   	        nuevo.setPosicion(posicion);
   	
    	        conjunto[util] = nuevo;
    	        util++;
	    }
	}
	else{
	    if ((util + 1) <= 40){
    		PoliReg triangulo;
    	        Asteroide nuevo(triangulo);
   	
   	        nuevo.setPosicion(posicion);
   	        
   	        Punto2D trayectoria(0,-10);
   	   	nuevo.setVeloc(trayectoria);
   	
    	        conjunto[util] = nuevo;
    	        util++;
    	    }
	}
}

void ConjuntoAsteroides::contrae(){ //eliminara la ultima posicion, esto era lo que daba el puto problema esque ponia util -1 > 3 por la carisima
    if (util > 0){
        util--;
    }
    
    //tecnicamente nunca llegaria el momento de que esto ocurra
}

bool ConjuntoAsteroides::colisionaPropio(){
    
    for (int i = 0 ; i < util; i++){
        for (int j = 0 ; j < util; j++){ 
            //en principio no deberia dar problema cuando 
            //caiga en el mismo y lo trate de comprobar con
            //el mismo porque contra eso ya hemos protegido
            //al colisiona de Asteroides que llama a su vez
            //al colisiona de PoliReg
            
            if (conjunto[i].colisiona(conjunto[j])){
                return true;
            }
        }
    }
    
    return false;
}

bool ConjuntoAsteroides::colisionaOtro( ConjuntoAsteroides & otro){ //ya no son const porque se van a modificar
    
    for (int i = 0 ; i < util; i++){
        for (int j = 0 ; j < util; j++){ 
            if (conjunto[i].colisiona(otro.getElemento(j))){
                return true;
            }    
        }
    }
    return false;
    
}

void ConjuntoAsteroides::eliminaLado(int ind){
    int nro_lados = conjunto[ind].getRoca().getLados();
    
    if (nro_lados == PoliReg::MIN_PTOS){ //se asume que el dato introducido es correcto
        _borrado(ind);
    }
    else{
        conjunto[ind].eliminaVertice();
    }
}

ConjuntoAsteroides &ConjuntoAsteroides::operator=(ConjuntoAsteroides & otro){ //no me deja usar get elemento porque al ser un const ... & solo quiere que uses metodos const y getElemento no es const
    
    util = otro.getUtil();
    
    for (int i = 0 ; i < util ; i++){
        conjunto[i] = otro.getElemento(i);
    }
    
    return (*this);
}
