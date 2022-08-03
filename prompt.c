#include "headers.h"
#include "prompt.h"

struct utsname unameStuff;

int comp2(char *a, char *b, int len)
{
    if (strlen(a) < len || strlen(b) < len)
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            if (a[i] != b[i])
            {
                return 1;
            }
        }
        return 0;
    }
}

char *pwd2(char *shell_dir)
{
    int SDlen = strlen(shell_dir);
    char *pwd = malloc(4096 * sizeof(char));
    getcwd(pwd, 4096);
 
    if (comp2(shell_dir, pwd, SDlen) == 0)
    {
        char *rwd = malloc((strlen(pwd) - SDlen + 10) * sizeof(char));
        rwd[0] = '~';
        for (int i = 1; i < strlen(pwd) - SDlen; i++)
        {
            rwd[i] = pwd[i + SDlen];
        }
        rwd[strlen(pwd)-SDlen]='\0';
        return rwd;
    }
    else
    {
        return pwd;
    }
}

void prompt(char *pwd) {

    int unameRet = uname(&unameStuff);
    char * login = (char *)malloc(64 * sizeof(char));
    login = getlogin();
    // char *pwd = pwd2(shell_dir);
    if(unameRet!=0)
    {
    	fprintf(stderr, "Failed to read system and user names");
    	exit(1);
    }

    if(pwd[0]=='\0')
    {
        pwd[0]='~';
        pwd[1]='\0';
    }

    printf("<%s@%s:%s>", login, unameStuff.nodename, pwd);
}

// int main(){
// 	prompt();
// }
