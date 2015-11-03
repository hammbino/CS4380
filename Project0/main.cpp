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

using byte = unsigned char;

const int MEM_SIZE = 1000000;
byte mem[MEM_SIZE] {};

map<string, int> SymbolTable {};

vector<string> operators {
    "TRP",                                      // Trap Instruction
    "JMP", "JMR", "BNZ", "BGT", "BLT", "BRZ",   // Jump Instructions
    "MOV", "LDA", "STR", "LDR", "STB", "LDB",   // Move Instructions
    "ADD", "ADI", "SUB", "MUL", "DIV",          // Arithmetic Instructions
    "AND", "OR",                                // Logical Instructions
    "CMP",                                      // Compare Instructions
    ".INT", ".ALN", ".BYT",                     // Directives
};

//check if a string is an OpCode Operator
bool IsOp(string &s) {
    for (auto i = operators.begin(); i != operators.end(); ++i) {
        if (!s.compare(*i))
            return true;
    }
    return false;
}

//check is a string is a register
bool IsReg(string s) {
    if ((s[0] == 'R' || s[0] == 'r') && s.size() == 2) {
            return true;
    }
    return false;
}

//check is opCode is Immediate
bool IsImmediate(string &s, string &opcode)
{
    for (auto i = 0; i < opcode.length(); ++i)
        opcode[i] = toupper(opcode[i]);
    if (opcode == ".INT" || opcode == ".BYT")
    {
        return false;
    }
    else
    {
        for (auto i = operators.begin(); i != operators.end(); ++i) {
            if (!s.compare(*i)) {
                return false;
            }
        }
//            
//        for (int i = 0; i < operators.size(); ++i) {
//            string op = operators[i];
//            if ( opcode == op ) {
//                return false;
//            }
//        }
    }
    return true;
}

void AddSymbol(string &s, string &s2, int &a)
{
    auto ret = SymbolTable.insert(std::make_pair(s, a));
    if ( ! ret.second ) {
//        cout << "key " <<  s << " already exists "
//        << " with value " << (ret.first)->second << endl;
    }
    else {
//        cout << "created key " << s << " with value " << a << endl;
        if (s2 == ".INT") {
            a += 4;
        }
        else if (s2 == ".BYT") {
            a++;
        }
    }
}

void IntToMem(int number,int &position) {
    mem[position++] = (char)(number >> 0);
    mem[position++] = (char)(number >> 8);
    mem[position++] = (char)(number >> 16);
    mem[position++] = (char)(number >> 24);
}

void CharToMem(char character, int &position)
{
    mem[position++] = character;
}



int main(int argc, const char * argv[]) {

    int memCounter = 0;
    int pc = 0;
    int position = 0;
    std::regex comment(";*");
    ifstream inputFile;
    string lineFromFile;
    string word;
    string tempString;
    char tempChar = '\n';
    
    
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
            std::vector<string> words;
             while (inputFile && std::getline(inputFile, lineFromFile)){
                 std::stringstream lineToSplit(lineFromFile);
                 words.clear();
                 if (lineToSplit.peek() != ';' && lineToSplit.peek() != '\n') {
                     while (lineToSplit >> word) {
    //                     if(regex_match(word,comment)) {
    //                         cout << word << endl;
    //                         lineToSplit.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
    //                     }
                     
                         
                         words.push_back(word);
                         
                         //check first strings for Labels
                         
                        }
//                     for (auto wordToken : words) {
//                         cout << wordToken << " ";
//                     }
//                     cout << endl;
                     if (words.size()) {
                         if (!IsOp(words[0]) && !IsReg(words[0]) && !IsImmediate(words[0], words[1])) {
                             AddSymbol(words[0], words[1], memCounter);
                         }
                     }
                 }
                 //DEBUG//
//                 cout << lineFromFile << endl;
             }
        }
        inputFile.close();
//
//        for (int i = 0; i < words.size(); ++i) {
//            cout << i << "\t" << words[i] << endl;
//        }
        

        // display symbol table contents
        for (auto i = SymbolTable.begin(); i!=SymbolTable.end(); ++i)
            std::cout << i->first << " => " << i->second << '\n';
    }
    //-------------
    // Second Pass
    //-------------
//    pc = memCounter;//start PC at end of static data (start of instructions)
//    while (inputFile && std::getline(inputFile, lineFromFile)){
//        std::stringstream lineToSplit(lineFromFile);
//        std::vector<string> words;
//        words.clear();
//        while (lineToSplit >> word) {
//            words.push_back(word);
//        }
//        auto search = SymbolTable.find(words[0]);
//        if (search != SymbolTable.end()) {
//            if(words[1] == ".INT") {
//                int i_dec = std::stoi(words[2]);
//                IntToMem(i_dec, position);
//            }
//            else if (words[1] == ".BYT") {
//                if (words[2] == "'" && words[3] == "'") {
//                    tempString = " ";
//                }
//                else {
//                    tempString = '\n';
//                }
//                CharToMem(tempChar, position);
//            }
//        }
//        
//        if (IsOp(words[0]) == false) //if the first string is the not the OpCode
//        {
//            words.erase(words.begin());
//        }
//        if (IsOp(words[0]) == true)
//        {
//            int i_dec = std::stoi(words[0]);
//            int i, j, k;
//            switch (i_dec)
//            {
//                case 13: //Add OpCode is 13
//                IntToMem(13, position);
//                //store RD into mem
//                i = std::stoi(words[1]);
//                IntToMem(i , position);
//                //store RS into mem
//                j = std::stoi(words[2]);
//                IntToMem(j, position);
//                break;
//                case 10: //LDR OpCode is 10
//                IntToMem(10, position);
//                //store RD into mem
//                int k = std::stod(words[1]);
//                IntToMem(k, position);
//                //store value from label
//                tempString = words[2];
//                int tempSymbolValue = SymbolTable[tempString];
//                IntToMem(tempSymbolValue, position);
//                break;
//                case 12: //LDB OpCode is 12
//                IntToMem(12, position);
//                //Store RD into mem
//                j = std::stoi(words[1]);
//                IntToMem(i, position);
//                //store label value into mem
//                tempString = words[2];
//                tempSymbolValue = SymbolTable[tempString];
//                IntToMem(tempSymbolValue, position);
//                break;
//                case 0: //TRP OpCode is 0
//                IntToMem(0, position);
//                //check what kind of TRP
//                if (words[1] == "3")
//                {
//                    IntToMem(3, position);
//                }
//                else if (words[1] == "0")
//                {
//                    IntToMem(0, position);
//                }
//                else if (words[1] == "1")
//                {
//                    IntToMem(1, position);
//                }
//                break;
//                case 7: //MOV OpCode is 7
//                IntToMem(7, position);
//                //store RD into mem
//                i = std::stoi(words[1]);
//                IntToMem(i, position);
//                //store RS into mem
//                i = std::stoi(words[2]);
//                IntToMem(i, position);
//                break;
//                case 17: //DIV OpCode is 17
//                IntToMem(17, position);
//                //store RD into mem
//                i = std::stoi(words[1]);
//                IntToMem(i, position);
//                //store RS into mem
//                i = std::stoi(words[2]);
//                IntToMem(i, position);
//                break;
//                case 16: //MUL OpCode is 16
//                IntToMem(16, position);
//                //store RD into mem
//                i = std::stoi(words[1]);
//                IntToMem(i, position);
//                //store RS into mem
//                i = std::stoi(words[2]);
//                IntToMem(i, position);
//                break;
//                case 15: //SUB OpCode is 15
//                IntToMem(15, position);
//                //store RD into mem
//                i = std::stoi(words[1]);
//                IntToMem(i, position);
//                //store RS into mem
//                i = std::stoi(words[1]);
//                IntToMem(i, position);
//                break;
//                default:
//                break;
//            }
//        }
//    }
}
