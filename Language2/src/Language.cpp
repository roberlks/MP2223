/* 
 * File:   Language.cpp
 * Author: roberlks222
 * 
 * Created on 28 de marzo de 2023, 15:50
 */

#include <string>
#include <fstream>
#include <iostream> 
#include "Language.h"



using namespace std;
const string DEF_ID = "unknown";
const string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";
Language::Language(){
    this->_languageId = DEF_ID;
    this->_size = 0;
}
Language::Language(int numberBigrams){

    if(numberBigrams > DIM_VECTOR_BIGRAM_FREQ || numberBigrams < 0){
        throw out_of_range("Class:Language\nConstructor:Language(int numberBigrams)\n\t Must be  greater than 0 and less than " + DIM_VECTOR_BIGRAM_FREQ);
    }
    this->_languageId = DEF_ID;
    this->_size = numberBigrams;

}

const string& Language::getLanguageId() const{
    return this->_languageId;
}

void Language::setLanguageId(const std::string& id){
    this->_languageId = id;
}

const BigramFreq& Language::at(int index) const{

    if(index >= this->_size || index < 0){
        throw out_of_range("Class:Language\nconst BigramFreq& at(int index) const\n\tMust be  greater than 0 and less than " + this->_size);
    }
    return this->_vectorBigramFreq[index];
    
}

BigramFreq& Language::at(int index){

    if(index > this->_size || index < 0){
        throw out_of_range("Class:Language\n BigramFreq& at(int index)\n\tMust be  greater than 0 and less than " + this->_size);
    }
    return this->_vectorBigramFreq[index];
    
}

int Language::getSize()const{
    return this->_size;
}

int Language::findBigram(const Bigram& bigram)const{
    bool not_found = true;
    int i = 0; //Counter
    int pos = -1; //Default case is not found
    while (not_found && i < this->_size){
        if (this->_vectorBigramFreq[i].getBigram().getText() == bigram.getText()){
            pos = i;
            not_found = false;
        }
        else
            i++;
    }
    return pos;
}

string Language::toString() const{
    

    string cad =to_string(this->_size);
    cad += "\n";
    for (int i = 0; i < this->_size; i++){
        cad += _vectorBigramFreq[i].toString();
        cad += "\n";
    }
    return cad;

}
void Language::sort(){
    
    

    // Ordena el array en orden descendente por frecuencia (mediante BubbleSort)
    // (Alfabetico en caso de igualdad)
    for (int i = 0; i < this->_size - 1; i++) {
        for (int j = i + 1; j < this->_size; j++) {
            if ((this->_vectorBigramFreq[i].getFrequency() < this->_vectorBigramFreq[j].getFrequency())||
                (this->_vectorBigramFreq[i].getFrequency()==this->_vectorBigramFreq[j].getFrequency()) &&
                (this->_vectorBigramFreq[i].getBigram().getText() > this->_vectorBigramFreq[j].getBigram().getText())) {
                    BigramFreq tmp = this->_vectorBigramFreq[i];
                    this->_vectorBigramFreq[i] = this->_vectorBigramFreq[j];    
                    this->_vectorBigramFreq[j] = tmp;
            }
        }
    }
}

void Language::save(const char fileName[]) const {
    ofstream outFile;
    outFile.open(fileName);
    if (!outFile) {
        throw ios_base::failure("Error opening output file");
    }
    outFile << this->MAGIC_STRING_T << endl << this->_languageId << endl;
    outFile << toString();

    if (!outFile) {
        throw ios_base::failure("Error writting to output file");
    }

    outFile.close();
}

void Language::load(const char fileName[]) {

    ifstream inFile;
    inFile.open(fileName);
    
    if (!inFile) {
        throw ios_base::failure("Error opening file");
    }

    string magicString;
    inFile >> magicString;
    
    if (magicString != MAGIC_STRING_T) {
        throw invalid_argument("Invalid magic string");
    }
    
    string id;
    inFile >> id;
    setLanguageId(id);
    
    int size;
    inFile >> size;

    if (size > DIM_VECTOR_BIGRAM_FREQ) {
        throw out_of_range("Number of bigrams exceeds maximum capacity");
    }

    this->_size = size;

    for (int i = 0; i < size; i++) {
        BigramFreq bf;
        string bigram_text = "";
        int bigram_freq = 0;
        inFile >> bigram_text;
        inFile >> bigram_freq;
        bf.setBigram(Bigram(bigram_text));
        bf.setFrequency(bigram_freq);
        
        this->_vectorBigramFreq[i] = bf;
    }

    if (!inFile) {
        throw ios_base::failure("Error reading from file");
    }

    inFile.close();
}

void Language::append(const BigramFreq& bigramFreq){
    int pos = findBigram(bigramFreq.getBigram());
    if (pos == -1){ //Add bigramFreq at the last position
        if(_size == DIM_VECTOR_BIGRAM_FREQ){
            throw out_of_range("\nClass Language. Method append. \n\tCannot add any more bigrams.");
        }
        _vectorBigramFreq[_size] = bigramFreq;
        _size ++;
    }
    else{ //Frequency ++
        _vectorBigramFreq[pos].setFrequency(_vectorBigramFreq[pos].getFrequency()+bigramFreq.getFrequency());
    }
}

void Language::join(const Language& language){
    for (int i = 0; i < language.getSize(); i++){
        append(language.at(i));
    }
}
