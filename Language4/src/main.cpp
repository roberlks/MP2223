
/* 
 * File:   main.cpp
 * Author: roberlks222
 *
 * Created on 17 de abril de 2023, 18:25
 */
#include<iostream>
#include<string>
#include <fstream>
#include <cstring>

#include "Language.h"
using namespace std;

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "language4 [-t min|max] <file1.bgr> <file2.bgr> [ ... <filen.bgr>]" << endl;
}

/**
 * This program reads an undefined number of Language objects from the set of 
 * files passed as parameters to main(). All the Languages object, except the 
 * first one, must be stored in a dynamic array of Language objects. Then, 
 * for each Language in the dynamic array, this program prints to the 
 * standard output the name of the file of that Language and the distance from 
 * the first Language to the current Language. 
 * Finally, the program should print in the standard output, the name of 
 * the file with the Language with the minimum|maximum distance to the Language 
 * of the first file and its language identifier.
 * 
 * At least, two Language files are required to run this program.
 * Running example:
 * > language4 [-t min|max] <file1.bgr> <file2.bgr> [  ... <filen.bgr>] 
 */
int main(int argc, char* argv[]) {
    
    bool min = true;
    int files = argc-2;
    int first = 1;

    if (argc < 3) {
        showEnglishHelp(cerr);
        return 1;
    }

    if(argv[1][0] == '-'){
        if(strcmp(argv[1],"-t") == 0){
            if(strcmp(argv[2],"max") == 0){
                min = false;
                first = 3;
            }else if(strcmp(argv[2],"min") == 0){
                first = 3;
            }else{
                showEnglishHelp(cerr);
                return 1;
            }
        }

        files=argc-4;
    }

    if (files < 1){
        showEnglishHelp(cerr);
        return 1;
    }
    
    Language* languages;
    
    languages = new Language[files];
    Language firstLanguage;
    firstLanguage.load(argv[first]);
    
    for (int i = 0; i<files; i++){
        languages[i].load(argv[i+first+1]);
    }

    double distances[files];
    int pos_min = 0, pos_max = 0;
    for (int i = 0; i<files; i++){
        //distances[i] = languages[i].getDistance(firstLanguage);
        distances[i] = firstLanguage.getDistance(languages[i]);
        
        cout << "Distance to " << argv[i+first+1] << ": " << distances[i] << endl;
        
        if (distances[i] < distances[pos_min]){pos_min = i;}
        if (distances[i] > distances[pos_max]){pos_max = i;}
        
    }
    if (min){
 
        cout << "Nearest language file: ";
        cout << argv[pos_min+first+1] << endl;
        cout << "Identifier of the nearest language: " << languages[pos_min].getLanguageId() << endl;
    }
    else{
        cout << "Farthest language file: " << argv[pos_max+first+1] << endl
             << "Identifier of the farthest language: " << languages[pos_max].getLanguageId()<<endl;
    }
    
    delete[] languages; 
    return 0;
 



}