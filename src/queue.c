#include "../include/queue.h"

void InitializePQ(PQPtr Q)
{
    // Q = malloc(sizeof(PQ));
    Q->currSize = 0;
    Q->head = NULL;
    Q->tail = NULL;
}

int isPQEmpty(PQPtr Q)
{
    return Q->currSize;
}

int PushPQ(PQPtr Q, IptAddress data)
{
    nodePtr tempNode;

    if ((tempNode = malloc(sizeof(node))) == NULL) {
        perror("malloc failed to allocate space");
        return -1;
    }
    
    //mporei kai ta data na 8eloun malloc an einai void* px 8a dw

    tempNode->data = data;
    // tempNode->data.page++;
    // printf(" aaa : %d \n",tempNode->data.page);
    tempNode->next = NULL;

    if (Q->currSize) {
        Q->tail->next = tempNode;
        Q->tail = tempNode;
    }
    else {             //if queue empty
        Q->head = tempNode;
        Q->tail = tempNode;
    }
    Q->currSize++;

    return 0;
}

IptAddressPtr PopPQ(PQPtr Q)
{   
    nodePtr tempNode = Q->head;
    IptAddressPtr data = malloc(sizeof(IptAddress));
    data = &tempNode->data; //met at okanw free ara seg
    printf(" dd %d \n\n", Q->head->data.page);
    if (Q->currSize != 0 && Q->currSize != 1)    {
        printf("wtf \n");
        Q->head = Q->head->next;
}
    else {
        Q->head = NULL;
        Q->tail =NULL;
    }
    printf("BIKE\n");
    Q->currSize--;
    //an kanw malloc ta data 8a xreiastei ka ifree edw
    free(tempNode);
    return data;
}

int myCompare(IptAddress data1, IptAddress data2)
{
    if (data1.page == data2.page && data1.isDirty == data2.isDirty && data1.pid == data2.pid)
        return 0;
    else 
        return 1;
}


void givePriority(PQPtr Q, IptAddress data)
{
    printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
    nodePtr fastPtr, slowPtr;
    fastPtr = Q->head;
    if (fastPtr != NULL) {
        while (myCompare(fastPtr->data, data)) {
            slowPtr = fastPtr;
            fastPtr = fastPtr->next;
        }
        if (fastPtr == Q->head) 
            Q->head = Q->head->next;
        else
            slowPtr->next = fastPtr->next;
        Q->tail->next = fastPtr;
        Q->tail = fastPtr;
        fastPtr->next = NULL;
    }
}


//free queue