#include "hw2_helpers.h"
#include "hw2_p1.h"

int getSubstrings(char *str,  char delim, char ** array, int maxSize) {
    // Initializing local variables
    int i = 0;      // index of str 
    int j = 0;      // index of array 

    // Checking for invalidity 
    if(maxSize < 1 || str == NULL || array == NULL){return -1;}
    
    // Checking for empty string 
    if(getLength(str) == 0){return 0;}
 
    // Performing the operation 
    for(i = 0; *(str+i); i++){
	if(*(str+i) == '\n'){break;}
        if(*(str+i) == delim){
            *(str+i) = '\0';
	    if(i == 0){
                *(array+j) = (str+i);
                j++;
            }
	    if(*(str+i+1) == '\n'){break;}
            if(*(str+i+1) != '\0' && j < maxSize && *(str+i+1) != delim){
                *(array+j) = (str+i+1);
                j++;
            }
        }else{
            if(i == 0){
                *(array+j) = (str+i);
                j++; 
            }
        }
        if(j >= maxSize){
            return j;   
        }
    }
    return j; 
}

void getMIPSfields (const uint32_t instruction, MIPSfields *f) {
    f->opcode = (((1 << 6)-1) & (instruction >> (27-1))); 
    f->rs = (((1 << 5)-1) & (instruction >> (22-1))); 
    f->rt = (((1 << 5)-1) & (instruction >> (17-1))); 
    f->rd = (((1 << 5)-1) & (instruction >> (12-1))); 
    f->shamt = (((1 << 5)-1) & (instruction >> (7-1))); 
    f->func = (((1 << 6)-1) & (instruction >> (1-1))); 
    f->immediate16 = (((1 << 16)-1) & (instruction >> (1-1))); 
    f->immediate26 = (((1 << 26)-1) & (instruction >> (1-1))); 
}

instr_s* createInstr(char* line, instr_e* type) {
    // Initializing local variables 
    instr_s* result = malloc(sizeof(instr_s)); 
    int size = getLength(line)+1; 
    
    // Creating the copy of the string
    char* toSubstring = malloc(size * sizeof(char));
    char* toSubstringSeek = toSubstring;
    while ((*toSubstringSeek++ = *line++));
    line -= size;

    char** array = malloc(5 * sizeof(char *));
    size = getSubstrings(toSubstring, ' ', array, 5);

    // Cheacking for invalidity 
    if(size != 4){return NULL;}
    if(!typeCheck(*array)){return NULL;}
    if(!hexCheck(*(array+1))){return NULL;}
    if(!mnemonicCheck(*(array+2))){return NULL;}
    int n = atoi(*(array+3));
    if(n < 0 || n > 10){return NULL;}

    // Perfroming the operation 
    if(**array == 'r'){ *type = R;}
    if(**array == 'i'){ *type = I;}
    if(**array == 'j'){ *type = J;}
           
    result->uid = calculateHex(*(array+1));
    result->pretty = n; 

    size = getLength(*(array+2)); 
    result->mnemonic = malloc(size * sizeof(char));
    
    int i = 0; 
    while(*(*(array+2)+i)){
    	result->mnemonic[i] = *(*(array+2)+i);
	i++; 
    }
    
    free(array);
    free(toSubstring);

    return result; 
}

void deleteInstr(instr_s* item){
    if(item != NULL){
	free(item->mnemonic);
	free(item);
    }
}

