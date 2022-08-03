#include "headers.h"
#include "bg.h"
#include "kjob.h"

void bg(char * in)
{
    char val[100][4096];
    int com_count = 0, j = 0;

    for (int i = 0; i < strlen(in); i++)
    {
        if (in[i] == ' ')
        {
            val[com_count][j] = '\0';
            com_count++;
            j = 0;
        }
        else
        {
            val[com_count][j] = in[i];
            j++;
        }
    }

    for (int i = 0; i < strlen(val[1]); i++)
    {
        if (((int)val[1][i] > (int)'9' || (int)val[1][i] < (int)'0'))
        {
            fprintf(stderr, "bg: invalid arguments: arguments must be integers: #%s#%d\n", val[1], i);
            return;
        }
    }

    int job_no = atoi(val[1]);

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

    if (job_no > unded)
    {
        fprintf(stderr, "bg: invalid job number\n");
    }

    curr = find_job(head, job_no, unded);

    kill(curr->pid,SIGCONT);

    return;
}