    /*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   ArrayBigramFreqFunctions.cpp
 * Author: roberlks222
 * 
 * Created on 8 de marzo de 2023, 18:38
 */

#include <iostream>
#include <string>

#include "ArrayBigramFreqFunctions.h"
//#define NoRedirect

using namespace std;

void readArrayBigramFreq(BigramFreq array[], int dim, int &nElements){
    
    #ifdef NoRedirect
    cout << "Introduzca el numero de caracteres: ";
    #endif
    cin >> nElements;
    
    if (nElements > dim) nElements = dim;
    if (nElements < 0) nElements = 0;
    
    for (int i = 0; i < nElements; i++){
        
        //Read Bigram (as string)
        #ifdef NoRedirect
        cout << "Introduzca el elemento " << i << " :";
        #endif
        string cad;
        cin >> cad;
        
        //Read frequency (int)
        #ifdef NoRedirect
        cout << "Introduzca la frecuencia del elemento " << i << " :";
        #endif
        int num;
        cin >> num;
        
        //Add to array in i position
        array[i].setBigram(Bigram(cad)); //Using anonymous default constructor
        array[i].setFrequency(num);
    }
    
    
} //readArrayBigramFreq

void printArrayBigramFreq (const BigramFreq array[], int nElements){
        
    cout << nElements << endl;
    
        for (int i = 0; i < nElements; i++){
        
        cout << array[i].toString() << endl;
    }
}

void swapElementsArrayBigramFreq(BigramFreq array[], int nElements, int first, int second){
    
    if (first >= nElements || second >=nElements){
        throw out_of_range ("ArrayBigramFreqFunctions.cpp void swapElementsArrayBigramFreq invalid pos (>=nElements");
    }
    BigramFreq tmp = array[first];
    array[first] = array[second];
    array[second] = tmp;
    
}

void sortArrayBigramFreq(BigramFreq array[], int nElements) {
    // Ordena el array en orden descendente por frecuencia (mediante BubbleSort)
    // (Alfabetico en caso de igualdad)
    for (int i = 0; i < nElements - 1; i++) {
        for (int j = i + 1; j < nElements; j++) {
            if ((array[i].getFrequency() < array[j].getFrequency())||
                (array[i].getFrequency()==array[j].getFrequency()) &&
                (array[i].getBigram().getText() > array[j].getBigram().getText())) {
                swapElementsArrayBigramFreq(array, nElements, i, j);
            }
        }
    }
}


void toUpperArrayBigramFreq(BigramFreq array[], int nElements){
    for (int i = 0; i<nElements; i++){
        Bigram tmp = array[i].getBigram();
        tmp.toUpper();
        array[i].setBigram(tmp);
    }
}
