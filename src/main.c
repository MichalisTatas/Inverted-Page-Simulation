#include <stdlib.h>
#include <string.h>

#include "../include/Simulator.h"
#include "../include/defines.h"

int main(int argc, char* argv[]) {

    if(argc < 7) {
        printf("Correct usage: \n");
        return -1;
    }

    char *algorithm;
    int quantum = 0;
    int frames = 0;
    int maxReferences = -1;

    for(int i=0; i < argc; i++) {
        if(!strcmp(argv[i], "-f")) {
            frames = atoi(argv[++i]);
        }
        else if(!strcmp(argv[i], "-q")) {
            quantum = atoi(argv[++i]);
        }
        else if(!strcmp(argv[i], "-m")) {
            maxReferences = atoi(argv[++i]);
        }
        else if(!strcmp(argv[i], "-a")) {
            i++;    // argv[++i] doesn't seem to work
            if((algorithm = malloc(sizeof(argv[i]))) == NULL) {
                perror("malloc failed");
                return -1;
            }
            strcpy(algorithm, argv[i]);
        }
    }

    Simulator_run(algorithm, frames, quantum, maxReferences);

    free(algorithm);

    return 0;
}