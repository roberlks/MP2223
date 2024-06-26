/* 
 * File:   Language.cpp
 * Author: roberlks222
 * 
 * Created on 30 de mayo de 2023, 15:50
 */
#include <string>
#include <fstream>
#include <iostream> 

#include "Language.h"

using namespace std;

const string DEF_ID = "unknown";

const string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";
const string Language::MAGIC_STRING_B="MP-LANGUAGE-B-1.0";

Language::Language(){
    this->_languageId = DEF_ID;
    this->_size = 0;
    this->_vectorBigramFreq = nullptr;
}
Language::Language(int numberBigrams){

    if(numberBigrams < 0){
        throw out_of_range("Class:Language\nConstructor:Language(int numberBigrams)\n\t Must be  greater than 0 ");
    }
    this->_languageId = DEF_ID;
    this->_size = numberBigrams;
    this->_vectorBigramFreq = new BigramFreq[_size];

}

Language::Language(const Language& orig) {
    Copy(orig);
}
Language::~Language() {
    delete[] _vectorBigramFreq;
}

Language& Language::operator=(const Language& orig){
    if (this == &orig) {
        // Verificar si el objeto es el mismo
        return *this;
    }
    
    delete[] _vectorBigramFreq;
    
    Copy(orig);
    return *this;
    
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

    if(index >= this->_size || index < 0){
        throw out_of_range("Class:Language\n BigramFreq& at(int index)\n\tMust be  greater than 0 and less than " + this->_size);
    }
    return this->_vectorBigramFreq[index];
    
}

int Language::getSize()const{
    return this->_size;
}


double Language::getDistance(const Language& otherLanguage) const{
    if ((this->_size == 0)){
        throw (std::invalid_argument("Class:Language\ngetDistance(const Language& otherLanguage)\n\tThis language is empty"));
    }
    double suma = 0.0;
    for (int i = 0; i<this->_size; i++){
        int rank2 = otherLanguage.findBigram(this->_vectorBigramFreq[i].getBigram());
        if (rank2==-1){rank2=this->_size;}
        suma += abs(i-rank2);
    } 
    double res = (suma/((this->_size)*(this->_size)));
    return res;    

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
    

    string cad = this->_languageId;
    cad += "\n";
    cad += to_string(this->_size);
    cad += "\n";
    for (int i = 0; i < this->_size; i++){
        cad += _vectorBigramFreq[i].toString();
        cad += "\n";
    }
    return cad;

}

void Language::sort(){
    
    
    //Sorts the array in descending order by frequency (BubbleSort)
    //Alphabetically in case of equality

    for (int i = 0; i < this->_size - 1; i++) {
        for (int j = i + 1; j < this->_size; j++) {
            if (this->_vectorBigramFreq[i]<this->_vectorBigramFreq[j]) {
                    BigramFreq tmp = this->_vectorBigramFreq[i];
                    this->_vectorBigramFreq[i] = this->_vectorBigramFreq[j];    
                    this->_vectorBigramFreq[j] = tmp;
            }
        }
    }
}

void Language::save(const char fileName[], char mode)  const {
    ofstream outFile;

    if (mode == 't'){
        outFile.open(fileName);
        if (!outFile) {
            throw ios_base::failure("Error opening output file");
        }
        outFile << this->MAGIC_STRING_T << endl;
        outFile << *this;
    }
    else if (mode == 'b'){
        outFile.open(fileName, ios::out|ios::binary);
        if (!outFile.is_open()) {
            throw ios_base::failure("Error opening output file");
        }
        outFile << this->MAGIC_STRING_B << endl;
        outFile << this->_languageId << endl << this->_size << endl;
        for (int i = 0; i< this->_size ; i++){
            this->_vectorBigramFreq[i].serialize(outFile);
        }
    }
    else
        return;

    if (!outFile) {
        throw ios_base::failure("Error writting to output file");
    }
    
    outFile.close();
}

void Language::updateSize (const int nsize){
    
    if (nsize < this->_size){
        throw out_of_range("Class: Language. Method: updateSize: nsize should be >= _size");
    }
    if (nsize == this->_size) return;
    
    BigramFreq* tmpPtr = new BigramFreq [nsize];
    
    for (int i = 0; i<this->_size; i++){
        tmpPtr[i] = this->_vectorBigramFreq[i];
    }
    delete [] _vectorBigramFreq;
    _vectorBigramFreq = tmpPtr;
    _size = nsize;
   
    
}

void Language::load(const char fileName[]) {

    ifstream inFile;
    inFile.open(fileName, ios::in|ios::binary);
    
    if (!inFile) {
        throw ios_base::failure("Error opening file");
    }

    string magicString;
    inFile >> magicString;
    
    if (magicString != MAGIC_STRING_T) {
        if (magicString != MAGIC_STRING_B){
            throw invalid_argument("Invalid magic string");
        }        
    }
    
    if (magicString == MAGIC_STRING_T){
        inFile >> *this;
    }
    else{
        readFirstFields(inFile);
        inFile.get(); //Jump on \n
        for (int i = 0; i<_size; i++){
            this->_vectorBigramFreq[i].deserialize(inFile); 
        }
    }
    

    if (!inFile) {
        throw ios_base::failure("Error writing to file");
    }

    inFile.close();
}

void Language::append(const BigramFreq& bigramFreq){
    int pos = findBigram(bigramFreq.getBigram());
    if (pos == -1){ //Add bigramFreq at the last position
        updateSize(this->_size+1); //updateSize(_size+1)
        _vectorBigramFreq[this->_size-1] = bigramFreq;
    }
    else{ //Frequency ++
        _vectorBigramFreq[pos].setFrequency(_vectorBigramFreq[pos].getFrequency()+bigramFreq.getFrequency());
    }
}

const BigramFreq& Language::operator[](const int index) const{
    return this->_vectorBigramFreq[index];
}
BigramFreq& Language::operator[](const int index){
    return this->_vectorBigramFreq[index];
}

Language& Language::operator+=(const Language& language){
    for (int i = 0; i < language.getSize(); i++){
        append(language.at(i));
    }
    return *this;
}

void Language::Copy(const Language& orig){
    _languageId = orig.getLanguageId();
    _size = orig.getSize();
    
    // Creates a new BigramFrew array
    _vectorBigramFreq = new BigramFreq[_size];
    
    //Copy element by element
    for (int i = 0; i < _size; i++) {
        _vectorBigramFreq[i] = orig.at(i);
    }
}

void Language::readFirstFields(istream& is){
    string id;
    is >> id;
    this->setLanguageId(id);
    
    int size;
    is >> size;  
    if (size <0){
        throw out_of_range("Size must be positive");
    }

    // Clean existing memory.
    delete[] this->_vectorBigramFreq;
    
    // Assign new vector size
    this->_size = size;
    
    // Create a new array of BigramFreqs
    this->_vectorBigramFreq = new BigramFreq[this->_size];
}

ostream& operator<<(ostream& os, const Language& language){
    os << language.toString();
    return os;
}
istream& operator>>(istream& is, Language& language){
    
    language.readFirstFields(is);
    for (int i = 0; i < language.getSize(); i++) {
        BigramFreq bf;
        is >> bf;
        language.at(i) = bf;
    }
    return is;
    
}