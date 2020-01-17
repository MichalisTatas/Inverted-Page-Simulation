#include "../include/LRU.h"
#include "../include/queue.h"

IptAddressPtr addressInIpt(IptPtr ipt, IptAddressPtr* address)
{
    for (int i=0; i<ipt->maxSize; i++) {
        if (ipt->array[i] != NULL) {
           if (ipt->array[i]->isDirty == (*address)->isDirty && ipt->array[i]->page == (*address)->page && ipt->array[i]->pid == (*address)->pid)
                return *address;
        }
    }
    return NULL;
}

void insertAtFreeSpace(IptPtr ipt,IptAddressPtr* address)
{
    for (int i=0; i<ipt->maxSize; i++) {
        if (ipt->array[i] == NULL) {
            ipt->array[i] = *address;
            return;
        }
    }
}

//q uses copies of the structs

int runLRU(IptPtr ipt, IptAddressPtr* address, PQPtr Q)
{
    
    // for (int i=0; i<4; i++) {
    //     PushPQ(&Q, i);
    // }

    // givePriority(&Q, 2);
    // for (int i=0; i<4; i++) {
    //     printf("data : %d \n",PopPQ(&Q));
    // }
    // printf("\n");

    // PushPQ(&Q, *address);
    // printf(" AAAA : %d %d %d\n", address->page, address->isDirty, address->pid);
    // IptAddress m = PopPQ(&Q);
    // printf(" BBBB : %d %d %d\n", m.page, m.isDirty, m.pid);
    // printf(" AAAA : %d %d %d\n\n\n", address->page, address->isDirty, address->pid);
    
    if (addressInIpt(ipt, address) != NULL) {
        printf("SEG>\n");
        givePriority(Q, **address);
    }
    else {
        printf("gt eimai edw \n");
        if (ipt->currSize < ipt->maxSize) {
            insertAtFreeSpace(ipt, address);
            PushPQ(Q, **address);
        }
    }

    printf("TATTATA : %d \n", Q->currSize);

    
    //     if hasFreeSpace()
    //         ins
    //     else 
    //         lru poulo kai meta ins
    // }

    // if (addressInIpt(ipt, address) != NULL) {

    // }

    return 0;
}