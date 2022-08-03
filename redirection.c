#include "headers.h"
#include "redirection.h"
#include "pwd.h"

void redir_io(char *in, char *concat_com)
{
    char com[100][4096];

    for(int i=0;i<100;i++)
    {
        for(int j=0;j<4096;j++)
        {
            com[i][j]='\0';
        }
    }

    int space_flag=1, com_count=0, j=0;

    // printf("in: %s", in);

    for(int i=0;i<strlen(in);i++)
    {
        if (space_flag == 1 && (in[i] == ' ' || in[i] == '\t' || in[i] == '\r'))
        {
            continue;
        }
        else if (in[i] == ' ' || in[i] == '\t' || in[i] == '\r')
        {
            com[com_count][j]='\0';
            space_flag=1;
            com_count++;
            j=0;
        }
        else
        {
            space_flag=0;
            com[com_count][j]=in[i];
            j++;
        }
    }

    char actual[100][4096];
    char *prev = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    for(int i=0;i<100;i++)
    {
        for(int k=0;k<4096;k++)
        {
            actual[i][k]='\0';
        }
    }


    int com_s=0;
    int fd_count=0;

    // for(int i=0;i<=com_count;i++)
    // {
    //     printf("com%d: %s#\n", i, com[i]);
    // }

    for(int i=0;i<=com_count;i++)
    {
        // printf("com%d: %s#\n", i, com[i]);
        if(comp(prev,">",strlen(prev))==0)
        {
            // printf("1\n\n\n\n\n");
            char filepath[4096]={};
            for(int p=0;p<strlen(com[i]);p++)
            {
                filepath[p]=com[i][p];
            }

            int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("Unable to duplicate file descriptor.");
                exit(1);
            }
            close(fd);
        }
        else if(comp(prev,">>",strlen(prev))==0)
        {
            // printf("2\n\n\n\n\n");
            char filepath[4096] = {};
            for (int p = 0; p < strlen(com[i]); p++)
            {
                filepath[p] = com[i][p];
            }

            int fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("Unable to duplicate file descriptor.");
                exit(1);
            }
            close(fd);
        }
        else if(comp(prev,"<",strlen(prev))==0)
        {
            // printf("3\n\n\n\n\n");
            char filepath[4096] = {};
            for (int p = 0; p < strlen(com[i]); p++)
            {
                filepath[p] = com[i][p];
            }

            int fd = open(filepath, O_RDONLY);
            if(fd<0)
            {
                perror("redir_io");
            }
            if (dup2(fd, STDIN_FILENO) < 0)
            {
                perror("Unable to duplicate file descriptor.");
                exit(1);
            }
            close(fd);
        }
        else if (!(comp(com[i], "<", strlen(com[i])) == 0 || comp(com[i], ">", strlen(com[i])) == 0 || comp(com[i], ">>", strlen(com[i])) == 0))
        {
            strcpy(actual[com_s], com[i]);
            com_s++;
        }
        prev=com[i];
        // printf("prev%d: %s\n", i, prev);
    }

    // printf("com_s %d\n", com_s);

    for(int i=0;i<com_s;i++)
    {
        strcat(concat_com,actual[i]);
        strcat(concat_com," ");
        // printf("concat_com %s#actual: %s#\n", concat_com, actual[i]);
    }
    
    if(strlen(concat_com)>1)
    {
        concat_com[strlen(concat_com)-1]='\0';
    }

    return;
}
