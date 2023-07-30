/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file JOIN.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */


/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */

#include "Language.h"

using namespace std;

void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>] " << endl;
    outputStream << "       join the Language files <file1.bgr> <file2.bgr> ... into <outputFile.bgr>" << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-o <outputFile.bgr>: name of the output file (output.bgr by default)" << endl;
    outputStream << "<file*.bgr>: each one of the files to be joined" << endl;
}

/**
 * This program reads an undefined number of Language objects from the files
 * passed as parameters to main(). It obtains as result the union of all the 
 * input Language objects. The result is then sorted by decreasing order of 
 * frequency and alphabetical order of bigrams when there is any tie in 
 * frequencies. Finally, the resulting Language is saved in an output file. The 
 * program must have at least an input file. 
 * Running example:
 * >  JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */
int main(int argc, char* argv[]) {
    char modo_salida = 't';
    string archivo_salida = "output.bgr";  

    int indiceArg = 1;
    while (indiceArg < argc && argv[indiceArg][0] == '-') {
        string arg = argv[indiceArg];

        if (arg == "-t") {
            modo_salida = 't';
        } else if (arg == "-b") {
            modo_salida = 'b';
        } else if (arg == "-o" && indiceArg + 1 < argc) {
            archivo_salida = argv[indiceArg + 1];
            indiceArg++;
        }
        else{
            showEnglishHelp(cerr);
            return 1;
        }

        indiceArg++;
    }
    if (argc-indiceArg < 1){
        showEnglishHelp(cerr);
        return 1;
    }
    
    Language ref;
    ref.load(argv[indiceArg]);
    indiceArg++;
    
    for (int i = indiceArg; i < argc; i++){
        Language cp;
        cp.load(argv[i]);
        
        if (cp.getLanguageId() == ref.getLanguageId()){
            ref += cp;
        }        
    }
    ref.sort();
    ref.save(archivo_salida.c_str(), modo_salida);
    
    
    
    return 0;
}

