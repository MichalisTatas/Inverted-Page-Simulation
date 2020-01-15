#ifndef ADDRESS_H
#define ADDRESS_H

#include <stdio.h>
#include <stdbool.h>


typedef address* addressPtr;

typedef struct address {
    int pid;
    int page;
    bool isDirty;
} address;

#endif    