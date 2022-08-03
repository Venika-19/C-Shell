#include "headers.h"
#include "bg.h"
#include "kjob.h"

void fg(char * in)
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
            fprintf(stderr, "fg: invalid arguments: arguments must be integers: #%s#%d\n", val[1], i);
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
        fprintf(stderr, "fg: invalid job number\n");
    }

    curr = find_job(head, job_no, unded);

    int main_pid=getpgrp();

    curr->ded=1;
    
    pid_fore=curr->pid;

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    tcsetpgrp(STDIN_FILENO, curr->pid);

    kill(curr->pid,SIGCONT);
    int status;
    waitpid(curr->pid,&status,WUNTRACED);

    tcsetpgrp(STDIN_FILENO,main_pid);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    if (WIFSTOPPED(status))
    {
        curr->ded=0;
    }

    pid_fore = -1;

    return;
}