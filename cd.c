#include "headers.h"
#include "cd.h"

void cd(char *in, char *shell_dir)
{
    char *pwd = malloc(4096 * sizeof(char));
    getcwd(pwd,4096);

    char *out = malloc(strlen(in) * sizeof(char));
    char prev = ' ', curr;

    int j = 0;
    for (int i = 0; i < strlen(in) - 2; i++)
    {
        curr = in[i + 2];
        if (curr == ' ' && prev == ' ')
        {
            continue;
        }
        else
        {
            out[j] = curr;
            j++;
            prev = curr;
        }
    }

    out[j]='\0';

    if(out[0] == '~')
    {
        if(strlen(out)>1)
        {
            char *out2 = malloc(4096);
            strcat(out2,shell_dir);

            for (int i = 1; i < strlen(out);i++)
            {
                out2[strlen(shell_dir)-1+i]=out[i];
            }

            out2[strlen(out)+strlen(shell_dir)]='\0';

            if (chdir(out2) != 0)
            {
                // printf("failed\n");
                perror("cd");
            }
        }


        if(strlen(out)==1)
        {
            if (chdir(shell_dir) != 0)
            {
                // printf("failed\n");
                perror("cd");
            }
        }
    }

    else if(out[0]=='-')
    {
        if(previous[0]=='\0')
        {
            fprintf(stderr, "cd: previous working directory undefined\n");
        }
        else
        {
            if (chdir(previous) != 0)
            {
                perror("cd");
                return;
            }
            printf("%s\n", previous);
        }
        
    }

    else if(strlen(in)==2)
    {
        if (chdir(shell_dir) != 0)
        {
            // printf("failed\n");
            perror("cd");
        }
    }

    else if(out[0]!='/')
    {
        char *rel_path = malloc((strlen(out)+strlen(pwd)+5) * sizeof(char));

        rel_path[strlen(out)+strlen(pwd)+4]='\0';

        for(int i=0;i<strlen(pwd);i++)
        {
            rel_path[i]=pwd[i];
        }
        int pwdl = strlen(pwd);
        rel_path[pwdl]='/';
        for(int i=0;i<strlen(out);i++)
        {
            rel_path[i+pwdl+1]=out[i];
        }
        if(rel_path[strlen(rel_path)-1]==' ')
        {
            rel_path[strlen(rel_path) - 1] = '\0';
        }
        // printf("@%s@\n",rel_path);
        // printf("rel_path: %s\n", rel_path);
        if(chdir(rel_path) != 0)
        {
            // printf("failed\n");
            // x
            perror("cd");
        }
        memset(rel_path,0,strlen(rel_path));
    }


    else
    {
        // printf("out: %s\n", out);
        if (chdir(out) != 0)
        {
            // printf("failed\n");
            perror("cd");
        }
    }

    for(int i=0;i<4096;i++)
    {
        previous[i]='\0';
    }
    for(int i=0;i<strlen(pwd);i++)
    {
        previous[i]=pwd[i];
    }
    
    memset(pwd,0,4096);
    memset(out,0,strlen(out));

    return;
}