#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1

/*
    parent.c: Purpose of this program is to begin working on takign our seperate processes within the folder and bring them together
*/

int main(int argc, char * argv[]){
    //amount of words needed to run the program
    char * wordLength = argv[2];

    //Get the input & output files
    char * input_file = argv[1];
    char * output_file = argv[3];

    // Check to make sure we have enough arguments within the call. For this we need 3 argumnets 
    //If not tell the user
    if (argc < 4) {
        printf("ERROR! Please try again not enough arguments entered into the program.\n");
        return 1;
    }
    //all processes needed for this program to run
    int wordGrab[2];
    int lengthCheck[2];
    int reverse[2];

    /*
    Process Flow for Program:
        1) wordGrab (parent process) will get the file contents and send to lengthCheck
        2) lengthCheck then gets the length of the file contents and sends to reverse
        3) reverse takes the file contents and sends to the caseworker program
    */
   
    // Create pipes to send the file  thorugh the different progams
    pipe(wordGrab); 
    pipe(lengthCheck); 
    pipe(reverse);

    //create a process id for wordGrab
    pid_t wordGrabPid = fork();

    //Starting point for the process
    //Begin with the parent process wordGrab
    if(wordGrabPid > 0){
        //Get the information for wordGrab
        char * arg[2];
        arg[0] = "./wordGrab.c";
        arg[1] = input_file;
        
        // dup2 everything going to STDOUT from wordGrab to our pipe
        dup2(wordGrab[WRITE_END], STDOUT_FILENO);

        // Close the read end, as we won't be reading anything
        close(wordGrab[READ_END]);

        // Send to the first child process lengthCheck
        execvp(arg[0], arg);
    }
    else{
        //child process 
         pid_t lengthCheckPid = fork();

        // Parent (lengthCheck)
        if (lengthCheckPid > 0) {
            // Get information for lengthCheck
            char * arg[2];
            arg[0] = "./lengthCheck";
            arg[1] = wordLength;
           

            // send to stdin
            dup2(wordGrab[READ_END], STDIN_FILENO);

            // send to our lengthCheck pipe
            dup2(lengthCheck[WRITE_END], STDOUT_FILENO);

            // close the pipe
            close(wordGrab[READ_END]);
            close(wordGrab[WRITE_END]);

            // send results to the next child process
            execvp(arg[0], arg);
        }
        else{
        // Fork process
            pid_t revPid = fork();

            // Parent (reverse)
            if (revPid > 0) {
                // get info for reverse
                char *arg[1];
                arg[0] = "./reverse";
                

                // Pipe the output from lengthCheck process to stdin
                dup2(lengthCheck[READ_END], STDIN_FILENO);

                // Pipe output from this process to our reverse pipe
                dup2(reverse[WRITE_END], STDOUT_FILENO);

                // Close our pipe to lengthCheck, as it's no longer needed after we copied it over to stdout
                close(lengthCheck[READ_END]);
                close(lengthCheck[WRITE_END]);

                // This child's stdin is now an open pipe to our parent process
                execvp(arg[0], arg);
            }
            
            else {
                //get to run caseWorker
                char * arg[2];
                arg[0] = "./caseWorker";
                arg[1] = output_file;

                // Pipe the output from reverse process to stdin
                dup2(reverse[READ_END], STDIN_FILENO);

                // close the pipe
                close(reverse[READ_END]);
                close(reverse[WRITE_END]);

                // This child's stdin is now an open pipe to our parent process
                execvp(arg[0], arg);
            }
        }
    }
}