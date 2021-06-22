#include <stdio.h> 
#include <stdlib.h> 
#include "hw2_p1.h"
#include "linkedList.h"

int main() 
{ 
    /*listnode_s* myHead = NULL;
    instr_e myType = -1;
	
    

    instr_s* myInstr1 = createInstr("r 00000009 jalr 2", &myType);
    instr_s* myInstr2 = createInstr("r 00000012 mflo 0", &myType);
    instr_s* myInstr3 = createInstr("j 00000100 jal 6", &myType);
    instr_s* myInstr4 = createInstr("i 00000200 lh 4", &myType);

    insertAtHead(&myHead, myInstr1);
    printf("insertAtHead: Current head element is %s\n", myHead->data->mnemonic);
    insertAtHead(&myHead, myInstr2);
    printf("insertAtHead: Current head element is %s\n", myHead->data->mnemonic);
    insertAtHead(&myHead, myInstr3);
    printf("insertAtHead: Current head element is %s\n", myHead->data->mnemonic);
    insertAtHead(&myHead, myInstr4);
    printf("insertAtHead: Current head element is %s\n", myHead->data->mnemonic);


    myInstr1 = createInstr("r 0000000c syscall 5", &myType);
    insertAtTail(&myHead, myInstr1);
    printf("insertAtTail: Current head element is %s\n", myHead->data->mnemonic);

    myInstr2 = findbyUID(myHead, 0xc);
    if(myInstr1 == myInstr2)
        printf("findbyUID: FOUND!\n");
    else
        printf("findbyUID: OOPS!\n");

    myInstr1 = createInstr("r 0000000c newsyscall 5", &myType);
    insertAtHead(&myHead, myInstr1);
    myInstr1 = findbyUID(myHead, 0xc);
    printf("findbyUID: %s\n", myInstr1->mnemonic); // should be newsyscall, not syscall

    myHead->data->uid = 0x2;  // Change the list to be in UID order

    myInstr1 = createInstr("r 00000012 mflo 0", &myType);
    errno = 0;  // set errno to OK before calling function
    insertInUIDOrder(&myHead, myInstr1); 
    if(errno == EEXIST)
        printf("insertInUIDOrder: InsertFailed. SUCCESS!!\n");
    else   
        printf("insertInUIDOrder: OOPS!!\n");
    deleteInstr(myInstr1);
    //printList(myHead);
    
    myInstr1 = createInstr("r 00004000 sltu 3", &myType);
    insertInUIDOrder(&myHead, myInstr1);
    insertInUIDOrder(&myHead, myInstr1);
   insertInUIDOrder(&myHead, myInstr1);
    printList(myHead);

    myInstr2 = findbyName(myHead, "sltu");
    if(myInstr2 != NULL){
    	printf("findbyName: FOUND!\n");
    }else{
	printf("findbyName: NotFOUND!\n");
    }
    if(myInstr1 == myInstr2)
        printf("findbyName: FOUND!\n");
    else
        printf("findbyName: OOPS!\n");
    deleteList(&myHead);*/
	
	listnode_s* myHead = NULL;
	instr_e myType = -1;

	instr_s* myInstr1 = createInstr("r 00000008 jalr 2", &myType);
	instr_s* myInstr2 = createInstr("r 00000019 mflo 0", &myType);
	instr_s* myInstr3 = createInstr("r 0000001b jal 6", &myType);
	instr_s* myInstr4 = createInstr("r 00000026 lh 4", &myType);
	instr_s* myInstr5 = createInstr("r 0000002a lh 4", &myType);

	insertAtHead(&myHead, myInstr4);
	insertAtHead(&myHead, myInstr3);
	insertAtHead(&myHead, myInstr2);
	insertAtHead(&myHead, myInstr1);
	insertAtTail(&myHead, myInstr5);

	printList(myHead);

	instr_s* myInstr6 = createInstr("r 00000022 lh 4", &myType);

	insertInUIDOrder(&myHead, myInstr6);
	printList(myHead);

 	deleteList(&myHead);

    return 0; 
} 
