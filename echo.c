#include "headers.h"
#include "echo.h"

void echo(char *in)
{
    char out[4096];

    char prev = ' ', curr;

    int j=0;
    for(int i=0;i<strlen(in) - 4;i++)
    {
        curr = in[i+4];
        if ((curr == ' ' || curr == '\t' || curr == '\r') && (prev == ' ' || prev == '\t' || prev == '\r'))
        {
            continue;
        }
        else
        {
            out[j]=curr;
            j++;
            prev=curr;
        }
    }
    out[j]='\0';
    printf("%s\n", out);

    return;
}