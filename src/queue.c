#include "../include/queue.h"

void InitializePQ(PQPtr Q)
{
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
    

    tempNode->data = data;
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

    data->isDirty = tempNode->data.isDirty;
    data->page = tempNode->data.page;
    data->pid = tempNode->data.pid;

    if (Q->currSize != 0) {
        if(Q->currSize == 1) {
            Q->head = NULL;
            Q->tail =NULL;
        }
        else {
            Q->head = Q->head->next;
        }
    }
    Q->currSize--;

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
    
    nodePtr fastPtr, slowPtr;
    fastPtr = Q->head;
    if (fastPtr != NULL) {
        while (myCompare(fastPtr->data, data) && fastPtr->next != NULL) {
            slowPtr = fastPtr;
            fastPtr = fastPtr->next;
        }
        if (fastPtr == Q->head) 
            Q->head = Q->head->next;
        else if (fastPtr->next == NULL)  //it is already in tail
            return;
        else
            slowPtr->next = fastPtr->next;
        Q->tail->next = fastPtr;
        Q->tail = fastPtr;
        fastPtr->next = NULL;   
    }
}


void destroyPQ(PQPtr Q, statistics* stats)
{
    IptAddressPtr temp;
    for (int i=0; i<Q->currSize + 10; i++) {
        temp = PopPQ(Q);
        if (temp->isDirty)
            stats->writes++;
        free(temp);
    }
}