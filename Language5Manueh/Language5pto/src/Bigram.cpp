
#include <Bigram.h>
#include <string>
#include <cctype>
#include <fstream>


Bigram::Bigram(const std::string& text){
   
    if(text.length() == 2){
        _text[0]=text.at(0);
        _text[1]=text.at(1);
        _text[2]='\0';
    }
    
    else{
        _text[0]= '_';
        _text[1]= '_';
        _text[2]= '\0';
        std::cerr<<"Bigrama no apto"<<std::endl;
        exit(1);
    }
    
}

Bigram::Bigram(char first, char second){
        _text[0]= first;
        _text[1]= second;
        _text[2]= '\0';
    
}
    
Bigram::Bigram(const char text[]){
    if(text[2] != '\0'){
        _text[0]= '_';
        _text[1]= '_';
        _text[2]= '\0';
    }
    else{
        _text[0]= text[0];
        _text[1]= text[1];
        _text[2]= text[2];
    }
}

std::string Bigram::getText() const {
    
    std::string _bigram = "__";
    
    _bigram.at(0) = _text[0];
    _bigram.at(1) = _text[1];
    
    
    
    return _bigram;
    
}  


std::string Bigram::toString() const{
    
    std::string _bigram = "__";
    
    _bigram.at(0) = _text[0];
    _bigram.at(1) = _text[1];
    
    
    
    return _bigram;
    
}

const char& Bigram::at(int index) const{
    
    if(index != 0 && index !=1){
        throw std::out_of_range("Out of Range");
    }
    else{
        return _text[index];
    }
            
}

char& Bigram::at(int index){
    
    if(index != 0 && index !=1){
        throw std::out_of_range("Out of Range");
    }
    else{
        return _text[index];
    }
              
}


bool isValidCharacter(char character, const std::string& validCharacters){
    
    bool aparece=false;
    int i=0;
    while(i < validCharacters.length() && !aparece){
        
        if(validCharacters.at(i) == character){
            aparece=true;
        }
        
        i++;
    }
    
    return aparece;
    
    
}

void Bigram::toUpper(){
    
    _text[0]= toupper(_text[0]);
    _text[1]= toupper(_text[1]);
         
}


// Nueva parte del Language 5


// Funciones públicas serialize y deserialize

void Bigram::serialize(std::ostream& outputStream){
    
    outputStream.write(_text, sizeof((char)*2));
    
}

void Bigram::deserialize(std::istream& inputStream){
    
    inputStream.read(_text, sizeof((char)*2));
    
}



// OPERADORES

std::ostream Bigram::operator<<(std::ostream os, Bigram bigram){
    
    os << bigram.getText();
    
    return os;
    
}

std::istream Bigram::operator>>(std::istream is, Bigram bigram){
    
    char prim,sec;
    
    is >> prim >> sec;
    
    bigram = Bigram(prim,sec);
    
    return is;
}
