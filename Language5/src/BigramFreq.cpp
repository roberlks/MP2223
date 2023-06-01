/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file BigramFreq.cpp
 * @author Roberto González Lugo
 * 
 * Created on 31 May 2023, 11:56
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

void BigramFreq::serialize(ostream& outputStream){
    this->_bigram.serialize(outputStream);
    outputStream.write(reinterpret_cast<const char*>(&_frequency), sizeof(int));
}
void BigramFreq::deserialize(istream& inputStream) {
    this->_bigram.deserialize(inputStream);
    inputStream.read(reinterpret_cast<char*>(&_frequency), sizeof(int));
}

ostream& operator<<(ostream& os, const BigramFreq& bigramFreq){
    os << bigramFreq.toString();
    return os;
}

istream& operator>>(istream& is, BigramFreq& bigramFreq){
    Bigram tmpBig;
    is>>tmpBig;
    bigramFreq.setBigram(tmpBig);
    int temp;
    is >> temp;
    bigramFreq.setFrequency(temp);
    return is;
}

bool operator>(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    
    return ((bigramFreq1.getFrequency() > bigramFreq2.getFrequency()) ||
            ((bigramFreq1.getFrequency() == bigramFreq2.getFrequency()) && 
            (bigramFreq1.getBigram().getText() < bigramFreq2.getBigram().getText())));
}

bool operator<(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    return bigramFreq2>bigramFreq1;
}
bool operator==(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    return (!(bigramFreq1>bigramFreq2) && !(bigramFreq1<bigramFreq2));
}
bool operator!=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    return !(bigramFreq1==bigramFreq2);
}
bool operator<=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    return !(bigramFreq1>bigramFreq2);
}

bool operator >=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    return !(bigramFreq1<bigramFreq2);
}

