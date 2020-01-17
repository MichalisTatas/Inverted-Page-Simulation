#ifndef QUEUE
#define QUEUE

#include "InvertedPageTable.h"

typedef struct node {
    IptAddress data;
    struct node* next;
} node;
typedef node* nodePtr;

typedef struct PriorityQueue {
    int currSize;
    // size_t dataSize;
    nodePtr head;
    nodePtr tail;
} PQ;
typedef PQ* PQPtr;

void InitializePQ(PQPtr Q);
int isPQEmpty(PQPtr Q);
int PushPQ(PQPtr Q, IptAddress data);
void destroyPQ(PQPtr Q, statistics* stats);
IptAddressPtr PopPQ();
void givePriority(PQPtr Q, IptAddress data);
int myCompare(IptAddress data1, IptAddress data2);


#endif