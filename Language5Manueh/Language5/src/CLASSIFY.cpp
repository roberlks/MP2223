/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file CLASSIFY.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */

#include <iostream>
#include "BigramCounter.h"
/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */

using namespace std;

void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "CLASSIFY <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ....]" << endl;
    outputStream << "          Obtains the identifier of the closest language to the input text file" << endl;
    outputStream << endl;
}

/**
 * This program print the language identifier of the closest language 
 * for an input text file (<text.txt>) among the set of provided models:
 * <lang1.bgr>, <lang2.bgr>, ...
 * 
 * Running example:
 * > CLASSIFY  <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ...]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */
int main(int argc, char *argv[]) {
    if (argc < 3){
        showEnglishHelp(cerr);
        return 1;
    }
    
    Language lan_cl;
    BigramCounter bc_cl;
    
    bc_cl.calculateFrequencies(argv[1]);
    lan_cl = bc_cl.toLanguage();
    
    int archivos = argc-2;
    
    Language lan_min;
    lan_min.load(argv[2]);
    double dis_min = lan_cl.getDistance(lan_min);
    
    for (int i = 1; i < archivos; i++){
        Language lan;
        lan.load(argv[i+2]);
        double dis = lan_cl.getDistance(lan);
        if (dis < dis_min){
            dis_min = dis;
            lan_min = lan;
        }
    }
    cout << "Final decision: language " << lan_min.getLanguageId() << " with a distance of " << dis_min << endl;
    return 0;
}

