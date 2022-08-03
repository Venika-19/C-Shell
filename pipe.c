#include "headers.h"
#include "pipe.h"

#include "run.h"
#include "redirection.h"

char * piping(char *in, char * shell_dir, char * prompt_dir)
{
    char com[100][4096];
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<4096;j++)
        {
            com[i][j]='\0';
        }
    }

    char prev=' ';

    

    int j=0, com_count=0;
    for(int i=0;i<strlen(in);i++)
    {
        if ((in[i] == ' ' || in[i] == '\t' || in[i] == '\r') && (prev == ' ' || prev == '\t' || prev == '\r'))
        {
            continue;
        }
        else if(in[i]=='|')
        {
            if(com[com_count][j-1]==' ')
            {
                com[com_count][j-1]='\0';
            }
            else
            {
                com[com_count][j]='\0';
            }
            j=0;
            com_count++;
            prev=' ';
        }
        else
        {
            com[com_count][j]=in[i];
            j++;
            prev=in[i];
        }
    }

    com_count++;

    int pipe_fd[1024]={0};

    for(int i=0;i<com_count;i++)
    {
        pipe(pipe_fd + 2*i);

        if(i!=com_count-1)
        {
            if (dup2(pipe_fd[2 * i + 1], STDOUT_FILENO) < 0)
            {
                perror("Unable to duplicate file descriptor.");
                exit(1);
            }
            close(pipe_fd[2*i+1]);
        }
        else
        {
            if (dup2(stdoutCopy, STDOUT_FILENO) < 0)
            {
                perror("Unable to duplicate file descriptor.");
                exit(1);
            }
        }

        char curr_com[4096] = {};
        redir_io(com[i],curr_com);
        prompt_dir=run(curr_com, shell_dir, prompt_dir);

        if (dup2(pipe_fd[2*i], STDIN_FILENO) < 0)
        {
            perror("Unable to duplicate file descriptor.");
            exit(1);
        }

        close(pipe_fd[2*i]);
    }

    if (dup2(stdinCopy, STDIN_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        exit(1);
    }
    
    if (dup2(stdoutCopy, STDOUT_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        exit(1);
    }

    return prompt_dir;
}

