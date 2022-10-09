/**
--------------------------------------
Authors: Aidan Traboulay & Aleksander Neceski
IDs: 200115590 & 201851860
Emails: trab5590@mylaurier.ca & nece1860@mylaurier.ca
--------------------------------------
**/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>


int main(int argc, char *argv[]) { 
    if (argc != 1) { 
        printf("Program must be run with only one arg being fileName");
        exit(EXIT_FAILURE);
    }

    // const char *name = "sample_in_grades.txt";	// file name

    

    // Teacher Process spawns GTA processes

    // int GTA_pipe[2]; // Used for pipe between Teacher process and GTA process
    int TA_pipe[2];  // Used for pipe between GTA process and TA process
    // char* TA_pipe_string; // string used to read/write for TA pipe
    // char* GTA_pipe_string; // string used to read/write for GTA pipe


    // Parent process spawns 3 GTA processes
    int GTA_pid, TA_PID;
    int i;  
    for (i = 0; i < 3; i++) {
        GTA_pid = fork();
        if (GTA_pid == 0) {
            printf("Layer 1 GTA: PID: %d; PPID: %d\n", getpid(), getppid());
            break; // GTA process doesn't continue operation
        }
        else if (GTA_pid > 0) { 
            printf("i in GTA generating loop: %d \n", i);
            wait(NULL); // wait for execution of child process to complete
            // Pipe Ta_pipe_string up to Teacher
        }
        else {
            printf("Layer 1 GTA Failure: PID: %d; PPID: %d\n", getpid(), getppid());
            perror("error"); //fork()
        }
    }

    // GTA processes spawns 3 TA processes
     
    if (GTA_pid == 0) {
        for (i = 0; i < 2; i++) {
            if (GTA_pid == 0) {
                pipe(TA_pipe); // open pipe between parent and child
                TA_PID = fork();
            }
            if(TA_PID > 0) {        // inside of Teacher process
                wait(NULL);         // Wait for GTA process completion
                close(TA_pipe[1]); 

                int arr[10];        
                // n stores the total bytes read successfully
                int n = read(TA_pipe[0], arr, sizeof(arr));
                printf("TA_piped_array size: %d\n", n);
                int j = 0;
                for ( j = 0;j < n/4; j++) { // GTA processing goes here 
                    printf("%d ", arr[j]); 
                    if (j == 4) printf("\n");
                    fflush(stdout);
                }
                close(TA_pipe[0]);
            }
            else if( TA_PID == 0 ) {
                printf("Layer 2 TA: PID: %d; PPID: %d\n", getpid(), getppid());
                int arr[] = {1, 2, 3, 4, 5};
                
                close(TA_pipe[0]); // close unused reading end 
                 
                write(TA_pipe[1], &arr, sizeof(arr));
                close(TA_pipe[1]); 
                return 0;
            }
            else {
                printf("Layer 2 TA Failure: PID: %d; PPID: %d\n", getpid(), getppid());
                perror("error"); //fork()
            }
        }
    }
    // close(GTA_pipe[0]);
    // close(GTA_pipe[0]);
    printf("\n");
    fflush(stdout);
    printf("\n");
    fflush(stdout);
    return 0;

    // Teacher Process 
        // info pull from pipe
        // Spawn GTA Child Process
            // get information 
            // print information

    // GTA Process
        // info pull from pipe
        // spawn child processes and have them write to their memory space 
    
    // TA Process
        // Open and read memory space 
        // Open and read file 
        // Read starting char -> increment to same char at next line up until no more file 
        // Increment total -> get average
        // pass up through pipe
}