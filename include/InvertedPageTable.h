#ifndef INVERTEDPAGETABLE_H
#define INVERTEDPAGETABLE_H

#include <stdbool.h>
#include <stdlib.h>

typedef IptAddress* IptAddressPtr;

typedef struct IptAddress {
    int pid;
    int page;
    bool isDirty;
} IptAddress;

typedef Ipt* IptPtr;

typedef struct invertedPageTable {
    size_t size;
    IptAddressPtr* array; 
} Ipt;


void fixAddress(IptAddressPtr address, char* line);
#endif