// Trump wishes he could create these

#include "headers.h"
#include "jobs.h"
#include "pwd.h"

void print_jobs(struct proc_info *curr, int unded)
{
    if(curr->ded==0)
    {
        unded--;
    }

    if(curr->next!=NULL)
    {
        print_jobs(curr->next,unded);
    }

    if(curr->ded==0)
    {
        //get info

        char pid[4096];
        sprintf(pid, "%d", curr->pid);

        char stat_path[4096];
        strcat(stat_path, "/proc/");
        strcat(stat_path, pid);
        strcat(stat_path, "/stat");

        FILE *fd_stat = fopen(stat_path, "r");

        char stats[52][128];
        for (int p = 0; p < 52; p++)
        {
            for (int q = 0; q < 128; q++)
            {
                stats[p][q] = '\0';
            }
        }
        // char state[5]="";
        // long unsigned int memory;

        // fprintf(stderr,"stat_path: %s\n", stat_path);

        fscanf(fd_stat, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6], stats[7], stats[8], stats[9], stats[10], stats[11], stats[12], stats[13], stats[14], stats[15], stats[16], stats[17], stats[18], stats[19], stats[20], stats[21], stats[22], stats[23], stats[24], stats[25], stats[26], stats[27], stats[28], stats[29], stats[30], stats[31], stats[32], stats[33], stats[34], stats[35], stats[36], stats[37], stats[38], stats[39], stats[40], stats[41], stats[42], stats[43], stats[44], stats[45], stats[46], stats[47], stats[48], stats[49], stats[50], stats[51]);
        //    1   2  3   4   5   6   7   8   9   10   11   12   13   14   15   16   17   18   19   20   21    22  23   24   25   26   27   28   29   30   31   32   33   34   35   36   37  38  39  40  41    42   43   44   45   46   47   48   49   50   51  52
        fclose(fd_stat);


        char status[4096]="";
        if(comp(stats[2],"T",1)==0)
        {
            strcpy(status,"Stopped");
        }
        else
        {
            strcpy(status,"Running");
        }

        char command[4096]="";

        for(int i=0;i<=curr->arg_count;i++)
        {
            strcat(command,curr->args[i]);
            strcat(command," ");
        }

        //print info
    
        printf("[%d] %s %s[%d]\n", unded+1, status, command, curr->pid);
    }
    return;
}


void jobs()
{
    struct proc_info *curr = head;

    int unded=0;

    while(curr!=NULL && head->size!=0)
    {
        if(curr->ded==0)
        {
            unded++;
        }
        curr=curr->next;
    }

    if(unded>0)
    {
        print_jobs(head,unded);
    }

    return;
}