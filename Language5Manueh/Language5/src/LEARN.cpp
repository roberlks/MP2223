/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file LEARN.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */
#include <regex>
#include<sstream>

#include "BigramCounter.h"
#include "Language.h"
using namespace std;

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> .... ]" << endl;
    outputStream << "           learn the model for the language languageId from the text files <text1.txt> <text2.txt> <text3.txt> ..." << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-l languageId: language identifier (unknown by default)" << endl;
    outputStream << "-o outputFilename: name of the output file (output.bgr by default)" << endl;
    outputStream << "<text1.txt> <text2.txt> <text3.txt> ....: names of the input files (at least one is mandatory)" << endl;
}

/**
 * This program learns a Language model from a set of input tex files (tex1.txt,
 * tex2.txt, ...
 * Running example:
 * > LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> ....]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */

int main(int argc, char *argv[]) {   
    char mode = 't';
    string languageID = "unknown";
    string archivoSalida = "output.bgr";

    int indiceArg = 1;
    while (indiceArg < argc && argv[indiceArg][0] == '-') {
        string arg = argv[indiceArg];

        if (arg == "-t") {
            mode = 't';
        } else if (arg == "-b") {
            mode = 'b';
        } else if (arg == "-l" && indiceArg + 1 < argc) {
            languageID = argv[indiceArg + 1];
            indiceArg++;
        } else if (arg == "-o" && indiceArg + 1 < argc) {
            archivoSalida = argv[indiceArg + 1];
            indiceArg++;
        } else {
            showEnglishHelp(cerr);
            return 1;
        }

        indiceArg++;
    }

    if (argc - indiceArg < 1) {
        showEnglishHelp(cerr);
        return 1;
    }
    
    BigramCounter ref;
    
    for (int i = indiceArg; i < argc; i++){
        BigramCounter tmp;
        tmp.calculateFrequencies(argv[i]);
        ref += tmp;
    }
    
    Language miLang;
    miLang = ref.toLanguage();
    miLang.setLanguageId(languageID);
    miLang.save(archivoSalida.c_str(), mode);
    
    return 0;
    
}