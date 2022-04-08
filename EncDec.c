/*
ECE 103
Homework #4
Benjamin Warren
bewarren@pdx.edu
Description: Program lets users decide to encode a message, decode an encoded message, or read in
a user provided file with an encoded message and then outputs the encoded/decoded message using
the user provided password to translate.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char LookupTable[95][95] = {0};//Global array for lookup table

void Table() { //Creates lookup table indices
    int i;
    int j;
    for(i = 0; i < 95; ++i) {
        for(j = 0; j < 95; ++j) {
                LookupTable[i][j] = (i + j + 32) % 127;
                    if((i + j + 32) > 127) {
                        LookupTable[i][j] +=32;
                    }
        }
    }
}

void Encode(char string[160], char pass[160], char encodedVal[160]) { //for encoding messages
    int i;
    int j;
    int k = 0;
    char Temp[160];

    for(i = 0; i < strlen(string) - 1; ++i) {
        Temp[i] = pass[(i % (strlen(pass) - 1))];
    }

    for(i = 0; i < strlen(string) - 1; ++i) {
        j = (Temp[i] - 32);
        k = (string[i] - 32);
        encodedVal[i] = LookupTable[j][k];
        printf("%c", encodedVal[i]);
    }
    printf("\n\n");
}

void Decode(char string[160], char pass[160], char decodedVal[160]) { //for decoding messages
    int i;
    int j;
    int k;
    int l;
    char Temp[160] = {0};

    for(i = 0; i < strlen(string) - 1; ++i) {
        if(string[i] == 10) {
        }
        else {
            Temp[i] = pass[(i % (strlen(pass) - 1))];
        }
    }

    for(i = 0; i < strlen(string) - 1; ++i) {
        if (string[i] == 10) {
            printf("\n");
        }
        else {
            j = (Temp[i] - 32);
            for(k = 0; k < 95; ++k){
                if(LookupTable[j][k] == string[i]) {
                    l = k;
                }
            }
            decodedVal[i] = LookupTable[0][l];
            printf("%c", decodedVal[i]);
        }
    }
    printf("\n\n");
}

int main() {
    char userString[160] = {0}, encodedStr[160] = {0}; //Encoded or decoded string storage
    char userCode[160] = {0}; //Password for encoding or decoding
    char testfile[160] = {0}; //User file to decode
    char select[160]; //Menu selection
    int i = 0; //looping or incrementing variable
    FILE *in_file; //Pointer to open a file user selected
    char file, filetext[160] = {0}; //Temp and string storage for input file

    Table();

    while(select[0] != 'q' || select[0] != 'Q') { //While user doesn't choose to quit
        printf("Available Options:\n");
        printf(" [e] Encode\n");
        printf(" [d] Decode\n");
        printf(" [r] Read file\n");
        printf(" [q] Quit\n\n");

        printf("Please enter your choice: ");
        fgets(select, 1000, stdin);

        if(select[0] == 'e' || select[0] =='E') { //Encodes Strings
            printf("\nEnter the original message: ");
            fgets(userString, 159, stdin);

            printf("\nEnter the passcode: ");
            fgets(userCode, 159, stdin);

            printf("\nEncoded message: ");
            Encode(userString, userCode, encodedStr);
        }

        else if(select[0] == 'd' || select[0] == 'D') { //Decodes strings
            printf("\nEnter the encoded message: ");
            fgets(userString, 159, stdin);

            printf("\nEnter the passcode: ");
            fgets(userCode, 159, stdin);

            printf("\nDecoded message: ");
            Decode(userString, userCode, encodedStr);
        }

        else if(select[0] == 'r' || select[0] == 'R') { //Reads files and decodes
            printf("\nEnter the file to be opened: ");
            fgets(testfile, 160, stdin);
           testfile[strlen(testfile) - 1] = '\0';

            in_file = fopen(testfile, "r");
            if (in_file == NULL) {
                printf("\nError cannot open file\n");
                return -1;
            }
            i = 0;
            while(1) {
                    file = fgetc(in_file);
                    if(file==EOF) {
                        break;
                    }
                    else {
                        filetext[i] = file;
                        ++i;
                    }
            }
            fclose(in_file);

            printf("\nEnter the passcode: ");
            fgets(userCode, 159, stdin);

            printf("\n");
            Decode(filetext, userCode, encodedStr);

        }

        else if(select[0] == 'q' || select[0] == 'Q') {
            printf("Program terminated\n");
            return 0;
        }

        else {
            printf("\nThat choice is not valid\n\n");
        }
    }

    return 0;
}
