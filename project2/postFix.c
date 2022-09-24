/* 
    Jeremiah Thompson
    CS 231: Project 2
    Week 2: April 15th, 2022
*/

#include "stackADT.h"
#include <ctype.h>
#include <string.h>

void evaluate(listType * stack, char operator){
    double num1 = pop(stack);
    double num2 = pop(stack);
    
    switch (operator){
    case '+':
        push(stack, (num2 + num1));
        break;
    case '-':
        push(stack, (num2 - num1));
        break;
    case '*':
        push(stack, (num2 * num1));
        break;
    case '/':
        push(stack, (num2/num1));
        break;
    
    default:
        exit(0);
    }
}

void strEval(char * expression, listType * stack){
    char set[] = "\n\t ";

    char * token = strtok(expression, set);

    while(token != NULL){
        if(isdigit(*token)){
            push(stack, (atof(token)));
        }
        else{
            evaluate(stack, *token);
        }
        token = strtok(NULL ,set);
    }

}

int main(int argc, char * argv[]){
    //create variables for the file inputs 
    FILE * file_input;
    FILE * output_file;
    
    //Our pointers to represent both the incoming file and what we output to "out.txt"
    file_input = fopen(argv[1], "r");
    output_file = fopen(argv[2], "w");

    //char varaiables
    char line[82];
    listType * stack;

    while(fgets(line, sizeof(line), file_input)){ //We have data
        //Create a empty stack
        stack = create();
        strEval(line, stack);
        double answer = pop(stack);
        fprintf(output_file,"%f\n" ,answer);
    }
    fclose(file_input);
    fclose(output_file);
    destroy(stack);
    return 0;  
}