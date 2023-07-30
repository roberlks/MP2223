/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file CLASSIFY.cpp
 * @author Roberto González Lugo
 * Created on 29 January 2023, 11:00
 */

#include <regex>
#include<sstream>


#include "BigramCounter.h"

using namespace std;
/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "CLASSIFY <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ....]" << endl;
    outputStream << "          Obtains the identifier of the closest language to the input text file" << endl;
    outputStream << endl;
}
void showFinalMessage (string language, double distance, ostream& outputStream = cout){
    outputStream << "Final decision: language " << language << " with a distance of " << distance << endl;
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
    
    //Verify input parameters
    if (argc < 3){
        showEnglishHelp(cerr);
        return 1;
    }
    
    
    //First, generate a new language object to identify its language.
    Language lg_toClassify;
    BigramCounter bc_toClassify;
    
    bc_toClassify.calculateFrequencies(argv[1]);
    lg_toClassify = bc_toClassify.toLanguage();
    
    
    int files = argc-2;
        
    Language lang_min;
    lang_min.load(argv[2]);
    double dist_min = lg_toClassify.getDistance(lang_min);
    
    
    for (int i = 1; i<files; i++){
        Language lang;
        lang.load(argv[i+2]);
//        distances[i] = lg_toClassify.getDistance(languages[i]);    
        double dist = lg_toClassify.getDistance(lang); 
        if (dist < dist_min){dist_min = dist; lang_min = lang;}        
    }
    
    showFinalMessage(lang_min.getLanguageId(), dist_min);
    
    return 0;
    
}

