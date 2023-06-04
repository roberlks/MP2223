/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file LEARN.cpp
 * @author Roberto González Lugo
 * Created on 29 January 2023, 11:00
 */


#include <cstring>
#include "BigramCounter.h"
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
using namespace std;

int main(int argc,char *argv[]) {   
    //Processing of call parameters:

    // Variables that store the info of the input parameters
    
    char mode = 't';//Text or binary mode
    string languageID = "unknown";  // Name of the language
    string outputFile = "output.bgr";  // Name of the output file

    // Processing optional parameters
    int argIndex = 1;
    while (argIndex < argc && argv[argIndex][0] == '-') {
        string arg = argv[argIndex];

        if (arg == "-t") {
            mode = 't';
        } else if (arg == "-b") {
            mode = 'b';
        } else if (arg == "-l" && argIndex + 1 < argc) {
            languageID = argv[argIndex + 1];
            argIndex++;
        } else if (arg == "-o" && argIndex + 1 < argc) {
            outputFile = argv[argIndex + 1];
            argIndex++;
        }

        argIndex++;
    }
    if (argc-argIndex < 1){
        showEnglishHelp(cerr);
    }
    
    BigramCounter MyBc; //The BigramCounter to store the info of all books toguether
    
    //Read and add all the books that are inputed (At least 1)
    for (int i = argIndex; i<argc; i++){
        BigramCounter bc;
        bc.calculateFrequencies(argv[i]);
        MyBc += bc;
    }
    
    Language lg;
    lg = MyBc.toLanguage();
    lg.setLanguageId(languageID);
    
    char outputFilename[outputFile.length() + 1];
    strcpy(outputFilename, outputFile.c_str());
    
    lg.save(outputFilename, mode);
    
    
    

    return 0;
}




//Prueba parametros:
    /*
    // Imprimir los valores de los parámetros leídos
    cout << "Modo de archivo de salida: " << (isBinary ? "Binario" : "Texto") << endl;
    cout << "Idioma: " << language << endl;
    cout << "Archivo de salida: " << outputFile << endl;

    // Procesar los archivos de entrada (resto de los argumentos)
    for (int i = argIndex; i < argc; i++) {
        string inputFile = argv[i];
        // Realizar el procesamiento necesario para cada archivo de entrada
        cout << "Archivo de entrada: " << inputFile << endl;
    }
    */

