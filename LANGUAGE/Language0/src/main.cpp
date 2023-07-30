
/* 
 * File:   main.cpp
 * Author: roberlks222
 *
 * Created on 4 de marzo de 2023, 0:19
 */


/**
 * This program reads a text (without spaces) with a undefined number of 
 * characters and a text with two characters (bigram). It finds the bigrams 
 * contained in the first text, storing them in an array of Bigram. 
 * After that, the bigrams of the array are shown in the standard output. 
 * Then it converts to uppercase the bigrams in the array that are equals to the 
 * bigram of the second text. Finally the bigrams of the array are shown again 
 * in the standard output. 
 * Running example:
 * > language0 < data/SimpleText.txt
 */

#include <cstdlib>
#include<iostream>
#include <string>
#include <cctype>

#include "Bigram.h"

using namespace std;

void PrintBigram(Bigram bigrama[], int total_utilizados){
    
    cout << total_utilizados << endl;
    
    for (int i=0; i<total_utilizados; i++){
        cout <<  bigrama[i].toString() << endl;
    }
}


int main() {
    
    // This string contains the list of characters that are considered as
    // valid within a word. The rest of characters are considered as
    // separators
    const string validCharacters = "abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

    
    string cad1, cad2;    
    // Read a text

    cin >> cad1;

    int const MAX_SIZE = cad1.length()-1;
    // Read a bigram (tex with two characters)
 
    cin >> cad2;
    Bigram looking_brigram (tolower(cad2.at(0)), tolower(cad2.at(1)));
    

    // Find the bigrams in text and put them in an array of Bigrams

    Bigram bigrams[MAX_SIZE];
    int total_utilizados = 0;
    
    for (int i = 0; i+1<cad1.length(); i++){
        
        char a = tolower(cad1.at(i));
        char b = tolower(cad1.at(i+1));
        
        if ((isValidCharacter(a, validCharacters)) && (isValidCharacter(b, validCharacters))){
            bigrams[total_utilizados] = Bigram(a,b);
            total_utilizados ++;
        }
        
    }
    
    // Show the bigrams stored in the array
    PrintBigram(bigrams, total_utilizados);
    cout << endl;
    
    //Look for the bigrams in the arrray that are equal to input bigram and convert to uppercase
    for (int i = 0; i < total_utilizados; i++){
        if (bigrams[i].getText() == looking_brigram.getText()){
            toUpper(bigrams[i]);
        }
    }
    
    // Show again the bigrams stored in the array
    
    PrintBigram(bigrams, total_utilizados);
    

    return 0;
}

