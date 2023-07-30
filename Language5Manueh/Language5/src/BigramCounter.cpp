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

#include <fstream>
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

// Métodos privados: Operadores

BigramCounter::BigramCounter(std::string validChars){
    _validCharacters = validChars;
    int size = _validCharacters.length();
    
    _frequency = new int*[size];
    
    for (int i = 0; i < size; i++) {
        _frequency[i] = new int[size];
        for (int j = 0; j < size; j++) {
            _frequency[i][j] = 0;
        }
    }
}

BigramCounter::BigramCounter(const BigramCounter& orig) {
    int size = orig.getSize();
    _validCharacters = orig._validCharacters;
    _frequency = new int*[size];
    for (int i = 0; i < size; i++) {
        _frequency[i] = new int[size];
        for (int j = 0; j < size; j++) {
            _frequency[i][j] = orig(i, j);
        }
    }
}

BigramCounter::~BigramCounter() {
    int size = getSize();
    for (int i = 0; i < size; i++) {
        delete[] _frequency[i];
    }
    delete[] _frequency;
}

int BigramCounter::getSize()const {
    return _validCharacters.length();
}

int BigramCounter::getNumberActiveBigrams() {
    int count = 0;
    int size = getSize();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (_frequency[i][j] > 0) {
                count++;
            }
        }
    }
    return count;
}

bool BigramCounter::setFrequency(Bigram bigram, int frequency) {
    char first = bigram.at(0);
    char second = bigram.at(1);
    int row = _validCharacters.find(first);
    int column = _validCharacters.find(second);
    if (row != std::string::npos && column != std::string::npos) {
        _frequency[row][column] = frequency;
        return true;
    }
    return false;
}

void BigramCounter::increaseFrequency(Bigram bigram, int frequency) {
    if (frequency == 0) {
        frequency = 1;
    }
    char first = bigram.at(0);
    char second = bigram.at(1);
    int row = _validCharacters.find(first);
    int column = _validCharacters.find(second);
    if (row == std::string::npos || column == std::string::npos) {
        throw std::invalid_argument("Invalid bigram");
    }
    _frequency[row][column] += frequency;
}

BigramCounter& BigramCounter::operator=(const BigramCounter& orig) {
    if (this != &orig) {
        int size = orig.getSize();
        _validCharacters = orig._validCharacters;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                _frequency[i][j] = orig(i, j);
            }
        }
    }
    return *this;
}

BigramCounter& BigramCounter::operator+=(const BigramCounter& rhs) {
    int size = getSize();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            _frequency[i][j] += rhs(i, j);
        }
    }
    return *this;
}
void BigramCounter::calculateFrequencies(const char* nombreArchivo) {
    ifstream archivo;
    archivo.open(nombreArchivo);
    if (!archivo.is_open()) {
        throw ios_base::failure("Error opening file");
    }

    int tamano = getSize();
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            (*this)(i, j) = 0;
        }
    }

    string linea;
    while (getline(archivo, linea)) {
        int i = 1;
        while (i < linea.length()) {
            char primerCaracter = tolower(linea[i - 1]);
            int primeraPosicion = _validCharacters.find(primerCaracter);

            if (primeraPosicion != string::npos) {
                
                char segundoCaracter = tolower(linea[i]);
                int segundaPosicion = _validCharacters.find(segundoCaracter);
                if (segundaPosicion != string::npos) {
                    (*this)(primeraPosicion, segundaPosicion)++;
                
                } else {
                    i++;
                }
            }
            i++;
        }
    }

    archivo.close();
}

Language BigramCounter::toLanguage() const {
    Language lenguaje;
    int tamano = getSize();    
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            int frecuencia = (*this)(i, j);
            if (frecuencia > 0) {
                
                Bigram bigrama(_validCharacters.at(i), _validCharacters.at(j));
                BigramFreq bf;
                bf.setBigram(bigrama);
                bf.setFrequency(frecuencia);
                lenguaje.append(bf);
            }
        }
    }
    lenguaje.sort();
    return lenguaje;
}


const int& BigramCounter::operator()(int row, int column) const {
    return this->_frequency[row][column];
}
int& BigramCounter::operator()(int row, int column){
    return this->_frequency[row][column];
}