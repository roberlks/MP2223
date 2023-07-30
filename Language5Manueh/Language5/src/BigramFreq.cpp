
#include "BigramFreq.h"
#include <string>
#include <cctype>

BigramFreq::BigramFreq(){
    
    Bigram bg('_','_');
    _bigram = bg;
    _frequency = 0;
    
}

const Bigram& BigramFreq::getBigram() const{
    
    return _bigram;
}

int BigramFreq::getFrequency()const{
    
    return _frequency;
}

void BigramFreq::setBigram(const Bigram& bigram){
    
    _bigram = bigram;
}

void BigramFreq::setFrequency(int frequency){
    
    if(frequency < 0){
        throw std::out_of_range("Out of range");
    }
    _frequency = frequency;
}

std::string BigramFreq::toString() const{
    
    return _bigram.toString() + " " + std::to_string(_frequency);
}

void BigramFreq::serialize(std::ostream& outputStream){
    _bigram.serialize(outputStream);
    outputStream.write(reinterpret_cast<const char*>(&_frequency), sizeof(int));
}

void BigramFreq::deserialize(std::istream& inputStream){
    _bigram.deserialize(inputStream);
    inputStream.read(reinterpret_cast<char*>(&_frequency), sizeof(int));

}

std::ostream& operator<<(std::ostream& os, const BigramFreq& bigramFreq) {
    os << bigramFreq.getBigram().toString() << " " << bigramFreq.getFrequency();
    return os;
}

std::istream& operator>>(std::istream& is, BigramFreq& bigramFreq) {
    
    std::string text;
    int frequency;
    is >> text;
    is >> frequency;
    Bigram mibig(text);
    bigramFreq.setBigram(mibig);
    bigramFreq.setFrequency(frequency);
    return is; 
}

bool operator>(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2) {
    if (bigramFreq1.getFrequency() > bigramFreq2.getFrequency()) {
        return true;
    } else if (bigramFreq1.getFrequency() == bigramFreq2.getFrequency()) {
        return bigramFreq1.getBigram().getText() < bigramFreq2.getBigram().getText();
    } else {
        return false;
    }
}

bool operator<(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2) {
    return (bigramFreq2>bigramFreq1);
}

bool operator==(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2) {
    return (!(bigramFreq1>bigramFreq2) && !(bigramFreq1<bigramFreq2));
}

bool operator!=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2) {
    return !(bigramFreq1 == bigramFreq2);
}

bool operator<=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2) {
    return (bigramFreq1 < bigramFreq2) || (bigramFreq1 == bigramFreq2);
}

bool operator>=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2) {
    return (bigramFreq1 > bigramFreq2) || (bigramFreq1 == bigramFreq2);
}