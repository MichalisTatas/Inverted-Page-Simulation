#ifndef LRU
#define LRU

#include "InvertedPageTable.h"
#include "queue.h"

int LruHandler(IptPtr ipt, char* algorithm, int frames, int quantity, int maxReferences, statistics* stats);
int runLRU(IptPtr ipt, IptAddressPtr address, PQPtr Q, statistics* stats);

#endif