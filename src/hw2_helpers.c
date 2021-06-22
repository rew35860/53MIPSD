#include "hw2_helpers.h"

// Define any helper functions here
void createCopy(char* strToCopy, char* str){
    int i = 0;
    while(*(strToCopy+i)){
        *(str+i) = *(strToCopy+i);
        i++;
    }
    *(str+i) = '\0';
}

int getLength(char *str){
    int i = 0; 
    while(*(str+i) != '\0'){
        i++;
    }
    return i;
}

int inHex(char *n){
    // Checking if *n [0,9]
    if(*n >= 48 && *n <= 57){
        return 1; 
    }
    // Checking if *n [A, F]
    if(*n >= 65 && *n <= 70){
        return 1; 
    }
    // Checking if *n [a,f]
    if(*n >= 97 && *n <= 102){
        return 1; 
    }
    return 0; 
}

int hexCheck(char *n){
    int i = 0; 
    while(*(n+i)){
        if(!inHex((n+i))){
            return 0; 
        }
	i++;
    }
    if(i != 8){
	return 0;
    }
    return 1; 
}

int typeCheck(char *n){
    if(*n == 'r' || 
       *n == 'j' ||
       *n == 'i'){
            return 1; 
    }
    return 0; 
}

int mnemonicCheck(char *n){
    int i = 0; 
    while(*(n+i)){
        if(*(n+i) < 97 || *(n+i) > 122){
            return 0; 
        }
	i++;
    }
    return 1;
}

int terminator(char* n){
    if(*n == '\0' || *n == '\n'){
	return 1; 
    }
    return 0; 
}

int calculateHex(char *n){
    int i = 0;
    int h = 268435456; 
    int r = 0; 
    while(*(n+i)){
	// Checking if *n [0,9]
	if(*(n+i) >= 48 && *(n+i) <= 57){
	    r += (*(n+i)-48)*h; 
	}
	// Checking if *n [A,F]
	if(*(n+i) >= 65 && *(n+i) <= 70){
            r += (*(n+i)-55)*h; 
    	}
    	// Checking if *n [a,f]
    	if(*(n+i) >= 97 && *(n+i) <= 102){
            r += (*(n+i)-87)*h; 
    	}
	h /= 16;
	i++;
    }
    return r; 
}

int linkedListLength(listnode_s* listhead){
    int n = 0;     

    while(listhead){
	n++; 
   	listhead = listhead->next;
    }
    return n;
}

int compare(char *n, char *t){
    int i = 0;
    while(*(n+i)){
    	if(*(n+i) != *(t+i)){
	    return 0; 	
	}
	i++;
    }
    return 1;
}

int checkduplicate(listnode_s* listhead, instr_s* curInstr){
    while(listhead){
	if(listhead->data->uid == curInstr->uid){
		return 1;	
	}
	listhead = listhead->next;
    }
    return 0;
}

int checkless(listnode_s* listhead, instr_s* curInstr){
    while(listhead){
	if(listhead->data->uid < curInstr->uid){
		return 0;	
	}
	listhead = listhead->next;
    }
    return 1;
}

int checkmore(listnode_s* listhead, instr_s* curInstr){
    while(listhead){
	if(listhead->data->uid > curInstr->uid){
		return 0;	
	}
	listhead = listhead->next;
    }
    return 1;
}

int getForm(char** inputArray, uint8_t pretty){
    char* toSubstring2 = "m r r r";
    char* toSubstring = malloc(8*sizeof(char));
    char* toSubstringSeek = toSubstring;
    // string.h strcpy (needed so toSubstring may be modified)
    while ((*toSubstringSeek++ = *toSubstring2++));
    toSubstring2 -= 8;

    int n = 0;
    if(pretty == 2 || pretty == 3 || pretty == 8 || pretty == 9){
        n = getSubstrings(toSubstring, ' ', inputArray, 4);
        return n;
    }
    if(pretty == 1 || pretty == 4 || pretty == 7 || pretty == 10){
        n = getSubstrings(toSubstring, ' ', inputArray, 3);
        return n;
    }
    if(pretty == 0 || pretty == 6){
        n = getSubstrings(toSubstring, ' ', inputArray, 2);
        return n;
    }

    n = getSubstrings(toSubstring, ' ', inputArray, 1);
    return n;
}

void getRegister(char* name, int n, int numeric){
    char* result = malloc(7*sizeof(char));

    char* registerNumber = malloc(3 * sizeof(char));
    snprintf( registerNumber, 3, "%d", n );

    int i = 0; 
    *result = '$'; 

    if(numeric){
        while(*(registerNumber+i)){
            *(result+i+1) = *(registerNumber+i);
            i++;
        }
        *(result+i+1) = '\0';
        createCopy(result, name);

        free(result);
        free(registerNumber);
        return;

    }else{

        if(n == 0){
            *(result+1) = 'z'; 
            *(result+2) = 'e';
            *(result+3) = 'r';
            *(result+4) = 'o'; 
            *(result+5) = '\0';
        }
        if(n == 1){
            *(result+1) = 'a'; 
            *(result+2) = 't';
            *(result+3) = '\0';
        }
        if(n == 2 || n == 3){
            *(result+1) = 'v'; 
            *(result+2) = *registerNumber-2;
            *(result+3) = '\0';
        }
        if(n >= 4 && n <= 7){
            *(result+1) = 'a'; 
            *(result+2) = *registerNumber-4;
            *(result+3) = '\0';
        }
        if(n >= 8 && n <= 15){
            int t = n-8;

            registerNumber = realloc(NULL, 2 * sizeof(char));
            snprintf( registerNumber, 2, "%d", t );

            *(result+1) = 't'; 
            *(result+2) = *registerNumber;
            *(result+3) = '\0';
        }
        if(n >= 16 && n <= 23){
            int t = n-16;
        
            registerNumber = realloc(NULL, 2 * sizeof(char));
            snprintf( registerNumber, 2, "%d", t );

            *(result+1) = 's'; 
            *(result+2) = *registerNumber;
            *(result+3) = '\0';
        }
        if(n == 24 || n == 25){
            int t = n-16;
        
            registerNumber = realloc(NULL, 2 * sizeof(char));
            snprintf( registerNumber, 2, "%d", t );

            *(result+1) = 'v'; 
            *(result+2) = *registerNumber;
            *(result+3) = '\0';
        }
        if(n == 26 || n == 27){
            int t = n-26;
        
            registerNumber = realloc(NULL, 2 * sizeof(char));
            snprintf( registerNumber, 2, "%d", t );

            *(result+1) = 'k'; 
            *(result+2) = *registerNumber;
            *(result+3) = '\0';
        }
        if(n == 28){
            *(result+1) = 'g'; 
            *(result+2) = 'p';
            *(result+3) = '\0';
        }
        if(n == 29){
            *(result+1) = 's'; 
            *(result+2) = 'p';
            *(result+3) = '\0';
        }
        if(n == 30){
            *(result+1) = 'f'; 
            *(result+2) = 'p';
            *(result+3) = '\0';
        }
        if(n == 31){
            *(result+1) = 'r'; 
            *(result+2) = 'a';
            *(result+3) = '\0';
        }
    }
    createCopy(result, name);
    free(result);
    free(registerNumber);
    return;
}

void addComma(char* str){
    int i = getLength(str);
    *(str+i) = ',';
    *(str+i+1) = '\0';
}

// only for pretty 4
void addpara(char* r, char* immi, char* rs){
    int size = getLength(immi) + getLength(rs) + 3; 
    char* result = malloc(size * sizeof(char));
    int i = 0; 
    int j = 0; 

    while(*(immi+i)){
        *(result+i) = *(immi+i);
        i++;
    }

    *(result+i) = '(';
    i++; 

    while(*(rs+j)){
        *(result+i) = *(rs+j);
        j++;
        i++;
    }
    *(result+i) = ')';
    *(result+i+1) = '\0'; 
    
    createCopy(result, r);
    return;
}

void getimmediate(char* name, int n){
    char* result = malloc(11*sizeof(char));
    char* hex = malloc(15 * sizeof(char));
    decToHexa(hex, n);

    int i = 0; 
    *result = '0';
    *(result+1) = 'x'; 

    while(*(hex+i)){
        *(result+i+2) = *(hex+i);
        i++;
    }

    *(result+i+2) = '\0';
    createCopy(result, name);

    free(result);
    free(hex);
    return;
}

void decToHexa(char* hex, int n){  
    char* hexa = malloc( 11 * sizeof(char));    
    int i = 0; 
    int j = 0;
    int t = 0;
    
    if(n == 0){
        *hex = '0';
        *(hex+1) = '\0';
        return;
    }

    while(n!=0){    
        int temp  = 0; 
        temp = n % 16; 


        if(temp < 10){ 
            *(hexa+i) = temp + 48; 
            i++; 
        }else{ 
            *(hexa+i) = temp + 87; 
            i++; 
        } 
        n = n/16; 
    } 
    for(int j=i-1; j>=0; j--){ 
        *(hex+t) = *(hexa+j); 
        t ++;
    }
    *(hex+t) = '\0';
    free(hexa);
} 

int isKthBitSet(int n, int k) 
{ 
    int t = n; 
	if (!((t >> (k - 1)) & 1)) 
		return 1;
	else
		return 2;
} 
