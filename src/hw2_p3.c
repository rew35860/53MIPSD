#include "linkedList.h"
#include "hw2_p3.h"
#include "hw2_helpers.h"

void printInstr(MIPSfields* instr, instr_s* curInstr, bool numeric, FILE * ofile){
    char** substrings = malloc(5*sizeof(char *));
    char* rs = malloc(7*sizeof(char *));
    char* rt = malloc(7*sizeof(char *));
    char* rd = malloc(7*sizeof(char *));
    char* shamt = malloc(7*sizeof(char *));
    char* immediate16 = malloc(11*sizeof(char *));
    char* immediate26 = malloc(11*sizeof(char *));
    char* immediate16rs;
    int flag = 0; 
    int r = getForm(substrings, curInstr->pretty);
    *substrings = curInstr->mnemonic; 

    if(curInstr->pretty == 0){
        getRegister(rd, instr->rd, numeric);
        *(substrings+1) = rd;
    }
    if(curInstr->pretty == 1){
        getRegister(rs, instr->rs, numeric);
        addComma(rs);
        *(substrings+1) = rs;
        getRegister(rt, instr->rt, numeric);
        *(substrings+2) = rt;
    }
    if(curInstr->pretty == 2){
        getRegister(rt, instr->rt, numeric);
        addComma(rt);
        *(substrings+1) = rt;
        getRegister(rs, instr->rs, numeric);
        addComma(rs);
        *(substrings+2) = rs;
        getimmediate(immediate16, instr->immediate16);
        *(substrings+3) = immediate16;
    }
    if(curInstr->pretty == 3){
        getRegister(rd, instr->rd, numeric);
        addComma(rd);
        *(substrings+1) = rd;
        getRegister(rs, instr->rs, numeric);
        addComma(rs);
        *(substrings+2) = rs;
        getRegister(rt, instr->rt, numeric);
        *(substrings+3) = rt;
    }
    if(curInstr->pretty == 4){
        getRegister(rt, instr->rt, numeric);
        addComma(rt);
        *(substrings+1) = rt;

        getRegister(rs, instr->rs, numeric);
        getimmediate(immediate16, instr->immediate16);

        int size = getLength(immediate16) + getLength(rs) + 3; 
        immediate16rs = malloc(size * sizeof(char));
        addpara(immediate16rs, immediate16, rs);
        *(substrings+2) = immediate16rs;
        flag = 1;
    }
    if(curInstr->pretty == 6){
        getimmediate(immediate26, instr->immediate26);
        *(substrings+1) = immediate26;
    }
    if(curInstr->pretty == 7){
        getRegister(rs, instr->rs, numeric);
        addComma(rs);
        *(substrings+1) = rs;
        getimmediate(immediate16, instr->immediate16);
        *(substrings+2) = immediate16;
    }
    if(curInstr->pretty == 8){
        getRegister(rd, instr->rd, numeric);
        addComma(rd);
        *(substrings+1) = rd;
        getRegister(rs, instr->rs, numeric);
        addComma(rs);
        *(substrings+2) = rs;
        getimmediate(shamt, instr->shamt);
        *(substrings+3) = shamt;
    }
    if(curInstr->pretty == 9){
        getRegister(rs, instr->rs, numeric);
        addComma(rs);
        *(substrings+1) = rs;
        getRegister(rt, instr->rt, numeric);
        addComma(rt);
        *(substrings+2) = rt;
        getimmediate(immediate16, instr->immediate16);
        *(substrings+3) = immediate16;
    }
    if(curInstr->pretty == 10){
        getRegister(rt, instr->rt, numeric);
        addComma(rt);
        *(substrings+1) = rt;
        getimmediate(immediate16, instr->immediate16);
        *(substrings+2) = immediate16;
    }

    for(int i = 0; i < r-1; i++){
        fprintf(ofile, "%s ", *(substrings+i));
    }
    fprintf(ofile,"%s\n", *(substrings+r-1));

    free(substrings);
    free(rs);
    free(rt);
    free(rd);
    free(shamt);
    free(immediate16);
    free(immediate26);
    if(flag){
        free(immediate16rs);
    }
}

void addInstr(instType_s* MIPSinstr, instr_s* curInstr, instr_e type){
    if(curInstr != NULL){
        insertInUIDOrder(&(MIPSinstr+type)->listHead, curInstr); 
        (MIPSinstr+type)->count += 1;
    }
}
