/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file JOIN.cpp
 * @author Roberto González Lugo
 * Created on 29 January 2023, 11:00
 */


#include "Language.h"

using namespace std;

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
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
    char mode_out = 't';//Text or binary mode
    string outputFile = "output.bgr";  // Name of the output file

    // Processing optional parameters
    int argIndex = 1;
    while (argIndex < argc && argv[argIndex][0] == '-') {
        string arg = argv[argIndex];

        if (arg == "-t") {
            mode_out = 't';
        } else if (arg == "-b") {
            mode_out = 'b';
        } else if (arg == "-o" && argIndex + 1 < argc) {
            outputFile = argv[argIndex + 1];
            argIndex++;
        }
        else{
            showEnglishHelp(cerr);
            return 1;
        }

        argIndex++;
    }
    if (argc-argIndex < 1){
        showEnglishHelp(cerr);
        return 1;
    }
    
    Language lg;
    lg.load(argv[argIndex]);
    argIndex++;
    for (int i = argIndex; i < argc; i++){
        Language tmp;
        tmp.load(argv[i]);
        if (tmp.getLanguageId() == lg.getLanguageId())
            lg += tmp;
    }
    lg.sort();
    lg.save(outputFile.c_str(), mode_out);
    
    
    return 0;
}

