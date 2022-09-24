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
#include <string.h>

int main(int argc, char * argv[]){
    FILE * file_pointer;
    char line[101];
    
    //Setting the pointer within "fopen" reading mode 
    //file_pointer = fopen(argv[1], "r"); **Not sure why this didn't work revisit later**
    file_pointer = fopen("in.txt", "r");

    
    //Print out the message within "in.txt" before any changes 
    printf("Here is our current contents of in.txt: \n");
    printf("=============\n");

    //Using "fgets" to get the contents from the input file
    printf("%s", fgets(line, sizeof(line), file_pointer));

    printf("Performing Case Toggle......\n");

    //Perform the write function for the "fopen" funciton
    file_pointer = fopen("out.txt", "w");
  	
    //This is the main loop that will drive the chracter changing for our script
  	for (int i = 0; line[i]!='\0'; i++){
  		
      if(line[i] >= 'a' && line[i] <= 'z'){
  			line[i] = line[i] - 32;
		  }		
  		
      else if(line[i] >= 'A' && line[i] <= 'Z'){
  			line[i] = line[i] + 32;
		  }
  	}
    
    printf("Here is the result after the toggle script out.txt: \n");
    printf("=============\n");

    //printf("%s", fgets(line, sizeof(line), file_pointer));
    
    printf("%s", line);
    fclose(file_pointer);

    return 0;
}

/* 
  How to run our program:
    Cmd 1: gcc [program name.c]
    Cmd 2: ./a.out in.txt out.txt
*/
