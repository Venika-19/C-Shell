#include "headers.h"
#include "kjob.h"
#include "background.h"

struct proc_info * find_job(struct proc_info *curr, int job_no, int unded)
{
    if (curr->ded == 0)
    {
        if(unded == job_no)
        {
            return curr;
        }
        unded--;
    }

    if (curr->next != NULL)
    {
        return find_job(curr->next, job_no, unded);
    }
    else
    {
        return curr;
    }
    
}



void kjob(char * in)
{
    signal(SIGCHLD, if_signal);

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

    for(int i=0;i<strlen(val[1]);i++)
    {
        if (((int)val[1][i] > (int)'9' || (int)val[1][i] < (int)'0'))
        {
            fprintf(stderr, "kjob: invalid arguments: arguments must be integers\n");
            return;
        }
    }
    for (int i = 0; i < strlen(val[2]); i++)
    {
        if (((int)val[2][i] > (int)'9' || (int)val[2][i] < (int)'0'))
        {
            fprintf(stderr, "kjob: invalid arguments: arguments must be integers\n");
            return;
        }
    }

    int job_no, sig_no;
    
    job_no = atoi(val[1]);
    sig_no = atoi(val[2]);

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

    if(job_no>unded)
    {
        fprintf(stderr,"kjob: invalid job number\n");
    }
    
    curr = find_job(head ,job_no, unded);

    kill(curr->pid, sig_no);

    return;
}