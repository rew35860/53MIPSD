#ifndef HW2_P1_H
#define HW2_P1_H

// Needed C stdlib headers
// Do not add to this list
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Part 1 structures
typedef struct{ 
    uint8_t opcode;
    uint8_t rs;
    uint8_t rt;
    uint8_t rd;
    uint8_t shamt;
    uint8_t func;
    uint16_t immediate16;
    uint32_t immediate26;
} MIPSfields; 


typedef struct instr {
    uint32_t uid;        
    uint8_t pretty;      
    char* mnemonic;      
} instr_s;

typedef enum {R, I, J} instr_e; 

// Part 1 Functions
int getSubstrings(char *,  char, char **, int); 
void getMIPSfields(const uint32_t, MIPSfields*);
instr_s* createInstr(char*, instr_e*);
void deleteInstr(instr_s*);

#endif