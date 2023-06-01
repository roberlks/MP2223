/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: roberlks222
 *
 * Created on May 8, 2023, 10:50 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Poligono.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    bool entradaEstandar = false;
    if (argc == 1){
        entradaEstandar = true;
    }
    
    Poligono mipol;
    if (entradaEstandar){
        cout << "Introduzca un poligono: ";
        mipol.leer(cin);
    }
    else {
        ifstream in;
        in.open(argv[1]);
        mipol.leer(in);
    }
    
    mipol.mostrar(cout);
    
    cout << endl << "Area= " << mipol.getArea() << endl 
         << "Perimetro= " << mipol.getPerimetro();
    mipol.liberar();
    
    return 0;
}

