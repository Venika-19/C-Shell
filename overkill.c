#include "headers.h"
#include "overkill.h"
#include "kjob.h"
#include "background.h"

void overkill()
{
    signal(SIGCHLD, if_signal);
    struct proc_info *curr = head;
    int unded = 0;

    while (curr != NULL)
    {
        if (curr->ded == 0)
        {
            unded++;
        }
        curr = curr->next;
    }

    // printf("unded: %d\n", unded);
    for(unded;unded>0;unded--)
    {
        struct proc_info * curr = find_job(head,1,unded);
        // printf("unded: %d, curr_pid: %d\n", unded, curr->pid);
        kill(curr->pid,9);
    }

    return;
}