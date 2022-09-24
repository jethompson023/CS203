/* 
Jeremiah Thompson
CS 231: Project 1
Week 1: April 8th, 2022
*/

/*
    Variables:
    - argv[1] is our input file
    - argv[2] is our output file 
    - FILE is our variable type
    - file_pointer is a type pointer for the file stream
    
    Program Operations:
    1) Opening "in.txt" file
    2) Reading the file
    3) Changing the case of all chracters using toggle case
    4) creating new file "out.txt"
    5) Writing data to "out.txt"
    6) Closing the file
*/

#include <stdio.h>
#include <stdlib.h>
#define BAD_EXIT 1

#include "stackADT.h"

int match(char left, char right){
    if(left == '(' && right == ')'){
        return 1;
    }

    if(left == '[' && right == ']'){
        return 1;
    }

    if(left == '{' && right == '}'){
        return 1;
    }
    return 0;
}

int main(int argc, char * argv[]){
    FILE * file_pointer;
    FILE * output_file;
    char line[82];
    
    //Setting the pointer within "fopen" reading mode 
    file_pointer = fopen(argv[1], "r"); 
    

    //Perform the write function for the "fopen" funciton
    output_file = fopen(argv[2], "w");

    char * data;
    data = fgets(line, sizeof(line), file_pointer);
  	
    //This is the main loop that will drive the character changing for our script
  	while(data != NULL){
        fprintf(output_file,"%s", line);
        listType * stack = create();
        for (int i = 0; line[i]!= '\0'; i++){
            
            if(line[i] == '(' || line[i] == '[' || line[i] == '{'){
                push(stack, line[i]);
            }		
                
            else if(line[i] == ')' || line[i] == ']' || line[i] == '}'){
                if(isEmpty(stack)){
                    fprintf(output_file, "ERROR parens don't match\n");
                    break;
                }
                else{
                    char top = peek(stack);
                    
                    if(match(top, line[i]) ){
                        pop(stack);
                    }
                    else{
                        fprintf(output_file, "ERROR parens don't match\n");
                        break;
                    }

                }

            }
        }
        
        if(!isEmpty(stack)){
            fprintf(output_file, "ERROR parens don't match\n");
        }
        else{
            fprintf(output_file, "All parens match!!\n");
        }
        data = fgets(line, sizeof(line), file_pointer);
        destroy(stack);
        
    }
    fclose(file_pointer);

    return 0;
}
