#ifndef WS
#define WS

#include "InvertedPageTable.h"
#include "queue.h"

int WsHandler(IptPtr ipt, char* algorithm, int frames, int quantity, int maxReferences, int maxWorkingSet, statistics* stats);
int runWS(IptPtr ipt, IptAddressPtr address, PQPtr Q1, PQPtr Q2, int maxWorkingSet, statistics* stats);
int addressinWS(PQPtr Q, IptAddressPtr address);

#endif