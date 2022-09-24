#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {
    int length = atoi(argv[1]);
    /*
        if -> length stdin is "equal to" length 
            -> then
            print stdin to stdout
    */
   
   char * line;
   size_t len = 0;
   ssize_t lineSize = 0;
   lineSize = getline(&line, &len, stdin);

   while(lineSize > 1){
    if(lineSize == length + 1){
        printf("%s", line);
    }
    lineSize = getline(&line, &len, stdin);
   }
   

}
 
