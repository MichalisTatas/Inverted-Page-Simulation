#include "../include/LRU.h"
#include "../include/queue.h"

int LruHandler(IptPtr ipt, char* algorithm, int frames, int quantity, int maxReferences, statistics* stats)
{
    int currentReferences = 0 , currentQuantity = 0;
    bool switchFiles  = false;
    FILE* file1 = fopen("./Assets/bzip.trace", "r");
    FILE* file2 = fopen("./Assets/gcc.trace", "r");

    if (file1 == NULL || file2 == NULL) {
        perror("failed to open file");
        return -1;
    }

    char* line = NULL;
    size_t len = 0;
    IptAddressPtr address;
    PQ Q;
    InitializePQ(&Q);
    while (currentReferences != 2*maxReferences) {

        if ((address = malloc(sizeof(IptAddress))) == NULL) {
            perror("malloc failed to allocate space");
            return -1;
        }

        if (switchFiles) {
            if (getline(&line, &len, file2) == -1) {
                printf("EOF\n");
                return -1;
            }
            if (++currentQuantity == quantity) {
                currentQuantity = 0;
                switchFiles = false;
            }
            address->pid = 2;
        }
        else {
            if (getline(&line, &len, file1) == -1) {
                printf("EOF\n");
                return -1;
            }
            if (++currentQuantity == quantity) {
                currentQuantity = 0;
                switchFiles = true;
            }
            address->pid = 1;
        }
        fillAddress(address, line);

        stats->pageRequest++;
        if (address->isDirty)
            stats->writes++;
        else
            stats->reads++;

        runLRU(ipt, address, &Q, stats);
        currentReferences++;
        
        for (int i=0; i<ipt->currSize; i++) {
            if (ipt->array[i] != NULL)
                printf("IPT address: %8d  pid : %d , operation : %d\n", ipt->array[i]->page, ipt->array[i]->pid, ipt->array[i]->isDirty);
        }
        printf("\n\n");
        
    }
        free(line);
        // free(address);

    destroyPQ(&Q);
    printf("Statistics : \n\n \t Reads : %d \n\n \t Writes : %d \n\n \t PageFaults : %d \n\n \t pageRequests : %d \n\n", stats->reads, stats->writes, stats->pageFaults, stats->pageRequest);

    fclose(file1);
    fclose(file2);
    return 0;
}

int runLRU(IptPtr ipt, IptAddressPtr address, PQPtr Q, statistics* stats)
{
    if (addressInIpt(ipt, address) != NULL) {       // if address already in the ipt
        givePriority(Q, *address);
        if (address->isDirty)
            setWrite(ipt, address);
        free(address);
    }
    else {
        stats->pageFaults++;
        if (ipt->currSize < ipt->maxSize) {        // if address not in ipt and ipt has free space
            insertAtFreeSpace(ipt, address);
            PushPQ(Q, *address);
            ipt->currSize++;
        }
        else {                                     // if address not in ipt and ipt has no free space
            IptAddressPtr n = PopPQ(Q);
            removeIpt(ipt, n);
            free(n);
            insertAtFreeSpace(ipt, address);
            PushPQ(Q, *address);
            ipt->currSize++;
        }
    }
    return 0;
}