/**
 * Daniel Ty
 * TCSS 422
 * Assignment 1
 * Due 5/11/2021
 **/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<time.h>
#define MAXSTR 255
#define ARGCNT 5
/**
 * This program runs three Linux command requests against an input text file in
 * parallel. The command requests and text file are defined by input received
 * from the user through the console.
 **/


// Method header
char** toArgs(char* theCmd, char* theFile);

// Main method
int main(void) {
    // commands    
    char cmd1[MAXSTR];
    char cmd2[MAXSTR];
    char cmd3[MAXSTR];
    // text file
    char fileName[MAXSTR];

    // get user input for command one
    printf("cmd1>");
    fgets(cmd1, sizeof(cmd1), stdin);
    cmd1[strcspn(cmd1,"\n")] = 0; // remove newline

    // get user input for command two
    printf("cmd2>");
    fgets(cmd2, sizeof(cmd2), stdin);
    cmd2[strcspn(cmd2,"\n")] = 0; // remove newline
    
    // get user input for command three
    printf("cmd3>");
    fgets(cmd3, sizeof(cmd3), stdin);
    cmd3[strcspn(cmd3,"\n")] = 0; // remove newline

    // get user input for file name
    printf("file>");
    fgets(fileName, sizeof(fileName), stdin);
    fileName[strcspn(fileName,"\n")] = 0; // remove newline

    puts("--------------------------------------------------------------------------------");

    // commands to char* array of arguments
    char** args;

    // clock
    clock_t t;
    t = clock(); // start time

    // pids
    pid_t p1;
    pid_t p2;
    pid_t p3;

    // nested forks
    p1 = fork();
    if (p1 == 0) { // child
        // arguments for command 1
        args = toArgs(cmd1, fileName);
    }

    if (p1 > 0) { // parent    
        p2 = fork();
        if (p2 == 0) { // child
            // arguments for command 2
            args = toArgs(cmd2, fileName);
        }

        if (p2 > 0) { // child
            p3 = fork();
            if (p3 == 0) {
                // arguments for command 3
                args = toArgs(cmd3, fileName);
            }

            if (p3 > 0) {
                // wait for all child processes
                waitpid(p1, NULL, 0);
                waitpid(p2, NULL, 0);
                waitpid(p3, NULL, 0);

                // subtract start time from current time
                t = clock() - t;
                double time = ((double)t) / CLOCKS_PER_SEC;

                puts("--------------------------------------------------------------------------------");
                printf("Children process IDs: %ld %ld %ld.\n", (long)p1, (long)p2, (long)p3);
                printf("Total elapsed time:%fms\n", time * 1000); // convert secs to ms
            }
        }
    }

    // if child, execute command
    if (p3 == 0) {
        int status = execvp(args[0], args);
        free(args);
        printf("STATUS CODE=%d\n", status);
        fflush(stdout);
    }
    
    return 0;
}

/**
 * Converts a command to an char pointer array of arguments.
 * Returns char pointer array of arguments.
 * char* theCmd is the command to be converted.
 * char* theFile is the text file the commands are directed toward.
 **/
char** toArgs(char* theCmd, char* theFile) {
    char** args = malloc(sizeof(char*) * ARGCNT);

    char* token = strtok(theCmd, " ");
    // loop through the string to extract all other tokens
    int i = 0;
    while(token != NULL) {
        *(args + i) = token;
        // printf(" %s\n", token); //printing each token
        token = strtok(NULL, " ");
        i++;
    }
    *(args + i) = theFile;

    return args;
}