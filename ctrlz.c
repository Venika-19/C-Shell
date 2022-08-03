#include "headers.h"
#include "ctrlz.h"
#include "background.h"

void ctrlc(int signum)
{
    if(pid_fore!=-1)
    {
        kill(pid_fore,SIGINT);
    }
}

void ctrlz(int signum)
{
    //pid_fore

    if(pid_fore!=-1)
    {
        kill(pid_fore,SIGTSTP);
    }

    return;
}