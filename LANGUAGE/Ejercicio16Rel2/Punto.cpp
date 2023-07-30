/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Punto.cpp
 * Author: roberlks222
 * 
 * Created on May 8, 2023, 10:51 PM
 */
#include "Punto.h"

double Punto::getDistancia(Punto otro) const{
    return (sqrt((double)(((getX()-otro.getX())*(getX()-otro.getX())+((getY()-otro.getY())*(getY()-otro.getY()))))));
}
