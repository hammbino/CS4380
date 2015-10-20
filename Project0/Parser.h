//
//  Parser.h
//  Project0
//
//  Created by Jeffrey on 10/19/15.
//  Copyright (c) 2015 Jeffrey Hammond. All rights reserved.
//

#ifndef Project0_Parser_h
#define Project0_Parser_h



class Parser {
    // The int value is the opCode value
    enum OpCode
    {
        TRP = 0,                        // Trap Instruction
        JMP, JMR, BNZ, BGT, BLT, BRZ,   // Jump Instructions
        MOV, LDA, STR, LDR, STB, LDB,   // Move Instructions
        ADD, ADI, SUB, MUL, DIV,        // Arithmetic Instructions
        AND, OR,                        // Logical Instructions
        CMP,                            // Compare Instructions
        DOT_INT, DOT_ALN, DOT_BYT,      // Directives
        UNKNOWN
    };
    private:
    string lable, operand0, operand1;
    OpCode opType;
    int opCodeIndex, operandsNeeded, numBytesToImplement;
    bool isBlankLine, isDirective;
    
    public:
    
    const int MAX_TOKENS = 4;
    const int INVALID_INDEX = -1;
    
    Parser()
    {
        lable = operand0 = operand1 = " ";
        opType = UNKNOWN;
        opCodeIndex = INVALID_INDEX;
        operandsNeeded = numBytesToImplement = 0;
        isDirective = false;
        isBlankLine = false;
    }
};

#endif
