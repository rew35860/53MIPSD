#include <stdio.h>
#include "hw2_p3.h"

int main() {

    instType_s* MIPSinstr = calloc(3, sizeof(instType_s)); // Initialize an all-zeroed MIPSinstr array 

    uint32_t instruction = 0x24080539; // addiu $t0, $zero, 0x539
    MIPSfields myinstrfields;
    getMIPSfields(instruction, &myinstrfields);
    
    instr_e type = 3; 
    instr_s* addiu = createInstr("i 24000000 addiu 2\n", &type);
    printInstr(&myinstrfields, addiu, 1, stdout);  // numeric registers
    printInstr(&myinstrfields, addiu, 0, stdout);  // human-readable

    addInstr(MIPSinstr, addiu, type);  //Type should be i

    instr_s* sub = createInstr("r 00000022 sub 3\n", &type);
    addInstr(MIPSinstr, sub, type);  //Type should be r

    // !!!!You can use [] in the testing mains, just not in your src/  !!!!
    printList(MIPSinstr[0].listHead);  // Should print sub
    printList(MIPSinstr[1].listHead);  // Should print addiu
    printList(MIPSinstr[2].listHead);  // Should print no instructions
    instr_s* or = createInstr("r 00000025 or 3\n", &type);
    addInstr(MIPSinstr, or, type);  //Type should be r
    instr_s* sra = createInstr("r 00000003 sra 8\n", &type);
    addInstr(MIPSinstr,sra, type);  //Type should be r
    instr_s* mtlo = createInstr("r 00000013 mtlo 0\n", &type);
    addInstr(MIPSinstr,mtlo, type);  //Type should be r  
    printList(MIPSinstr[0].listHead);  // Should print sra->mtlo->sub->or

    deleteList(&MIPSinstr[0].listHead);
    deleteList(&MIPSinstr[1].listHead);
    deleteList(&MIPSinstr[2].listHead);


    free(MIPSinstr); // free the memory we allocated because we are awesomely efficient programmers!
    return 0;
}
