/*
 I was unable to get my file handler to read and or output to another file,
but my two translator functions both work
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char* breakBefore(char*, char);
char* breakAfter(char*, char);
char* destToBinary(char*);
char* compToBinary(char*);
char* translate(char*);
char* jumpToBinary(char*);
int stringToInt(char*);
char* intToBinary(int);
char* aTranslator(char*);
int charToDigit(char);
void fileHandler();


int main()
{
    fileHandler();
    return 0;
}
char* aTranslator(char* ins){
    char* result = malloc(sizeof (char)*17);
    char* toTranslate = breakAfter(ins, '@');
    result = intToBinary(stringToInt(toTranslate));
    free(toTranslate);
    return result;
}
char* translate(char* ins){//translates c instructions
    int jmpOrDest = -1;
    char* toReturn = malloc(sizeof (char)*17);
    toReturn[0] = '\0';
    int len = strlen(ins);
    for(int i = 0; i < len;i++){
        if(ins[i] == '='){
            jmpOrDest = 1;
            break;
        }
        else if(ins[i] == ';'){
            jmpOrDest = 0;
            break;
        }
    }
    if (jmpOrDest == 1){ //means you have a dest
        char* compValue = breakAfter(ins,'=');
        char* destValue = breakBefore(ins,'=');

        char* compTranslation = compToBinary(compValue);
        char* destTranslation = destToBinary(destValue);

        strcat(toReturn,"111");
        strcat(toReturn, compTranslation);
        strcat(toReturn, destTranslation);
        strcat(toReturn,"000");

        free(compValue);
        free(destValue);
        free(compTranslation);
        free(destTranslation);
    }
    else if (jmpOrDest == 0) { //means you have a jump
        char* compValue = breakBefore(ins,';');
        char* jumpValue = breakAfter(ins,';');

        char* compTranslation = compToBinary(compValue);
        char* jumpTranslation = jumpToBinary(jumpValue);

        strcat(toReturn,"111");
        strcat(toReturn, compTranslation);
        strcat(toReturn, "000");
        strcat(toReturn,jumpTranslation);

        free(compValue);
        free(jumpValue);
        free(compTranslation);
        free(jumpTranslation);

    }
    return toReturn;
}

char* compToBinary(char* text){
    char* toReturn = malloc(sizeof (char)* 8);

    if (strcmp(text, "0") ==0){
        strcpy(toReturn,"0101010");
    }
    else if (strcmp(text, "1") ==0){
        strcpy(toReturn,"0111111");
       }
    else if (strcmp(text, "-1") ==0){
        strcpy(toReturn,"0111010");
       }
    else if (strcmp(text, "D") ==0){
        strcpy(toReturn,"0001100");
       }
    else if (strcmp(text, "A") ==0){
        strcpy(toReturn,"0110000");
       }
    else if(strcmp(text,"M") == 0){
       strcpy(toReturn,"1110000");
    }
    else if (strcmp(text, "!D") ==0){
        strcpy(toReturn,"0001101");
       }
    else if (strcmp(text, "!A") ==0){
        strcpy(toReturn,"0110001");
       }
    else if (strcmp(text,"!M") == 0) {
        strcpy(toReturn,"1110001");
    }
    else if (strcmp(text, "-D") ==0){
        strcpy(toReturn,"0001111");
       }
    else if (strcmp(text, "-A") ==0){
        strcpy(toReturn,"0110011");
       }
    else if (strcmp(text,"-M") == 0) {
        strcpy(toReturn,"1110011");
    }
    else if (strcmp(text, "D+1") ==0){
        strcpy(toReturn,"0011111");
       }
    else if (strcmp(text, "A+1") ==0){
        strcpy(toReturn,"0110111");
       }
    else if (strcmp(text,"M+1") == 0) {
        strcpy(toReturn,"1110111");
    }
    else if (strcmp(text, "D-1") ==0){
        strcpy(toReturn,"0001110");
       }
    else if (strcmp(text, "A-1") ==0){
        strcpy(toReturn,"0110010");
       }
    else if (strcmp(text,"M-1") == 0) {
        strcpy(toReturn,"1110010");
    }
    else if (strcmp(text, "D+A") ==0){
        strcpy(toReturn,"0000010");
       }
    else if (strcmp(text,"D+M")==0) {
        strcpy(toReturn,"1000010");
    }
    else if (strcmp(text, "D-A") ==0){
        strcpy(toReturn,"0010011");
       }
    else if (strcmp(text,"D-M")==0) {
        strcpy(toReturn,"1010011");
    }
    else if (strcmp(text, "A-D") ==0){
        strcpy(toReturn,"0000111");
       }
    else if(strcmp(text,"M-D")==0) {
        strcpy(toReturn,"1000111");
    }
    else if (strcmp(text, "D&A") ==0){
        strcpy(toReturn,"0000000");
       }
    else if (strcmp(text,"D&M")==0) {
        strcpy(toReturn,"1000000");
    }
    else if (strcmp(text, "D|A") ==0){
        strcpy(toReturn,"0010101");
       }
    else if (strcmp(text,"D|M")==0) {
        strcpy(toReturn,"1010101");
    }
    else{
        strcpy(toReturn,"xxxxxxx");
    }
    return toReturn;
}

char* destToBinary(char* text){
    char* toReturn = malloc(sizeof (char)*4);
        if (strcmp(text, "M") ==0){
            strcpy(toReturn,"001");
        }
        else if (strcmp(text, "D") ==0){
            strcpy(toReturn,"010");
           }
        else if (strcmp(text, "DM") ==0){
            strcpy(toReturn,"011");
           }
        else if (strcmp(text, "A") ==0){
            strcpy(toReturn,"100");
           }
        else if (strcmp(text, "AM") ==0){
            strcpy(toReturn,"101");
           }
        else if (strcmp(text, "AD") ==0){
            strcpy(toReturn,"110");
           }
        else if (strcmp(text, "ADM") ==0){
            strcpy(toReturn,"111");
           }
        else{
            strcpy(toReturn,"xxx");
        }

        return toReturn;
}
char* jumpToBinary(char* text){
    char* toReturn = malloc(sizeof (char)*4);
        if (strcmp(text, "M") ==0){
            strcpy(toReturn,"001");
        }
        else if (strcmp(text, "JGT") ==0){
            strcpy(toReturn,"001");
           }
        else if (strcmp(text, "JEQ") ==0){
            strcpy(toReturn,"010");
           }
        else if (strcmp(text, "JGE") ==0){
            strcpy(toReturn,"011");
           }
        else if (strcmp(text, "JNE") ==0){
            strcpy(toReturn,"101");
           }
        else if (strcmp(text, "JLE") ==0){
            strcpy(toReturn,"110");
           }
        else if (strcmp(text, "JMP") ==0){
            strcpy(toReturn,"111");
           }
        else if (strcmp(text,"JLT") == 0) {
            strcpy(toReturn,"100");
        }
        else{
            strcpy(toReturn,"xxx");
        }

        return toReturn;
}

char* breakBefore(char* string, char breakChar){
    unsigned long long position = 0;
    while(string[position] != breakChar && position < strlen(string)){
        position++;
    }
    char* result = malloc(sizeof(char) * (position + 1));

    for(unsigned long long i = 0; i < position; i++){
        result[i] = string[i];
    }

    result[position] = '\0';

    return result;
}

char* breakAfter(char* string, char breakChar){
    unsigned long long position = 0;
    while(string[position] != breakChar && position < strlen(string)){
        position++;
    }

    unsigned long long size = strlen(string) - position;
    char* result = malloc(sizeof(char) * (size + 1));

    position++;
    int start = 0;
    for(unsigned long long i = position; i < strlen(string); i++){
        result[start] = string[i];
        start++;
    }

    result[start] = '\0';

    return result;
}

char* intToBinary(int num){
    char *result = (char*)malloc(16*sizeof(char));
    //set each element in result to '0'
    for(int i=0;i<15;i++){
        result[i]='0';

    }
    int position = 14;
    while(position > 0){
        if(num % 2 == 0){
            result[position] = '0';
        }
        else if(num % 2 == 1){
            result[position] = '1';
        }
        num = num / 2;
        position--;
    }

    result[15] = '\0';
    return result;
}
int stringToInt(char* string){
    int len = strlen(string);
    int sum = 0;
    int power = 0;
    for(int i = len-1; i >= 0; i--){
        sum= sum+charToDigit(string[i]) * floor(pow(10,power++));
    }
    return sum;
}

int charToDigit(char digit){
    return digit - '0';
}

void fileHandler(){
    FILE* inputFile = NULL;
    FILE* outputFile = NULL;
    const int bufferSize = 256;
    char inputFileName[bufferSize];

    printf("Enter a file to read: ");
    fgets(inputFileName,bufferSize,stdin);

    inputFileName[strcspn(inputFileName, "\n")] = 0;

    inputFile = fopen(inputFileName, "r");
    outputFile = fopen("out.txt", "w");

    if(inputFile == NULL){
        puts("Error opening input File");
    }

    else if(outputFile == NULL){
        puts("Error opening output File");
    }

    else{
        char buffer[bufferSize];
        while (fgets(buffer,bufferSize,inputFile) != NULL) {
            buffer[strcspn(buffer,"\r\n")] = 0;
            if(buffer[0] == '@' ){
                char* toTranslate = buffer;
                char* result = aTranslator(toTranslate);
                fputs('0',outputFile);
                fputs(result,outputFile);
                fputs("\n", outputFile);
                free(result);
            }
            else{
                char* result = translate(buffer);
                fputs(result,outputFile);
                fputs("\n", outputFile);
                free(result);
            }


        }


    }
    fclose(inputFile);
    fclose(outputFile);

}
