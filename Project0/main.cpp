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
#include <sstream>
#include <cstring>
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <regex>
#include <limits>

map<string, int> SymbolTable;

vector<string> operators {
    "TRP",                                      // Trap Instruction
    "JMP", "JMR", "BNZ", "BGT", "BLT", "BRZ",   // Jump Instructions
    "MOV", "LDA", "STR", "LDR", "STB", "LDB",   // Move Instructions
    "ADD", "ADI", "SUB", "MUL", "DIV",          // Arithmetic Instructions
    "AND", "OR",                                // Logical Instructions
    "CMP",                                      // Compare Instructions
    ".INT", ".ALN", ".BYT",                     // Directives
};

bool IsOp(string s) {
//    //Op values to compare against
//    std::vector<string> operators {
//        "TRP",                                      // Trap Instruction
//        "JMP", "JMR", "BNZ", "BGT", "BLT", "BRZ",   // Jump Instructions
//        "MOV", "LDA", "STR", "LDR", "STB", "LDB",   // Move Instructions
//        "ADD", "ADI", "SUB", "MUL", "DIV",          // Arithmetic Instructions
//        "AND", "OR",                                // Logical Instructions
//        "CMP",                                      // Compare Instructions
//        ".INT", ".ALN", ".BYT",                     // Directives
//    };
    //check if an OpCode Operator
    for (int i = 0; i < operators.size(); ++i) {
        string op = operators[i];
        if ( s == op ) {
            return true;
        }
    }
    return false;
}

bool IsReg(string s)
{
    char reg = 'R';
    if (s[0] == reg)
    {
        if (s.size() == 2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool IsImmediate(string s, string opcode)
{
    if (opcode == ".INT" || opcode == ".BYT")
    {
        return false;
    }
    else
    {
        for (int i = 0; i < operators.size(); ++i) {
            string op = operators[i];
            if ( s == op ) {
                return false;
            }
        }
    }
    return true;
}

void AddSymbol(string s, int a)
{
    auto search = SymbolTable.find(s);
    if(search != SymbolTable.end()) {
        SymbolTable.emplace(s, a);
    }
//    else {
//        std::cerr << "ERROR: Symbol not found\n";
//    }
}

using byte = unsigned char;

int main(int argc, const char * argv[]) {
    const int MEM_SIZE = 1000000;
    int memCounter = 0;
    std::regex comment(";*");
    std::vector<string> words;
    byte mem[MEM_SIZE];
    ifstream inputFile;
    
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
            // ----------------
            // First Read
            // ----------------
             string lineFromFile;
             while (inputFile && std::getline(inputFile, lineFromFile)){
                 std::stringstream lineToSplit(lineFromFile);
                 string word;
                 while (lineToSplit >> word) {
//
//                     if(regex_match(word,comment)) {
//                         cout << word << endl;
//                         lineToSplit.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
//                     }
                     words.push_back(word);
                 }
                 
            }
//            for (int i = 0; i < words.size(); ++i) {
//                cout << words[i] << endl;
            }
        inputFile.close();
        
        //check first strings for Labels
        if (!IsOp(words[0]) && !IsReg(words[0]) && !IsImmediate(words[0], words[1]))
        {
            AddSymbol(words[0], memCounter);
            if (words[1] == ".INT")
            {
                memCounter += 4;
            }
            else if (words[1] == ".BYT")
            {
                memCounter++;
            }
            else
            {
                std::cerr << "ERROR: Invalid value given \n";
                return -1;
            }
        }
    }
}

