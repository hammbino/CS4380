//
//  main.cpp
//  Project0
//
//  Created by Jeffrey on 10/18/15.
//  Copyright (c) 2015 Jeffrey Hammond. All rights reserved.
//



#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::string;
using std::ifstream;
#include <cstring>
#include "Parser.h"

const char* const DELIMITER = " ";

using byte = unsigned char;
int main(int argc, const char * argv[]) {
    const int MEM_SIZE = 100;

    byte mem[MEM_SIZE];
    ifstream inputFile;
    int i = 0;
    
//    Parser myParser = new Parser();
    
    // a .asm file must be sent from the command line
    if ( argc < 2 ) {
        std::cerr << "ERROR: the name of the .asm file MUST be spcified\n";
        return -1;
    }
    else {
        // assume argv[1] is a filename to open
        ifstream inputFile ( argv[1] );
        // check to see if file opening succeeded
        if ( !inputFile ) {
         
            std::cerr << "ERROR: Could not open .asm file\n";
            return -1;
            
        }
        else {
            string line;
            while (inputFile && getline(inputFile, line)){
                i++;
                cout << line << endl;
                cout << i << endl;
            }
        }
    // the_file is closed implicitly here
    }
}