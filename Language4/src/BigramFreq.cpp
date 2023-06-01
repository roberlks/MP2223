/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   BigramFreq.cpp
 * Author: roberlks222
 * 
 * Created on 8 de marzo de 2023, 18:40
 */

#include <string>

#include "BigramFreq.h"

using namespace std;

BigramFreq::BigramFreq(){
    this->_bigram = Bigram();
    this->_frequency = 0;
}

const Bigram& BigramFreq::getBigram()const{
    return this->_bigram;
}

int BigramFreq::getFrequency() const {
    return this->_frequency;
}

void BigramFreq::setBigram (const Bigram& bigram){
    this->_bigram = bigram;
}

void BigramFreq::setFrequency (int frequency){
    if(frequency <0){
        throw out_of_range("BigramFreq.cpp void BigramFreq::setFrequency invalid frequency (Must be positive)");
    }
    else{
        this->_frequency = frequency;
    }
}

string BigramFreq::toString()const{
    string cad = this->_bigram.toString();
    cad += ' ' + to_string(this->_frequency);
    return cad;
}
