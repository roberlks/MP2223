/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file Language.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */



#include "Language.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>



using namespace std;
const string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";
const string Language::MAGIC_STRING_B="MP-LANGUAGE-B-1.0";

Language::Language(){
    _vectorBigramFreq = nullptr;
    _languageId = "unknown";
    _size=0;
  
    
}

Language::Language(int numberBigrams){
    
    _languageId = "unknown";
    _size = numberBigrams;
    _vectorBigramFreq = new BigramFreq[_size+1];
    
    if(numberBigrams<0){
        
        throw std::out_of_range("Out of Range");
    }
    
    for(int i=0; i<_size; i++){
        _vectorBigramFreq[i].setFrequency(0);
        _vectorBigramFreq[i].setBigram(Bigram());
        
    }
}
Language::Language(const Language& orig){
    
    _languageId=orig.getLanguageId();
    _size = orig.getSize();
    _vectorBigramFreq = new BigramFreq[_size];
    
    for(int i=0; i<_size; i++){
        _vectorBigramFreq[i] = orig.at(i);
    }
    
}

Language::~Language(){
    
    if(_size!=0){
        delete[] _vectorBigramFreq;
    }
    _vectorBigramFreq = nullptr;
    
    _size=0;
    _languageId = "unknown";
}


Language& Language::operator=(const Language& orig){
    
    if(_size != 0){
        delete[] _vectorBigramFreq;
    }
    _languageId = orig.getLanguageId();
    _size = orig.getSize();
    _vectorBigramFreq = new BigramFreq[_size];
    
    for(int i=0; i<_size; i++){
        _vectorBigramFreq[i].setBigram(orig.at(i).getBigram());
        _vectorBigramFreq[i].setFrequency(orig.at(i).getFrequency());
    }
    
    return *this;
}

const string& Language::getLanguageId() const{
    
    return _languageId;
    
}

void Language::setLanguageId(const string& id){
    
    _languageId = id;

}

BigramFreq& Language::at(int index){
    
    if(index < 0 || index >= _size){
        throw std::out_of_range("Out of Range");
    }
    
   
    return _vectorBigramFreq[index];
    
}

const BigramFreq& Language::at(int index)const{
    
    if(index < 0 || index >= _size){
        throw out_of_range("Out of Range");
    }
    
    
    return _vectorBigramFreq[index];
    
}

int Language::getSize() const{
    
    return _size;
    
}

int Language::findBigram(const Bigram& bigram) const{
    
    int loc=-1, i=0;
    bool sigue=true;
    
    while( i<_size && sigue){
        if(_vectorBigramFreq[i].getBigram().at(0) == bigram.at(0)){
            if (_vectorBigramFreq[i].getBigram().at(1) == bigram.at(1)){
                
            
                loc=i;
                sigue=false;
            }
        }
        i++;
    }
    
    return loc;
}

string Language::toString() const{
    
    string output= _languageId;
    output += "\n" + to_string(_size);
    
    for(int i=0; i<_size; i++){
        output += "\n"+_vectorBigramFreq[i].toString() ;
    }
    output +="\n";
    return output;
    
}

void Language::sort(){
    
    int pos_max = 0;
    for(int i=0; i<_size; i++){
        pos_max = i;
         for(int j=i+1; j<_size; j++){
               if(_vectorBigramFreq[j]>_vectorBigramFreq[pos_max]){
            pos_max = j;
        }
    }
        BigramFreq aux = _vectorBigramFreq[i];
    _vectorBigramFreq[i] = _vectorBigramFreq[pos_max];
    _vectorBigramFreq[pos_max] = aux;
    }
}

void Language::save(const char fileName[], char mode) const{
    ofstream os;
    if (mode == 't'){
        os.open(fileName);        
        if (!os) {
            throw ios_base::failure("Error opening output file");
        }
        os << MAGIC_STRING_T << endl;
        os << *this;
    }
    else if (mode == 'b'){
        os.open(fileName, ios::out|ios::binary);
        if (!os.is_open()) {
            throw ios_base::failure("Error opening output file");
        }
        os << MAGIC_STRING_B << endl << _languageId << endl << _size << endl;
        for (int i = 0; i< _size ; i++){
            _vectorBigramFreq[i].serialize(os);
        }
    }
    else{
        return;
    }
    
    if (!os){
        throw ios_base::failure("Error writting to output file");
    }
    os.close();

        
}
    
    
  
 
void Language::load(const char fileName[]){     
    ifstream is;
    is.open(fileName, ios::in|ios::binary);
    
    if (!is) {
        throw ios_base::failure("Error opening loader file");
    }
    
    string cad_mag;
    is >> cad_mag;
    
    if ((cad_mag != MAGIC_STRING_T)&&(cad_mag!= MAGIC_STRING_B)){
        cout << "MAG CAD: " << cad_mag << " != " << MAGIC_STRING_B << endl;
        throw invalid_argument("Invalid magic string");
    }
    
    if (cad_mag == MAGIC_STRING_T){
        is >> *this;
    }
    else {
        LeerInfoPrincpio(is);
        is.get();
        for (int i = 0; i<_size; i++){
            _vectorBigramFreq[i].deserialize(is); 
        }        
    }
    if (!is) {
        throw ios_base::failure("Error reading from file");
    }

    is.close();
    
}


void Language::append(const BigramFreq& bigramFreq){
    int pos = findBigram(bigramFreq.getBigram());
    if (pos == -1){ 
        
        BigramFreq* pointer = new BigramFreq [_size+1];
        
        
        for (int i = 0; i<this->_size; i++){
            pointer[i] = this->_vectorBigramFreq[i];
        }
        delete [] _vectorBigramFreq;
        
        
        _vectorBigramFreq = pointer;

        _vectorBigramFreq[_size] = bigramFreq;
        _size ++;
    }
    else{ 
        _vectorBigramFreq[pos].setFrequency(_vectorBigramFreq[pos].getFrequency()+bigramFreq.getFrequency());
    }
}

/*void Language::join(const Language& language){
    
    for(int i=0; i<language.getSize(); i++){
        append(language.at(i));
        
    }
    
    
}*/

double Language::getDistance(const Language& otherLanguage) const{
    
    if(getSize() == 0){
        throw invalid_argument("Objeto Language vacío");
    }
    
    double num=0, denom=getSize()*getSize();
    double aux=0;
    double distance;
    
    
    for(int i=0 ; i< getSize(); i++){
        
        if(otherLanguage.findBigram(at(i).getBigram()) == -1){
            
            aux = getSize();
        }
        
        else{ 
            
            aux = otherLanguage.findBigram(at(i).getBigram());
            
        }
        
       
        num += abs(i - aux);
        
        
    }
    
    distance = num / denom;
    
    return distance;
}


BigramFreq& Language::operator[](int index) {
    if (index < 0 || index >= _size)
        throw std::out_of_range("Invalid index");

    return _vectorBigramFreq[index];
}

const BigramFreq& Language::operator[](int index) const {
    if (index < 0 || index >= _size)
        throw std::out_of_range("Invalid index");

    return _vectorBigramFreq[index];
}

Language Language::operator+=(Language language) {
    for (int i = 0; i < language._size; ++i) {
        int index = findBigram(language._vectorBigramFreq[i].getBigram());
        if (index != -1) {
            _vectorBigramFreq[index].setFrequency(_vectorBigramFreq[index].getFrequency() + language._vectorBigramFreq[i].getFrequency());
        } else {
            append(language._vectorBigramFreq[i]);
        }
    }

    return *this;
}
void Language::LeerInfoPrincpio(istream& is){
 
    string id;
    is >> id;
    this->setLanguageId(id);
    int size;
    is >> size;
    delete [] _vectorBigramFreq;
    _vectorBigramFreq = new BigramFreq[size];
    _size = size;    
}

ostream& operator<<(ostream& os, const Language& language) {
    os << language.toString();
    return os;
}

istream& operator>>(istream& is, Language& language) {

    language.LeerInfoPrincpio(is);
    

    for (int i = 0; i < language.getSize(); ++i) {
        BigramFreq bigramFreq;
        is >> bigramFreq;
        language.at(i)=bigramFreq;
    }

    return is;
}