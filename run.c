#include "headers.h"
#include "run.h"

// Functions start
#include "prompt.h"
#include "pwd.h"
#include "echo.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
#include "foreground.h"
#include "background.h"
#include "history.h"
#include "redirection.h"
#include "env.h"
#include "jobs.h"
#include "kjob.h"
#include "overkill.h"
#include "bg.h"
#include "fg.h"
// Functions end

char * run(char *curr_com, char *shell_dir, char *prompt_dir)
{
    int else_flag = 0;

    if (comp(curr_com, "quit", 4) == 0)
    {
        if (strlen(curr_com) != 4)
        {
            if (curr_com[4] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                exit(0);
            }
        }

        else
        {
            exit(0);
        }
    }

    else if (comp(curr_com, "pwd", 3) == 0)
    {
        if (strlen(curr_com) != 3)
        {
            if (curr_com[3] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                pwd(shell_dir);
            }
        }

        else
        {
            pwd(shell_dir);
        }
    }

    else if (comp(curr_com, "echo", 4) == 0)
    {
        if (strlen(curr_com) != 4)
        {
            if (curr_com[4] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                echo(curr_com);
            }
        }

        else
        {
            echo(curr_com);
        }
    }

    else if (comp(curr_com, "cd", 2) == 0)
    {
        if (strlen(curr_com) != 2)
        {
            if (curr_com[2] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                cd(curr_com, shell_dir);
                prompt_dir = pwd2(shell_dir);
            }
        }

        else
        {
            cd(curr_com, shell_dir);
            prompt_dir = pwd2(shell_dir);
        }
    }

    else if (comp(curr_com, "ls", 2) == 0)
    {
        if (strlen(curr_com) != 2)
        {
            if (curr_com[2] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                ls(curr_com, shell_dir);
            }
        }

        else
        {
            ls(curr_com, shell_dir);
        }
    }

    else if (comp(curr_com, "pinfo", 5) == 0)
    {
        if (strlen(curr_com) != 5)
        {
            if (curr_com[5] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                pinfo(curr_com);
            }
        }

        else
        {
            pinfo(curr_com);
        }
    }

    else if (comp(curr_com, "history", 7) == 0)
    {
        if (strlen(curr_com) != 7)
        {
            if (curr_com[7] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                history(curr_com, shell_dir);
            }
        }

        else
        {
            history(curr_com, shell_dir);
        }
    }

    else if (comp(curr_com, "setenv", 6) == 0)
    {
        if (strlen(curr_com) != 6)
        {
            if (curr_com[6] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                mysetenv(curr_com);
            }
        }

        else
        {
            mysetenv(curr_com);
        }
    }

    else if (comp(curr_com, "unsetenv", 8) == 0)
    {
        if (strlen(curr_com) != 8)
        {
            if (curr_com[8] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                myunsetenv(curr_com);
            }
        }

        else
        {
            myunsetenv(curr_com);
        }
    }

    else if (comp(curr_com, "jobs", 4) == 0)
    {
        if (strlen(curr_com) != 4)
        {
            if (curr_com[4] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                jobs();
            }
        }

        else
        {
            jobs();
        }
    }

    else if (comp(curr_com, "kjob", 4) == 0)
    {
        if (strlen(curr_com) != 4)
        {
            if (curr_com[4] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                kjob(curr_com);
            }
        }

        else
        {
            kjob(curr_com);
        }
    }

    else if (comp(curr_com, "overkill", 8) == 0)
    {
        if (strlen(curr_com) != 8)
        {
            if (curr_com[8] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                overkill();
            }
        }

        else
        {
            overkill();
        }
    }

    else if (comp(curr_com, "bg", 2) == 0)
    {
        if (strlen(curr_com) != 2)
        {
            if (curr_com[2] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                bg(curr_com);
            }
        }

        else
        {
            bg(curr_com);
        }
    }

    else if (comp(curr_com, "fg", 2) == 0)
    {
        if (strlen(curr_com) != 2)
        {
            if (curr_com[2] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                fg(curr_com);
            }
        }

        else
        {
            fg(curr_com);
        }
    }

    else
    {
        if (curr_com[strlen(curr_com) - 1] != '&')
        {
            foreground(curr_com);
        }
        else
        {
            background(curr_com);
        }
    }

    if (else_flag)
    {
        if (curr_com[strlen(curr_com) - 1] != '&')
        {
            foreground(curr_com);
        }
        else
        {
            background(curr_com);
        }
    }

    return prompt_dir;
}