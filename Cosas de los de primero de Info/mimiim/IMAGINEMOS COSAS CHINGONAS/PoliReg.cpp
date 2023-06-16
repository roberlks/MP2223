/*
Jorge López Molina
DNI: 78114273V
Marino Fernández Pérez
DNI: 75941131F
1ºA grupo 2
*/

#include "Punto2D.h"
#include "PoliReg.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int PoliReg::MAX_PTOS = 200;
const float PoliReg::MAX_RADIO = 200.0;
const int PoliReg::MIN_PTOS = 3;
const float PoliReg::MIN_RADIO = 15.0;

void PoliReg::_reservaMemoria(int tam){
    
    if (vertices != 0){
        _liberaMemoria();
    }
    
    vertices = new Punto2D [tam];
}

void PoliReg::_liberaMemoria(){
    delete [] vertices;
    vertices = 0;
}

void PoliReg::_generaVertices(){
    Punto2D vertice_valido(centro.getX(),centro.getY()-radio);

    vertices[0] = vertice_valido; 

    float rads_girar = (360/N) * M_PI / 180;

    for (int i = 1 ; i < N ; i++){
        vertice_valido.rotar(centro,rads_girar);
        vertices[i] = vertice_valido;
    }
}

void PoliReg::_copia(const PoliReg & copia){
    centro = copia.getCentro();
    radio = copia.getRadio();
    N = copia.getNroPtos();

    for (int i = 0 ; i < N ; i++){
        vertices[i] = copia.getVertice(i);
    }
}

PoliReg::PoliReg(){
    centro.setXY(0,0);
    radio = PoliReg::MIN_RADIO;
    N = PoliReg::MIN_PTOS;
    vertices = 0;

    _reservaMemoria(N);
    _generaVertices();
}

PoliReg::PoliReg(int nro_ptos, const Punto2D & _centro, float radio):centro(_centro){
    
    this->radio = radio;
    N = nro_ptos;
    
    if (radio < PoliReg::MIN_RADIO || radio > PoliReg::MAX_RADIO){
        this->radio = PoliReg::MIN_RADIO;
    }

    if (nro_ptos < PoliReg::MIN_PTOS || nro_ptos > PoliReg::MAX_PTOS){
        this->N = PoliReg::MIN_PTOS;
    }
    
    vertices = 0;

    _reservaMemoria(N);
    _generaVertices();
}

PoliReg::PoliReg(const PoliReg & copiar){
    vertices = 0;
    
    _reservaMemoria(copiar.getNroPtos());
    _copia(copiar);
}

PoliReg::~PoliReg(){
    _liberaMemoria();
}

void PoliReg::agregaVertice(){
    if ((N + 1) <= PoliReg::MAX_PTOS){
        _liberaMemoria();
        N++;

        _reservaMemoria(N);
        _generaVertices();
    }
}

void PoliReg::eliminaVertice(){
    if ((N - 1) >= PoliReg::MIN_PTOS){
        _liberaMemoria();
        
        N--;
        _reservaMemoria(N);
        _generaVertices();
    }
}

void PoliReg::expande(float delta){
    if (delta > 0){
        float new_rad = radio+delta;

        if (new_rad <= PoliReg::MAX_RADIO){
            radio = new_rad;
            _generaVertices();
        }
    }
}

void PoliReg::contrae(float delta){
    if (delta > 0){
        float new_rad = radio - delta;

        if (new_rad >= PoliReg::MIN_RADIO){
            radio = new_rad;            
            _generaVertices();
        }
    }
}

float PoliReg::perimetro() const{
    float un_lado = vertices[0].distancia(vertices[1]);
    return un_lado*N;
}

void PoliReg::rotar(float rads){
    for (int i = 0 ; i < N ; i++){
        vertices[i].rotar(centro, rads);
    }
}
//aqui he cambiado cosas si falla puede que sea por esto.

//he recompilado y no falla luego no es probable que esto este mal
bool PoliReg::colision(const PoliReg & otro) const{
    
    bool intersecan = false;

    if (this != &otro){ //proteccion para no medir la colision sobre si mismo
        
        float dist_centros = centro.distancia(otro.getCentro());
        float suma_radios = radio + otro.getRadio();

        if (dist_centros <= suma_radios){
            intersecan = true;
        }
        
    }

    return intersecan;
}

void PoliReg::mover(float dx, float dy){
    centro.mover(dx,dy);

   for (int i = 0 ; i < N ; i++){
        vertices[i].mover(dx,dy);
   } 
}

PoliReg& PoliReg::operator=(const PoliReg & rhs){
    if (this != &rhs){
        _liberaMemoria(); 
        _reservaMemoria(rhs.getNroPtos());
        _copia(rhs);
    }

    return (*this);
}

ostream& operator<<(ostream &flujo, const PoliReg &poli){
    flujo <<"@centro: " << poli.centro << "\n";
    flujo <<"@radio: " << poli.radio << "\n";
    flujo <<"@Puntos: " << poli.N << "\n";
    
    for (int i = 0; i < poli.N; i++){
        flujo << poli.vertices[i];
        flujo << "\n";
    }
    
    return flujo;
}

istream& operator>>(istream &flujo, PoliReg &poli){
    int n;
    float radio;
    Punto2D centro;
    string basura1 = "";
    //string basura2 = "";
    //string basura3 = "";
    
    flujo >> basura1;
    flujo >> centro;
    flujo >> basura1;
    flujo >> radio;
    flujo >> basura1;
    flujo >> n;

    PoliReg aux(n, centro, radio);
    poli = aux;
    
    for (int i = 0; i < poli.N; i++)
        flujo >> poli.vertices[i];
    
    return flujo;
}

bool PoliReg::operator==(const PoliReg& otro) const{
    
    bool son_iguales = false;
    
    if (this->N == otro.getNroPtos()){
        son_iguales = true;
        
        for (int i = 0; i < N && son_iguales; i++){
            if (!(vertices[i] == otro.getVertice(i)))
                son_iguales = false;
        }
    }
    
    return son_iguales;
}

bool PoliReg::operator<(const PoliReg& b) const{
    return this->perimetro() < b.perimetro();
 }

