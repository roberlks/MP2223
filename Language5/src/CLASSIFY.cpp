/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file CLASSIFY.cpp
 * @author Roberto González Lugo
 * Created on 29 January 2023, 11:00
 */

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
//    const char separador = '|';
//    const std::string FinalMessage = "Final decision: language | with a distance of |";
//
//    std::string primeraParte;
//    std::string segundaParte;
//
//    // Buscar el primer separador
//    size_t pos = FinalMessage.find(separador);
//    if (pos != std::string::npos) {
//        // Extraer la primera parte antes del separador
//        primeraParte = FinalMessage.substr(0, pos);
//
//        // Buscar el segundo separador a partir de la posición siguiente
//        size_t pos2 = FinalMessage.find(separador, pos + 1);
//        if (pos2 != std::string::npos) {
//            // Extraer la segunda parte entre los dos separadores
//            segundaParte = FinalMessage.substr(pos + 1, pos2 - pos - 1);
//        }
//    }
//    
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
    
    lg_toClassify.sort();
    
    int files = argc-2;
    
    Language* languages = new Language[files];
    
        
    for (int i = 0; i<files; i++){
        languages[i].load(argv[i+2]);
    }

    double distances[files];
    int pos_min = 0;
    for (int i = 0; i<files; i++){
        //distances[i] = languages[i].getDistance(firstLanguage);
        distances[i] = lg_toClassify.getDistance(languages[i]);        
        if (distances[i] < distances[pos_min]){pos_min = i;}        
    }
    
    showFinalMessage(languages[pos_min].getLanguageId(), distances[pos_min]);
    delete [] languages;
    
    return 0;
    
}

