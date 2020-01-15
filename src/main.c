#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Simulator.h"

int main(int argc, char* argv[])
{
    if (argc < 7) {
        printf("need more information");
    }
    char* algorithm;
    int quantity, maxReferences, frames;
    for (int i=0; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            frames = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-q") == 0) {
            quantity = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-m") == 0) {
            maxReferences = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-a") == 0) {
            i++;    // malloc(sizeof(argv[++i])) doesn't seem to work
            if ((algorithm = malloc(sizeof(argv[i]))) == NULL) {
                perror("malloc failed");
                return -1;
            }
            strcpy(algorithm, argv[i]);
        }
    }

    simulatorRun(algorithm, frames, quantity, maxReferences);

    free(algorithm);
    return 0;
}