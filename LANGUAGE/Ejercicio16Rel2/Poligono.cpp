/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Poligono.cpp
 * Author: roberlks222
 * 
 * Created on May 8, 2023, 10:52 PM
 */

#include "Poligono.h"

double areaTriangulo(const Punto& pto1, const Punto& pto2, const Punto& pto3){
    double T =   0;
    double S1= pto1.getDistancia(pto2);
    double S2= pto2.getDistancia(pto3);
    double S3= pto3.getDistancia(pto1);
    T = ((S1 + S2 + S3)/2.0);
    double area = sqrt(T*(T-S1)*(T-S2)*(T-S3));
    return area;
}


Poligono::Poligono(){
    this->nVertices = 0;
    vertices = nullptr;
}

Poligono::Poligono(int n){
    this->nVertices = n;
    vertices = new Punto[n];
}

void Poligono::liberar(){
    delete [] this->vertices;
}

int Poligono::getNumeroVertices() const{
    return this->nVertices;
}

Punto Poligono::getVertice(int index) const{
    return vertices[index];
}
void Poligono::addVertice(const Punto& y){
    Punto *vertidos = nullptr;
    vertidos = new Punto[this->nVertices+1];
    for (int i = 0; i<nVertices; i++){
        vertidos[i] = this->vertices[i];
    }
    vertidos[nVertices] = y;
    delete [] vertices;
    this->nVertices++;
    vertices = vertidos;
}
double Poligono::getPerimetro() const{
    int per = 0;
    for(int i = 0; i < nVertices-1 ; i++){
        per += vertices[i].getDistancia(vertices[i+1]);
    }
    per += vertices[nVertices-1].getDistancia(vertices[0]);
    return per;
}

double Poligono::getArea() const{
    double area = 0;
    Punto puntoInt = getPuntoInterior();
    for (int i = 2; i < this->nVertices-1; i++){
        area += areaTriangulo(puntoInt, vertices[i-1], vertices[i]);
    }
    return area;
}

void Poligono::mostrar(ostream& flujo){
    flujo << this->nVertices << endl;
    for (int i = 0; i<this->nVertices; i++){
        flujo << this->vertices[i].getX() << " " << this->vertices[i].getY() << endl;
    }
}

void Poligono::leer(istream& flujo){
    this ->nVertices = 0;
    int nVert=0;
    flujo >> nVert;
    
    for (int i = 0; i<nVert; i++){
        int x, y;
        flujo >> x;
        flujo >> y;
        Punto tmp(x, y);
        addVertice(tmp);
    }
}
