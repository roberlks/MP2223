
/* 
 * File:   main.cpp
 * Author: roberlks222
 *
 * Created on 8 de marzo de 2023, 18:25
 */


/**
 * This program reads from the stardard input, an integer n (number of elements) 
 * and a list of n pairs bigram-frequency. The pairs are stored in an array, 
 * and then it is sorted in decreasing order of frequency. After that, 
 * all the bigrams are changed to uppercase. The sorted array is finally shown 
 * in the stardard output. 
 * Running example:
 * > language1 < data/miniquijotebigrams.txt 
 */

#include <cstdlib>
#include<iostream>
#include <string>
#include <cctype>

#include "Bigram.h"
#include "BigramFreq.h"
#include "ArrayBigramFreqFunctions.h"

using namespace std;

int main() {
    
    const int MAX_ARRAY_ELEMENTS = 1000;
    // This string contains the list of characters that are considered as
    // valid within a word. The rest of characters are considered as
    // separators
    const string validCharacters = "abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";
    
    //Read the number of Elements in the array
    int nElements;
    
    //Create the arrya
    BigramFreq array[MAX_ARRAY_ELEMENTS];
    
    //Read all the pairs
    readArrayBigramFreq (array, MAX_ARRAY_ELEMENTS, nElements);
    
    //Sort the array
    sortArrayBigramFreq(array, nElements);
    
    //Convert to uppercase
    toUpperArrayBigramFreq(array, nElements);
    
    //Print it
    printArrayBigramFreq(array, nElements);
    
    return 0;
}