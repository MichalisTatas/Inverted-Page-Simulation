#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../include/Simulator.h"
#include "../include/InvertedPageTable.h"
#include "../include/queue.h"
#include "../include/WS.h"
#include "../include/LRU.h"

int simulatorRun(char* algorithm, int frames, int quantity, int maxReferences, int maxWorkingSet)
{
    IptPtr ipt = NULL;
    statistics* stats = malloc(sizeof(statistics));
    stats->reads = 0;
    stats->writes = 0;
    stats->pageRequest = 0;
    stats->pageFaults = 0;

    if ((ipt = malloc(sizeof(Ipt))) == NULL) {
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

    if (!strcmp(algorithm, "LRU") || !strcmp(algorithm, "lru"))
        LruHandler(ipt, algorithm, frames, quantity, maxReferences, stats);
    else
        WsHandler(ipt, algorithm, frames, quantity, maxReferences, maxWorkingSet, stats);

    for (int i=0; i<ipt->maxSize; i++)
        if(ipt->array[i] != NULL)
            free(ipt->array[i]);               //do i need to check if null?
    
    free(stats);
    free(ipt->array);
    free(ipt);
    return 0;
}