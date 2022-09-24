/*
Jeremiah Thompson 
CS 231
April 26th, 2022

Wordgrab.c

    1) read a text file
    2) write the contents one word per line to output.

*/
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>


#define WORD_STATE 0
#define SEPARATOR_STATE 1

/*
    Word_State: any input letter will be copied to the output. the tranisition is to this same state.
*/

/*
    How to Run
    1) gcc -o wordGrab wordGrab.c in.txt
    2) ./wordGrab in.txt
*/

int isALetter(char input_char){
    return (input_char >= 'A' && input_char <= 'Z' || input_char >= 'a' && input_char <= 'z');
}

int main(int argc, char * argv[]) {
   //open file
    FILE * file_pointer;
    file_pointer = fopen(argv[1], "r");
    int input_char = getc(file_pointer); //get characters from file
    int state = SEPARATOR_STATE;

    while(input_char != EOF){
        /*
            Condition 1: when state = WORD_STATE & input_char is a letter --> Action
            Condition 2: when state = WORD_STATE & input_char is NOT a letter --> Action
            Condition 3: when state = SEPERATOR_STATE & input_char is a letter --> Action
            Condition 4: when state = SEPERATOR_STATE & input_char is NOT a letter --> No action no need for writing script
        */ 
       if (isALetter(input_char)){
           //Condition 1 & 3
           putchar(input_char);
           //Condition 3
           if(state == SEPARATOR_STATE){ 
               state = WORD_STATE; 
           }
       } 
       //Condition 2
       else if (state == WORD_STATE){
        putchar('\n'); 
        state = SEPARATOR_STATE;
       }
       //Condition 4 has no action 
        input_char = getc(file_pointer);
    }
   
}