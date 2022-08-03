#include "headers.h"
#include "pinfo.h"

void pinfo(char *in)
{
    // proc/pid/stat    and   proc/pid/exe

    int j=0;
    char pid[128];
    for(int i=0;i<128;i++)
    {
        pid[i]='\0';
    }
    for(int i=6;i<strlen(in);i++)
    {
        if(in[i]!=' ')
        {
            pid[j]=in[i];
            j++;
        }
        else
        {
            break;
        }
    }
    
    if(pid[0]=='\0')
    {
        int pid_int = getpid();
        sprintf(pid, "%d", pid_int);
    }

    char stat_path[4096], exe_path[4096];
    for(int i=0;i<4096;i++)
    {
        stat_path[i]='\0';
        exe_path[i]='\0';
    }

    // printf("\nflag1\n\n");

    strcat(stat_path, "/proc/");
    strcat(stat_path, pid);
    strcat(stat_path, "/stat");
    strcat(exe_path, "/proc/");
    strcat(exe_path, pid);
    strcat(exe_path, "/exe");

    // printf("\nflag2\n\n");

    int exit_flag=0;

    FILE *fd_stat = fopen(stat_path, "r");
    FILE *fd_exe = fopen(exe_path, "r");
    if(!fd_stat||!fd_exe)
    {
        fprintf(stderr,"pinfo: Invalid pid\n");
        return;
    }

    // printf("\nflag3\n\n");

    char stats[52][128];
    for(int p=0;p<52;p++)
    {
        for(int q=0;q<128;q++)
        {
            stats[p][q]='\0';
        }
    }
    // char state[5]="";
    // long unsigned int memory;

    fscanf(fd_stat, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6], stats[7], stats[8], stats[9], stats[10], stats[11], stats[12], stats[13], stats[14], stats[15], stats[16], stats[17], stats[18], stats[19], stats[20], stats[21], stats[22], stats[23], stats[24], stats[25], stats[26], stats[27], stats[28], stats[29], stats[30], stats[31], stats[32], stats[33], stats[34], stats[35], stats[36], stats[37], stats[38], stats[39], stats[40], stats[41], stats[42], stats[43], stats[44], stats[45], stats[46], stats[47], stats[48], stats[49], stats[50], stats[51]);
    //    1   2  3   4   5   6   7   8   9   10   11   12   13   14   15   16   17   18   19   20   21    22  23   24   25   26   27   28   29   30   31   32   33   34   35   36   37  38  39  40  41    42   43   44   45   46   47   48   49   50   51  52
    fclose(fd_stat);
   
    // char *mem_info = read_file(stat_path,18);   
    printf("pid -- %s\n",pid);
    printf("Process Status -- %s\n", stats[2]);
    printf("memory -- %s\n", stats[22]);
    // printf("memstr -- %s\n", mem_info);



    char execute_path[4096]={'\0'};

    if(readlink(exe_path,execute_path,4096)<0)
    {
        perror("pinfo");
    }
    else
    {
        printf("Executable Path -- %s\n", execute_path);
    }


    return;
}