
/* 
 * File:   Bigram.cpp
 * Author: roberlks222
 * 
 * Created on 4 de marzo de 2023, 0:22
 */

#include <iostream>
#include <string>
#include <cctype>

#include "Bigram.h"

using namespace std;

Bigram::Bigram(const string& text){
    
    if(text.length() != 2){
    
        this->_text = "__";
    
    }
    else{
        
        this->_text = text;
    
    }
    
}

Bigram::Bigram(char first, char second){
    this->_text = first;
    this->_text.push_back(second);
}

string Bigram::getText() const{
    return this->_text;
}

string Bigram::toString()const{
    
    return this->_text;
}

const char& Bigram::at(int index) const{
    
    if(index<0 || index >1)
        throw out_of_range("Bigram.cpp, Bigram::at(int index)const\n\t-Error, indice no valido");
    
    return _text.at(index);
}

char& Bigram::at(int index){
    
    if(index<0 || index >1)
        throw out_of_range("Bigram.cpp, Bigram::at(int index)\n\t-Error, indice no valido");
    
    return _text.at(index);
}

bool isValidCharacter (char character, const string& validCharacters){
    
    //Si la posicion de buscar el caracter en la string no es valida (es npos)
    return (validCharacters.find(character) != string::npos);
}

void toUpper (Bigram &bigram){
    
    for (int i = 0; i < 2; i++)
        bigram.at(i) = toupper(bigram.at(i));
    
}
