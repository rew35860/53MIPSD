#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "hw2_p3.h"


#define USAGE_MSG   "53MIPSD [-h] [-o ofile] [-i ifile] [-n] IMAPFILE\n"                                           \
                    "\n  -h    Displays the help menu"                                                             \
                    "\n  -o    ofile Specifies the name of the file to output to. If unspecified, stdout is used"  \
                    "\n  -i    ifile Specifies the name of the binary file to read. If unspecified, stdin is used" \
                    "\n  -n    Prints the registers as numerical values, instead of human-readable names\n"        \



int main(int argc, char* argv[]) {

    char* ofile = NULL; // The output file (remains NULL if -o option is not provided) 
    char* ifile = NULL; // The input file (remains NULL if -i option is not provided)
    bool numeric = false; // Numeric mode (remains false if -n option is not provided)
    opterr = 0;
    int c;
    while ((c = getopt(argc, argv, "ho:i:n")) >= 0) {
        switch (c)
        {
        case 'h':
            printf(USAGE_MSG);
            return EXIT_SUCCESS;
        case 'o':
            ofile = optarg;
            break;
        case 'i':
            ifile = optarg;
            break;
        case 'n':
            numeric = true;
            break;
        case '?':
            if (optopt == 'i' || optopt == 'o') {
                fprintf(stderr, "Option -%c requires an argument.\n\n" USAGE_MSG, optopt);
            }
        default:
            fprintf(stderr, USAGE_MSG);
            return EXIT_FAILURE;
        }
    }

    // validate that we only have 1 positional argument
    if (optind + 1 != argc) {
        fprintf(stderr, "Exactly one positional argument should be specified.\n\n" USAGE_MSG);
        return EXIT_FAILURE;
    }

    char* imapfile = argv[optind]; // The IMAPFILE specified

    // ifile, ofile, numeric and imapfile are now usable by your program!

    instType_s*  MIPSinstr = calloc(3, sizeof(instType_s)); // Initialize an all-zeroed MIPSinstr 1D array 
    char**       regNames  = calloc(32, sizeof(char*));     // Initialize 1D array for the register names

    // THE PRINT STATEMENTS BELOW ARE FOR DEBUGGING PURPOSES ONLY!
    // printf("ifile: %s\n", ifile);
    // printf("ofile: %s\n", ofile);
    // printf("numeric: %d\n", numeric);
    // printf("IMAPFILE: %s\n", imapfile);
    // THE PRINT STATEMENTS ABOVE ARE FOR DEBUGGING PURPOSES ONLY!


    // CODE START HERE ------------------------------------------------------------------------------------    
    // IMAPFILE IMPLEMENTATION
    // Opening the imapfile 
    FILE* imap; 
    imap = fopen(imapfile, "r"); 

    // Handeling non-existing file 
    if(imap == NULL){
        exit(2);             
    }

    // Reading the file line by line until EOF 
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    instr_e type = 3; 

    while((nread = getline(&line, &len, imap)) != -1){
        instr_s* mips = createInstr(line, &type);
        if(mips == NULL){
            exit(2);
        }
        addInstr(MIPSinstr, mips, type);
        if(errno == EEXIST){
            exit(2);
        }
    }

    fclose(imap);


    // INPUT FILE & OUTPUT FILE IMPLEMENTATION 
    uint32_t inputbits;
    instr_s* myInstr1;
    FILE* inputFile = stdin; 
    FILE* outputFile = stdout;

    if(ifile != NULL){
        inputFile = fopen(ifile, "r"); 
        if(inputFile == NULL){
            exit(2); 
        }
    }
    if(ofile != NULL){
        outputFile = fopen(ofile, "w");
        if(outputFile == NULL){
            exit(2);
        }
    }
  
    while(fread(&inputbits,sizeof(inputbits),1,inputFile) == 1){ 
        if(sizeof(inputbits) < 4){
            exit(2);
        }
        MIPSfields* myFields = malloc(sizeof(MIPSfields));  
        getMIPSfields(inputbits, myFields);
        
        if(myFields->opcode == 0){
            myInstr1 = findbyUID((MIPSinstr+0)->listHead, myFields->func);
        }else{
            if(myFields->opcode == 2 || myFields->opcode == 3){
                myInstr1 = findbyUID((MIPSinstr+2)->listHead, (myFields->opcode) << 26);
            } 
            else{
                myInstr1 = findbyUID((MIPSinstr+1)->listHead, (myFields->opcode) << 26);
            }
        }
        if(myInstr1 == NULL){   // UID does not exist
            exit(2);
        }else{
            printInstr(myFields, myInstr1, numeric, outputFile);
        }
    }
    if(ftell(inputFile) == 0){
        return 2;
    }

    fclose(inputFile);
    fclose(outputFile);
    
    // FREE MEMORY 
    deleteInstr(myInstr1);

    deleteList(&MIPSinstr[0].listHead);
    deleteList(&MIPSinstr[1].listHead);
    deleteList(&MIPSinstr[2].listHead);

    free(line);
    free(MIPSinstr); // free the memory we allocated because we are awesomely efficient programmers!
    free(regNames);  
    
    return EXIT_SUCCESS;
}