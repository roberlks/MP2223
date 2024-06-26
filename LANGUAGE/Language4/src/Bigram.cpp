
/* 
 * File:   Bigram.cpp
 * Author: roberlks222
 * 
 * Created on 8 de marzo de 2023, 18:25
 */

#include <iostream>
#include <string>
#include <cctype>
#include <cstring> 

#include "Bigram.h"

using namespace std;
const char CNULL = '\0';

Bigram::Bigram(const string& text) : _text{'_', '_', CNULL} {
    if (text.length() == 2){
        this->_text[0] = text.at(0);
        this->_text[1] = text.at(1);
        this->_text[2] = CNULL;
    }
}

Bigram::Bigram(char first, char second){
        this->_text[0] = first;
        this->_text[1] = second;
        this->_text[2] = CNULL;
}

Bigram::Bigram(const char text[]){
    if(strlen(text) == 2){
        this->_text[0] = text[0];
        this->_text[1] = text[1];
        this->_text[2] = CNULL;
    }
    else{ 
        this->_text[0] = '_';
        this->_text[1] = '_';
        this->_text[2] = CNULL;
    }
}
string Bigram::getText() const{
    return (toString());
}

string Bigram::toString()const{
    return this->_text; 
}

const char& Bigram::at(int index) const{
    
    if(index<0 || index >1)
        throw out_of_range("Bigram.cpp, Bigram::at(int index)const\n\t-Error, indice no valido");
    else
        return _text[index];
}

char& Bigram::at(int index){
    
    if(index<0 || index >1)
        throw out_of_range("Bigram.cpp, Bigram::at(int index)\n\t-Error, indice no valido");
    else
        return _text[index];
}
void Bigram::toUpper(){
    _text[0] = toupper(_text[0]);
    _text[1] = toupper(_text[1]);
}

bool isValidCharacter (char character, const string& validCharacters){
    
    //Si la posicion de buscar el caracter en la string no es valida (es npos)
    return (validCharacters.find(character) != string::npos);
}

