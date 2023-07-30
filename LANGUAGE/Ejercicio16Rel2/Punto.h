/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Punto.h
 * Author: roberlks222
 *
 * Created on May 8, 2023, 10:51 PM
 */

#ifndef PUNTO_H
#define PUNTO_H

#include <cmath>



class Punto{
    double x;
    double y;
    public:
        double getDistancia(Punto otro) const;
        Punto(){x=0; y=0;};
        Punto(int x, int y){this->x=x; this->y=y;};
        double getX() const{return x;};
        double getY() const{return y;};
        void setXY(int x, int y){this->x=x; this->y=y;};
};


#endif /* PUNTO_H */

