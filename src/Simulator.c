#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../include/Simulator.h"
#include "../include/InvertedPageTable.h"
#include "../include/queue.h"
#include "../include/WS.h"
#include "../include/LRU.h"

int simulatorRun(char* algorithm, int frames, int quantity, int maxReferences)
{
    int currentReferences = 0 , currentQuantity = 0;
    bool switchFiles;
    int (*replacementAlgo)();
    IptPtr ipt = NULL;

    if ((ipt = malloc(sizeof(IptPtr))) == NULL) {
        perror("malloc failed to allocate space");
        return -1;
    }
    ipt->currSize = 0;
    ipt->maxSize = frames;

    if ((ipt->array= malloc(frames*sizeof(IptAddressPtr))) == NULL) {
        perror("malloc failed to allocate space");
        return -1;
    }

    for (int i = 0; i < ipt->maxSize; i++)
        ipt->array[i] = NULL;

    FILE* file1 = fopen("./Assets/bzip.trace", "r");
    FILE* file2 = fopen("./Assets/gcc.trace", "r");

    if (file1 == NULL || file2 == NULL) {
        perror("failed to open file");
        return -1;
    }

    if (!strcmp(algorithm, "LRU") || !strcmp(algorithm, "lru"))
        replacementAlgo = runLRU;
    else if (!strcmp(algorithm, "WS") || !strcmp(algorithm, "ws"))
        replacementAlgo = runWS;
    else {
        printf("wrong replacement algorithm");
        return -1;
    }

    char* line;
    size_t len;
    IptAddressPtr address;
    PQ Q;
    InitializePQ(&Q);
    while (currentReferences != 2*maxReferences) {

        if ((address = malloc(sizeof(IptAddressPtr))) == NULL) {
            perror("malloc failed to allocate space");
            return -1;
        }

        if (switchFiles) {
            if (getline(&line, &len, file2) == -1)
                return -1;
            if (++currentQuantity == quantity) {
                currentQuantity = 0;
                switchFiles = false;
            }
            address->pid = 2;
        }
        else {
            if (getline(&line, &len, file1) == -1)
                return -1;
            if (++currentQuantity == quantity) {
                currentQuantity = 0;
                switchFiles = true;
            }
            address->pid = 1;
        }
        fillAddress(address, line);

        replacementAlgo(ipt, &address, &Q);
        currentReferences++;
    }
    // free(address); //xreoazetai?

    for (int i=0; i<ipt->maxSize; i++) {
        if (ipt->array[i] != NULL)
            printf("FF : %d \n", ipt->array[i]->page);
    }

    IptAddressPtr temp = malloc(sizeof(IptAddress));
    for (int i=0; i<Q.currSize; i++) {
        printf("gamwe to xristo \n");
        temp = PopPQ(&Q);
        printf("GG   : %d \n", temp->page);
    }

    free(line);

    fclose(file1);
    fclose(file2);

    for (int i=0; i<ipt->maxSize; i++)
        free(ipt->array[i]);               //do i need to check if null?

    free(ipt->array);
    free(ipt);
    return 0;
}