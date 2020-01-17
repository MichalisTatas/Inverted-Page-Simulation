#ifndef INVERTEDPAGETABLE_H
#define INVERTEDPAGETABLE_H

#define FRAME_SIZE 4096
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct IptAddress {
    int pid;
    int page;
    bool isDirty;
} IptAddress;
typedef IptAddress* IptAddressPtr;

typedef struct invertedPageTable {
    int currSize;
    size_t maxSize;
    IptAddressPtr* array; 
} Ipt;
typedef Ipt* IptPtr;


void fillAddress(IptAddressPtr address, char* line);
// insertFreeIptSpace();
#endif