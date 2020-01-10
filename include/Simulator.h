#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "./InvertedPageTable.h"
#define PAGE_SIZE 4096


int Simulator_run(char* algorithm, int frames, int quantum, int maxReferences);

Address *Simulator_getAddress(FILE *filePtr1, FILE *filePtr2, int *currReferences, int maxReferences, int *currQuantum, int quantum, bool *togglefiles);

#endif