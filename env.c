#include "headers.h"
#include "env.h"

void mysetenv(char *in)
{
    char val[100][4096];
    int com_count=0, j=0;

    for(int i=0;i<strlen(in);i++)
    {
        if(in[i]==' ')
        {
            val[com_count][j]='\0';
            com_count++;
            j=0;
        }
        else
        {
            val[com_count][j]=in[i];
            j++;
        }  
    }

    if(com_count<1 || com_count>2)
    {
        fprintf(stderr,"setenv: invalid number of arguments\n");
        return;
    }

    if(setenv(val[1],val[2],1)<0)
    {
        perror("setenv");
    }

    return;
}

void myunsetenv(char *in)
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

    if (com_count!=1)
    {
        fprintf(stderr, "unsetenv: invalid number of arguments %d\n", com_count);
        return;
    }

    if (unsetenv(val[1]) < 0)
    {
        perror("unsetenv");
    }

    return;
}