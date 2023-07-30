/*
 * Metodología de la Programación: Language3
 * Curso 2022/2023
 */

/* 
 * File:   main.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 *
 * Created on 7 de febrero de 2023, 14:02
 */
#include "Language.h"
#include "Bigram.h"
#include "BigramFreq.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>

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


bool Archivobgr(string nombre){
    bool aparece=false;
    
    for(int i=0; i<nombre.size(); i++){
        if(nombre.at(i)=='.'){
            if(nombre.at(i+1)=='b'){
                if(nombre.at(i+2)=='g'){
                    if(nombre.at(i+3)=='r'){
                       aparece=true;
                    }
                } 
            }
        }
    }
    return aparece;
}


void salida_min(int argc, Language target, Language* vector, string nombres[]){
   
           
    double distancia;
    double min=100000;
    int m;
    
    
    for(int i=0; i< argc; i++){
        distancia=target.getDistance(vector[i]);
        cout<<"Distance to "<<nombres[i]<<": "<<distancia<<endl;
        if(distancia < min){
            min = distancia;
            m = i;
        }
    
    }
    
    cout<<"Nearest language file: "<<nombres[m]<<endl;
  
    cout<<"Identifier of the nearest language: "<<vector[m].getLanguageId()<<endl;
    
}

void salida_max(int argc, Language target, Language* vector,string nombres[]){
   
           
    double distancia;
    double max=0;
    int m;
    
    
    for(int i=0; i< argc; i++){
       
        distancia=target.getDistance(vector[i]);
        cout<<"Distance to "<<nombres[i]<<": "<<distancia<<endl;
        if(distancia > max){
            max = distancia;
            m = i;
        }
    
    }
    
    cout<<"Farthest language file: "<<nombres[m]<<endl;
  
    cout<<"Identifier of the farthest language: "<<vector[m].getLanguageId()<<endl;
  
    
}
    


int main(int argc, char* argv[]) {
    
    if(argc < 3){
        
        showEnglishHelp(cout);
    }
    
    else{
        string cod1(argv[1]);
        string cod2(argv[2]);
        Language *vector = nullptr;
        Language target;
        
        
        if(cod1 == "-t"){
            
            
            if(cod2 == "max"){
                target.load(argv[3]);
                int n= argc-4;
                vector = new Language[n];
                string nombres[n];
                for(int i=4; i<argc; i++){
                    Language lang;
                    lang.load(argv[i]);
                    vector[i-4]=lang;
                    string cod(argv[i]);
                    nombres[i-4]=cod;
                 
                }
           
                salida_max(n,target,vector,nombres);
               
                delete[] vector;
                vector=nullptr;
        
            }
            
            else if(cod2 == "min"){
                target.load(argv[3]);
                int n= argc-4;
                vector = new Language[n];
                string nombres[n];
                for(int i=4; i<argc; i++){
                    Language lang;
                    lang.load(argv[i]);
                    vector[i-4]=lang;
                    string cod(argv[i]);
                    nombres[i-4]=cod;
                   
                }
                
                salida_min(n,target,vector,nombres);
  
                delete[] vector;
                vector = nullptr;
            }
        
            else {

                showEnglishHelp(cout);
            }
        }
        
        else if(Archivobgr(cod1)){
            
            target.load(argv[1]);
            int n= argc-2;
            vector = new Language[n];
            string nombres[n];
                
            for(int i=2; i<argc; i++){
                Language lang;
                lang.load(argv[i]);
                vector[i-2]=lang;
                string cod(argv[i]);
                nombres[i-2]=cod;
                
            }
            
            
            salida_min(n,target,vector,nombres);
           
            delete[] vector;
            vector = nullptr;
         
        }
        
        else{
       
            showEnglishHelp(cout);   
        }
        
        
        return 0;
    }
}