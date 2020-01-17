#include "../include/LRU.h"
#include "../include/queue.h"

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

//q uses copies of the structs

int runLRU(IptPtr ipt, IptAddressPtr address, PQPtr Q)
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
    
    if (addressInIpt(ipt, address) != NULL) {       // if address already in the ipt
        // printf("address with page ktl is already in %d %d %d \n",(*address)->page, (*address)->pid, (*address)->isDirty);
        givePriority(Q, *address);
        free(address);
        // ipt->currSize++;
    }
    else {
        if (ipt->currSize < ipt->maxSize) {        // if address not in ipt and ipt has free space
            insertAtFreeSpace(ipt, address);
            PushPQ(Q, *address);
            ipt->currSize++;
        }
        else {                                     // if address not in ipt and ipt has no free space
            // printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaA\n");
            IptAddressPtr n = PopPQ(Q);
            removeIpt(ipt, n);
            free(n);
            // printf("node to go : %d \n", n->page);
            insertAtFreeSpace(ipt, address);
            PushPQ(Q, *address);
            ipt->currSize++;
        }
    }
    // free(address);
    return 0;
}