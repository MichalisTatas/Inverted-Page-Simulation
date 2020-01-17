#include "../include/InvertedPageTable.h"
#include "../include/queue.h"

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

IptAddressPtr addressInIpt(IptPtr ipt, IptAddressPtr address)
{
    for (int i=0; i<ipt->maxSize; i++) {
        if (ipt->array[i] != NULL) {
           if (ipt->array[i]->isDirty == address->isDirty && ipt->array[i]->page == address->page && ipt->array[i]->pid == address->pid)
                return address;
        }
    }
    return NULL;
}

void insertAtFreeSpace(IptPtr ipt,IptAddressPtr address)
{
    for (int i=0; i<ipt->maxSize; i++) {
        if (ipt->array[i] == NULL) {
            ipt->array[i] = address;
            return;
        }
    }
}

void removeIpt(IptPtr ipt, IptAddressPtr address)
{
    for (int i=0; i<ipt->maxSize; i++) {
       if (ipt->array[i]->isDirty == address->isDirty && ipt->array[i]->page == address->page && ipt->array[i]->pid == address->pid) {
            // IptAddressPtr m = ipt->array[i];   
            free(ipt->array[i]); 
            ipt->array[i] = NULL;
            // free(m);
            ipt->currSize--;
       }
    }
}

void setWrite(IptPtr ipt, IptAddressPtr address)
{
    for (int i=0; i<ipt->currSize; i++) {
        if (!myCompare(*(ipt->array[i]), *address)) {
            ipt->array[i]->isDirty = true;
            break;
        } 
    }
}