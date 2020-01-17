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

typedef struct statistics {
    int reads;
    int writes;
    int pageFaults;
    int pageRequest;
} statistics;

void fillAddress(IptAddressPtr address, char* line);
IptAddressPtr addressInIpt(IptPtr ipt, IptAddressPtr address);
void insertAtFreeSpace(IptPtr ipt,IptAddressPtr address);
void removeIpt(IptPtr ipt, IptAddressPtr address);
void setWrite(IptPtr ipt, IptAddressPtr address);

#endif