#include "stack.c"
#include <string.h>
#include <stdio.h>

int main(){
    char str[] = "This is a string";
    char set[] = "\n\t ";

    char * token = strtok(str, set);

    while(token != NULL){
        printf("%s\n", token);
        token= strtok(NULL,set);
    }
}