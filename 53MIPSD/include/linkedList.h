#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "hw2_p1.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

struct listnode{
    instr_s* data;		    // pointer to the instruction struct stored
    struct listnode* next;   // pointer to item in the list 
};
typedef struct listnode listnode_s;

//Functions already implemented 
void insertAtHead(listnode_s** listHead, instr_s* curInstr);
void insertAtTail(listnode_s** listHead, instr_s* curInstr);
instr_s* findbyUID(listnode_s* listHead, uint32_t targetUID);
void printList(listnode_s* listHead);

// Function to implement
void insertInUIDOrder(listnode_s** listHead, instr_s* curInstr);
instr_s* findbyName(listnode_s* listHead, char* targetName);
void deleteList(listnode_s** listHead);

#endif
