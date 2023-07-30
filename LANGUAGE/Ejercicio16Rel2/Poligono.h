/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Poligono.h
 * Author: roberlks222
 *
 * Created on May 8, 2023, 10:52 PM
 */

#ifndef POLIGONO_H
#define POLIGONO_H

#include <iostream>
#include <fstream>
#include "Punto.h"
using namespace std;

class Poligono{
    int nVertices; // N ́umero de puntos en el array din ́amico
    Punto *vertices; // Array din ́amico de objetos Punto
    public:
        Poligono();
        Poligono(int n);
        void liberar();
        int getNumeroVertices() const;
        Punto getVertice(int index) const;
        void addVertice(const Punto& v);
        double getPerimetro() const;
        double getArea() const;
        Punto getPuntoInterior() const{return vertices[0];}
        void mostrar(ostream& flujo);
        void leer(istream& flujo);
};
#endif /* POLIGONO_H */

