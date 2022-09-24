/* 
    Jeremiah Thompson
    CS 231: Project 3
    caseWorker: This program will read the data from the input 
    and then output to a file. 
*/

#include "stdio.h"
#include "string.h"
#include <stdbool.h> 
#include <ctype.h>

/*
    Program Process 
    1) Import the input file "getc(file_pointer)"
    2) Create Loop to read every character within the "input_stream"
    3) "If" you come across a vowel within the array change the letter "case" "toUpper"
        "else if" if you read a constant in the array change the case "toLower"
        "else if" that it is neither just print the output 
*/

bool isVowel(char c){
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

int main(int argc, char * argv[0]){
    //open file 
    FILE * fpointer; 
    fpointer = fopen(argv[1], "w");
    char input_char;
    scanf("%c", &input_char);

    while(input_char != EOF){
        if(isVowel(input_char)){
            fprintf(fpointer,"%c", toupper(input_char));
        }
        else{
            fprintf(fpointer,"%c", tolower(input_char));
        }
        //scanf("%c", &input_char);
        input_char = getchar();
        fflush(fpointer);
    }
    fclose(fpointer);
}