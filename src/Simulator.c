#include <stdlib.h>
#include <string.h>

#include "../include/Simulator.h"

int Simulator_run(char* algorithm, int frames, int quantum, int maxReferences) {

    int currReferences = 0;
    int currQuantum = 0;
    bool toggleFiles = false;
    FILE *filePtr1 = NULL, *filePtr2 = NULL;
    AddressPtr address = NULL;
    InvertedPageTablePtr invertedPageTable = NULL;

    if((invertedPageTable = malloc(sizeof(InvertedPageTable))) == NULL) {
        perror("malloc failed");
        return -1;
    }
    invertedPageTable->size = frames;
    if((invertedPageTable->table = malloc(frames*sizeof(AddressPtr))) == NULL) {
        perror("malloc failed");
        return -1;
    }

    filePtr1 = fopen("./Assets/bzip.trace", "r");
    filePtr2 = fopen("./Assets/gcc.trace", "r");

    if(filePtr1 == NULL || filePtr2 == NULL) {
        perror("fopen failed");
        return -1;
    }

    while((address = Simulator_getAddress(filePtr1, filePtr2, &currReferences, maxReferences, &currQuantum, quantum, &toggleFiles)) != NULL) {
        printf("%ld, %10ld, %d\n", address->pid, address->pageNumber, address->dirty);
        free(address);
    }

    fclose(filePtr1);
    fclose(filePtr2);

    free(invertedPageTable->table);
    free(invertedPageTable);

    return 0;
}

Address *Simulator_getAddress(FILE *filePtr1, FILE *filePtr2, int *currReferences, int maxReferences, int *currQuantumm, int quantum, bool *togglefiles) {

    char* line = NULL;
    size_t len = 0;
    AddressPtr address = NULL;

    if(maxReferences != -1) {
        if((*currReferences)++ == 2*maxReferences) {
            return NULL;
        }
    }

    if((address = malloc(sizeof(Address))) == NULL) {
        perror("malloc failed");
        return NULL;
    }

    if(*togglefiles) {
        if(getline(&line, &len, filePtr2) == -1) {
            return NULL;
        }
        if(++(*currQuantumm) == quantum) {
            *currQuantumm = 0;
            *togglefiles = false;
        }
        address->pid = 2;
    }
    else {
        if(getline(&line, &len, filePtr1) == -1) {
            return NULL;
        }
        if(++(*currQuantumm) == quantum) {
            *currQuantumm = 0;
            *togglefiles = true;
        }
        address->pid = 1;
    }

    Address_getInfo(&address, line);

    free(line);

    return address;
}