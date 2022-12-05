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
#include <sys/stat.h>
#include <stdbool.h>

#define neededC 21

int t_arr_len = 0;
int num_resources = 0;

int ** needed;
int ** allocated;
int * available;
int * max;

int* getneededResourceFromLine(char *line) { 
    
    int i = 0;
    char* token = strtok(line, ",");
    int * t_arr = malloc(sizeof(int) * num_resources);
    t_arr[i] = atoi(token);
    while ((token = strtok(NULL, ","))) {    
        i += 1;
        t_arr[i] = atoi(token);
        
    }

    return t_arr;
}

void readFileToneededArrAlloc(FILE** f, int ** needed) { 
    ssize_t read;
    size_t len = 0;
    char * line;
    int * t_arr; 

    // allocate lines and assign to index in array
    int i = 0; 
    while ((read = getline(&line, &len, *f)) != -1) {
        *(needed + i) = malloc(sizeof(int)*num_resources);
        t_arr = getneededResourceFromLine(line);
        for (int j = 0; j < num_resources; j++) { 
            needed[i][j] = t_arr[j];
        }
        i+=1;
    }

    return;
}

void determine_t_arr_len(FILE** f) { 
    ssize_t read;
    size_t len = 0;
    char * line;
     
    // count number of lines
    while ((read = getline(&line, &len, *f)) != -1) { 
        t_arr_len += 1;
    }
    // back to top of file
    rewind(*f);

    return;
}

void invoke_command(char* prefix, char* buf, int* resources) { 
    if (strcmp(prefix, "Exit") == 0) {
        exit(0);
    } else if (strcmp(prefix, "Run") == 0) { 
        printf("Not Implemented Yet \n");
    } else if (strcmp(prefix, "Status") == 0) { 
        printf("Not Implemented Yet\n");
    } else if (strcmp(prefix, "RQ") == 0) { 
        printf("Not Implemented Yet \n");
    } else if (strcmp(prefix, "RL") == 0) { 
        // release_resources(&temp);
        printf("Not Implemented Yet \n");
    } else { 
        printf("Invalid input, use one of RQ, RL, Status, Run, Exit \n");
    }
}

// bool safety_algorithm(int *available, int **needed, int **allocated, int **needed, int num_processes, int num_resources) {
//     int *work = malloc(sizeof(int) * num_resources);
//     int *is_done = malloc(sizeof(int) * num_processes);
//     int i, j, k, count = 0;

//     for (i = 0; i < num_resources; i++) {
//         work[i] = available[i];
//     }

//     for (i = 0; i < num_processes; i++) {
//         is_done[i] = 0;
//     }

//     for (i = 0; i < num_processes; i++) {
//         for (j = 0; j < num_processes; j++) {
//             if (is_done[j] == 0) {
//                 for (k = 0; k < num_resources; k++) {
//                     if (needed[j][k] > work[k]) {
//                         break;
//                     }
//                 }
//                 if (k == num_resources) {
//                     for (k = 0; k < num_resources; k++) {
//                         work[k] += allocated[j][k];
//                     }
//                     is_done[j] = 1;
//                 }
//             }
//         }
//     }

//     if (count == num_processes) {
//         return true;
//     } else {
//         return false;
//     }
// }

/* RQ Command */
void request_resources() {
    // BANKERS ALGORITHM CONCEPT 
        // never allocate resources to a process when there 
        // aren't enough remaining processes for it to complete

    // iterate over resources required

        // If current available resources < needed required
            // deny = true

    // if deny = false 
        // iterate over resources and allocate
}

/* RL Command */
void release_resources(char* buf) {
    char* token = strtok(buf, " ");
    int temp[num_resources];
    token = strtok(NULL, " "); // get thread num
    int thread_num = atoi(token);
    int i = 0;
    while ((token = strtok(NULL, " ")) != NULL) {    
        temp[i] = atoi(token);
        i++;
    }

    printf("thread_num: %d", thread_num);

}

/* Status Command */
void status() {

}

/* Run Command */
void run() {

}


int main(int argc, char** argv) {
    FILE* f;
    f = fopen("sample_in_banker.txt" , "r");

    printf("Opened File \n");
    available = malloc(sizeof(int) * num_resources);
    int resources[argc - 1];
    if (argc > 1) {
        for (int i = 1; i < argc; i++) { 
            resources[i] = atoi(argv[i]);
            available[i] = resources[i];
            num_resources += 1; 
        }
    } else { 
        exit(0);
    }

    max = *resources;

    printf("Wrote resources array \n");
    printf("num_resources: %d \n", num_resources);

    determine_t_arr_len(&f);

    printf("Determined thread count \n");
    printf("t_arr_len: %d \n", t_arr_len);
    needed = malloc(sizeof(int*)*t_arr_len);
    readFileToneededArrAlloc(&f, needed);
    printf("Read file to 2d array \n");
    allocated = malloc(sizeof(int*)*t_arr_len);

    for (int i = 0; i < t_arr_len; i++) { 
        allocated[i] = calloc(num_resources, sizeof(int));
        for (int j = 0; j < num_resources; j++) { 
            printf("%d ", needed[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < t_arr_len; i++) { 
        for (int j = 0; j < num_resources; j++) { 
            printf("%d ", allocated[i][j]);
        }
        printf("\n");
    }

    while (1) {
        char buf[neededC];                  
        
        fputs ("enter string: ", stdout);   /* prompt */
        while (fgets(buf, neededC, stdin)) {   // fgets
            char * prefix = strtok(buf, " \n");
            invoke_command(prefix, buf, resources);
            fputs ("enter string: ", stdout);
        }
    }
}