#ifndef HELPERS_2_H
#define HELPERS_2_H

#include "linkedList.h"

// Declare any helper functions here
void createCopy(char* strToCopy, char* str);
int getLength(char *str);
int hexCheck(char *n);
int inHex(char *n);
int typeCheck(char *n);
int mnemonicCheck(char *n);
int terminator(char *n);
int calculateHex(char *n);
int linkedListLength(listnode_s* listhead);
int compare(char *n, char *t);
int checkduplicate(listnode_s* listhead, instr_s* curInstr);
int checkless(listnode_s* listhead, instr_s* curInstr);
int checkmore(listnode_s* listhead, instr_s* curInstr);
int getForm(char** inputArray, uint8_t pretty);
void getRegister(char* name, int n, int numeric);
void addComma(char* str);
void addpara(char* r, char* immi, char* rs);
void getimmediate(char* name, int n);
void decToHexa(char* hex, int n);
int isKthBitSet(int n, int k);
#endif
