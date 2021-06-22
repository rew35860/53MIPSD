#include "linkedList.h"
#include "hw2_helpers.h"
/*
    What is a linked list?
    A linked list is a set of dynamically allocated nodes, arranged in
    such a way that each node contains one value and one pointer.
    The pointer always points to the next member of the list.
    If the pointer is NULL, then it is the last node in the list.

    A linked list is held using a local pointer variable which
    points to the first item of the list. If that pointer is also NULL,
    then the list is considered to be empty.
    -----------------------------              -------------------------------
    |              |             |            \ |              |             |
    |     DATA     |     NEXT    |--------------|     DATA     |     NEXT    |
    |              |             |            / |              |             |
    ------------------------------              ------------------------------
*/

void insertAtHead(listnode_s** listHead, instr_s* curInstr) {
    listnode_s* new_node = malloc(sizeof(listnode_s));
    new_node->data = curInstr;
    new_node->next = *listHead;
    *listHead = new_node;
}

void insertAtTail(listnode_s** listHead, instr_s* curInstr) {
    while(*listHead) {
        listHead = &((*listHead)->next);
    }
    *listHead = malloc(sizeof(listnode_s));
    (*listHead)->next = NULL;
    (*listHead)->data = curInstr;
}

instr_s* findbyUID(listnode_s* listHead, uint32_t targetUID) {
    while(listHead) {
        if(listHead->data->uid == targetUID)
            return listHead->data;
        listHead = listHead->next;
    }
    return NULL;
}

void printList(listnode_s* listHead)  {
    printf("***LIST START***\n");
    while(listHead) {
        instr_s* curInstr = listHead->data;
        printf("[listnode 0x%p]:  uid: 0x%08x pretty %u mnemonic: %s next: 0x%p\n", curInstr, curInstr->uid, curInstr->pretty, curInstr->mnemonic, listHead->next); 
        listHead = listHead->next;
    }
    printf("***LIST END***\n");
    return;
}

void insertInUIDOrder(listnode_s** listHead, instr_s* curInstr) {
    // Insert Code Here
    // Checking if listHead is empty 
    listnode_s* new_node = malloc(sizeof(listnode_s));
  
    if(*listHead == NULL){
	insertAtHead(listHead, curInstr);
	return;
    }else{
	// Checking if listHead only has one value
	if(linkedListLength(*listHead) == 1){
	     if((curInstr->uid) == ((*listHead)->data->uid)){
	 	errno = EEXIST;
		return;
	     }   
	     if((curInstr->uid) < ((*listHead)->data->uid)){
		insertAtHead(listHead, curInstr);
		return;
	     }
	     if((curInstr->uid) > ((*listHead)->data->uid)){
		insertAtTail(listHead, curInstr);
		return;
	     }
	}else{
	    if(checkduplicate(*listHead, curInstr)){
	     	errno = EEXIST;
		    return;
        }
	    if(checkless(*listHead, curInstr)){
		    insertAtHead(listHead, curInstr);
		    return;
	    }
        if(checkmore(*listHead, curInstr)){
		    insertAtTail(listHead, curInstr);
		    return;
	    }
	    while(*listHead){
		    if((*listHead)->next != NULL && ((curInstr->uid) > ((*listHead)->data->uid) && (curInstr->uid) < ((*listHead)->next->data->uid))){
	 	        new_node->data = curInstr;
    		    new_node->next = (*listHead)->next;
		        (*listHead)->next = new_node;	
		        return;
		    }
		    listHead = &((*listHead)->next);
	    }
	}	
    }
    errno = EEXIST;
    return;
}

instr_s* findbyName(listnode_s* listHead, char* targetName) {
    // Insert Code Here
     while(listHead) {
        if(compare(listHead->data->mnemonic, targetName)){
            return listHead->data;
	}
        listHead = listHead->next;
    }
    return NULL;
}

void deleteList(listnode_s** listHead) {
    // Insert Code Here
    listnode_s *store; 

    while(*listHead){
	store = (*listHead)->next;
	deleteInstr((*listHead)->data);
	free(*listHead);
	*listHead = store;
    }
}
