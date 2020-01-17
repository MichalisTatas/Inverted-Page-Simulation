#include "../include/InvertedPageTable.h"

void fillAddress(IptAddressPtr address, char* line)
{
    char* hexNum;
    char* operation;

    hexNum = strtok(line, " ");
    operation = strtok(NULL, "\n");
    address->page = strtoul(hexNum, NULL, 16) / FRAME_SIZE;

    if (!strcmp(operation, "R"))
        address->isDirty = false;
    else
        address->isDirty = true;
}