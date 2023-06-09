/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file BigramCounter.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 12 February 2023, 11:00
 */

#include <iostream>
#include<string>

#include "BigramCounter.h"


using namespace std;
/**
 * DEFAULT_VALID_CHARACTERS is a c-string that contains the set of characters
 * that will be considered as part of a word (valid chars). 
 * The characters not in the c-string will be considered as separator of words.
 * The constructor of the class BigramCounter uses this c-string as a 
 * default parameter. It is possible to use a different c-string if that
 * constructor is used with a different c-string
 */
const char* const BigramCounter::DEFAULT_VALID_CHARACTERS="abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";


BigramCounter::BigramCounter(const string validChars){
    const int n = validChars.length();
    this->_frequency = new int* [n];

    for (int i = 0; i<n; i++){
        this->_frequency[i] = new int[n];
        for (int j=0; j<n;j++)
            this->_frequency[i][j] = 0;
    }
    this->_validCharacters = validChars;
}

BigramCounter::BigramCounter(const BigramCounter& orig){
    copy(orig);
}

BigramCounter::~BigramCounter() {
    this->deallocate();
}

void BigramCounter::deallocate (){
    if (_frequency==nullptr){
        return;
    } 
    for (int i = 0; i < getSize(); i++) {
        delete[] _frequency[i];
    }
    delete[] _frequency;
}

void BigramCounter::copy(const BigramCounter& orig) {



    // Copy member fields
    this->_validCharacters = orig.getValidChar();
    
    int n = orig.getSize();

    // Reserve memory for the new matrix
    this->_frequency = new int*[n];
    for (int i = 0; i < n; i++) {
        this->_frequency[i] = new int[n];
    }

    // Fill matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            (*this)(i, j) = orig(i, j);
        }
        
    }
}


string BigramCounter::getValidChar()const {
    return this->_validCharacters;
}

int BigramCounter::getSize() const{
    return this->_validCharacters.length();
}

int BigramCounter::getNumberActiveBigrams() const{
    int counter = 0;
    for (int i = 0; i < getSize(); i ++){
        for (int j = 0; j < getSize(); j++){
            if ((*this)(i, j) > 0)
                    counter++;
        }
    }
    return counter;
}

bool BigramCounter::setFrequency(const Bigram& bigram, int frequency){
    int row = CharToPos(bigram.at(0));
    int column = CharToPos(bigram.at(1));
    
    if (row  == string::npos || column == string::npos)
        return false;
    (*this)(row, column) = frequency;
    return true;
}

void BigramCounter::increaseFrequency(const Bigram& bigram, int frequency){
    int row = CharToPos(bigram.at(0));
    int column = CharToPos(bigram.at(1));
    if (row  == string::npos || column == string::npos)
        throw invalid_argument("Class BigraMCounter.cpp, method increaseFrequency. Bigram contains an invalid character, therefore does not exist");
    (frequency == 0)?frequency = 1:frequency; 
    (*this)(row, column) += frequency;
}

BigramCounter& BigramCounter::operator=(const BigramCounter& orig){
    if (&orig == this){
        return *this;
    }
    deallocate();
    copy(orig);
    return *this;
}

BigramCounter& BigramCounter::operator+=(const BigramCounter& rhs){
    int size = getSize();
    if (this->_validCharacters != rhs.getValidChar())
        return *this;
    
    //We suppose the structure of the matrix is the same, (_validChar == rhs._validChar)
    for (int i = 0; i < size; i++)
        for (int j=0; j<size; j++)
            (*this)(i,j) += rhs(i,j);
    return *this;   
}

void BigramCounter::calculateFrequencies(const char* fileName) {
    
    // Open input file
    ifstream file(fileName);
    if (!file.is_open()) {
        throw ios_base::failure("Unable to open file");
    }
    
    //Reset all freqs to 0
    int n = getSize();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            (*this)(i, j) = 0;
        }
    }
    
    

    // Read line by line and calculate bigram frequencies
    std::string line;
    while (getline(file, line)) {
        
        
        // Process each pair of chars from this line
        int i = 1;
        while (i < line.length()){
            
            char firstChar = tolower(line[i-1]);
            int firstPos = CharToPos(firstChar);

            if (firstPos != string::npos){
                char secondChar = tolower(line[i]); 
                int secondPos = CharToPos(secondChar);
                if (secondPos != string::npos){
                    (*this)(firstPos, secondPos) ++;
                }
                else
                    i++;
            }
            i++;
        }
    }

    // Close input file
    file.close();
}

Language BigramCounter::toLanguage() const{
    Language lg;
    int n = getSize();
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            int freq = (*this)(i,j);
            if (freq > 0){
                Bigram bg(PosToChar(i), PosToChar(j));
                BigramFreq bf;
                bf.setBigram(bg);
                bf.setFrequency(freq);
                lg.append(bf);
            }
        }
    }
    lg.sort();
    return lg;
}




int BigramCounter::CharToPos(char c)const {
    return this->_validCharacters.find(c);
}
char BigramCounter::PosToChar(int n)const {
    return this->_validCharacters.at(n);
}

const int& BigramCounter::operator()(int row, int column) const {
    return this->_frequency[row][column];
}
int& BigramCounter::operator()(int row, int column){
    return this->_frequency[row][column];
}


