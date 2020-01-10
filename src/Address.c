#include <stdlib.h>
#include <string.h>
#include "../include/Address.h"

int Address_getInfo(AddressPtr *address, char* info) {

    char *token, *operation;

    token = strtok(info, " ");
    operation = strtok(NULL, "\n");

    (*address)->pageNumber = strtoul(token, NULL, 16);

    if(!strcmp(operation, "R")) {
        (*address)->dirty = true;
    }
    else {
        (*address)->dirty = false;
    }

    // printf("%s\t%s\n", token, operation);
    // printf("%ld\n", strtoul(token, NULL, 16));

    return 0;
}