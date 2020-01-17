#include "../include/WS.h"

int WsHandler(IptPtr ipt, char* algorithm, int frames, int quantity, int maxReferences, int maxWorkingSet, statistics* stats)
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
    PQ Q1, Q2;
    InitializePQ(&Q1);
    InitializePQ(&Q2);
    while (currentReferences != 2*maxReferences) {

        if ((address = malloc(sizeof(IptAddress))) == NULL) {
            perror("malloc failed to allocate space");
            return -1;
        }

        if (switchFiles) {
            if (getline(&line, &len, file2) == -1) {
                printf("EOF\n");
                free(address);
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
                free(address);
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
            stats->writes ++;
        else
            stats->reads ++;

        runWS(ipt, address, &Q1, &Q2, maxWorkingSet, stats);
        currentReferences++;
        
        for (int i=0; i<ipt->currSize; i++) {
            if (ipt->array[i] != NULL)
                printf("IPT address: %8d  pid : %d , operation : %d\n", ipt->array[i]->page, ipt->array[i]->pid, ipt->array[i]->isDirty);
        }
        printf("\n\n");
    }

    free(line);
    
    printf("Statistics : \n\n \t Reads : %d \n\n \t Writes : %d \n\n \t PageFaults : %d \n\n \t pageRequests : %d \n\n", stats->reads, stats->writes, stats->pageFaults, stats->pageRequest);
    
    destroyPQ(&Q1, stats);
    destroyPQ(&Q2, stats);
    fclose(file1);
    fclose(file2);
    return 0;
}

int addressinWS(PQPtr Q, IptAddressPtr address)
{
    nodePtr temp = Q->head;
    for (int i=0; i<Q->currSize; i++) {
        if (!myCompare(temp->data, *address))
            return i;
    }

    return 0;
}

int runWS(IptPtr ipt, IptAddressPtr address, PQPtr Q1, PQPtr Q2, int maxWorkingSet, statistics* stats)
{
    PQPtr Q;
    if (address->pid == 1)
        Q = Q1;
    else
        Q = Q2;

    if (addressInIpt(ipt, address)) {            // if address is in inverted page table
        givePriority(Q, *address);
        if (address->isDirty)
            setWrite(ipt, address);
        free(address);
    }
    else {                                       // if address not in inverted page table   
        stats->pageFaults++;
        if (ipt->currSize < ipt->maxSize) {         //if ipt has free space
            insertAtFreeSpace(ipt, address);
            ipt->currSize++;
            if (Q->currSize <= maxWorkingSet)
                PushPQ(Q, *address);       
            else {
                IptAddressPtr t = PopPQ(Q);  //prepei na kane free ta data
                free(t);
                PushPQ(Q, *address);
            }
        }
        else {                                      //if ipt hasn't free space
            for (int i=0; i < ipt->maxSize; i++) {
                if(!addressinWS(Q, ipt->array[i])) {
                    free(ipt->array[i]);
                    ipt->array[i] = NULL;
                    insertAtFreeSpace(ipt, address);
                    if (Q->currSize <= maxWorkingSet)
                        PushPQ(Q, *address);       
                    else {
                        IptAddressPtr t = PopPQ(Q);
                        free(t);
                        PushPQ(Q, *address);
                    }
                    break;
                }
            }
        }
    }
    return 0;
}
