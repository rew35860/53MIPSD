#ifndef HW2_P3_H
#define HW2_P3_H
#include "linkedList.h"
#include <stdbool.h>
#include <unistd.h>

#define EXIT_FILEERR 2

typedef struct{
    size_t count;       
    listnode_s* listHead;	
} instType_s;

void printInstr(MIPSfields*, instr_s*, bool, FILE * );
void addInstr(instType_s*, instr_s*, instr_e);

#endif
