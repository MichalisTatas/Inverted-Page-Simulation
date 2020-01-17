#ifndef LRU
#define LRU

#include "InvertedPageTable.h"
#include "queue.h"

int runLRU(IptPtr ipt, IptAddressPtr* address, PQPtr Q);

#endif