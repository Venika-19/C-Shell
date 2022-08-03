#include "headers.h"
#include "ls.h"

void display(char *dir_name, char *flagstr, int count)
{
    char *curr_dir = malloc(4096 * sizeof(char));
    getcwd(curr_dir, 4096);

    char dir_path[16376];

    if(dir_name[0]=='/')
    {
        strcat(dir_path,dir_name);
    }
    else
    {
        strcat(dir_path,curr_dir);
        strcat(dir_path,"/");
        strcat(dir_path,dir_name);
    }

    int flag=0;
    for(int i=0;i<strlen(flagstr);i++)
    {
        if(flagstr[i]=='a' && flag%2==0)
        {
            flag+=1;
        }
        else if(flagstr[i]=='l' && flag<2)
        {
            flag+=2;
        }
    }

    struct dirent **contents;

    // printf("dir_path:%s###\n",dir_path);

    int dir_count = scandir(dir_path, &contents, NULL, alphasort);

    if(dir_count<0)
    {
        perror("dir_count");
        return;
    }

    if(flag>=2)
    {
        if (count > 1)
        {
            printf("%s:\n", dir_name);
        }

        long long int total = 0;
        for (int i = 0; i < dir_count; i++)
        {
            if(contents[i]->d_name[0]!='.' || flag==3)
            {
                char the_other_way[4096] = "";
                strcat(the_other_way, curr_dir);
                strcat(the_other_way, "/");
                strcat(the_other_way, dir_name);
                strcat(the_other_way, "/");
                strcat(the_other_way, contents[i]->d_name);

                // printf("the_other_way: %s\n", the_other_way);

                struct stat infoTOW;
                stat(the_other_way, &infoTOW);
                total += infoTOW.st_blocks;
                // printf("#tot: %lld#Block_st: %lu\n", total, infoTOW.st_blocks);
            }
        }
        total = total / 2;

        printf("total %lld\n", total);

        for(int i=0;i<dir_count;i++)
        {
            if(flag%2==0)
            {
                if(contents[i]->d_name[0]=='.')
                {
                    continue;
                }
            }

            char *file_path = malloc(4096 * sizeof(char));

            for(int i=0;i<4096;i++)
            {
                file_path[i]='\0';
            }

            strcat(file_path,dir_path);
            strcat(file_path,"/");
            strcat(file_path,contents[i]->d_name);

            struct stat dirInfo;
            stat(file_path,&dirInfo);

            printf((S_ISDIR(dirInfo.st_mode)) ? "d" : "-");
            printf((dirInfo.st_mode&S_IRUSR) ? "r" : "-");
            printf((dirInfo.st_mode&S_IWUSR) ? "w" : "-");
            printf((dirInfo.st_mode&S_IXUSR) ? "x" : "-");
            printf((dirInfo.st_mode&S_IRGRP) ? "r" : "-");
            printf((dirInfo.st_mode&S_IWGRP) ? "w" : "-");
            printf((dirInfo.st_mode&S_IXGRP) ? "x" : "-");
            printf((dirInfo.st_mode&S_IROTH) ? "r" : "-");
            printf((dirInfo.st_mode&S_IWOTH) ? "w" : "-");
            printf((dirInfo.st_mode&S_IXOTH) ? "x" : "-");

            printf(" %7ld", dirInfo.st_nlink);
            
            struct passwd *pass = getpwuid(dirInfo.st_uid);
            struct group *group = getgrgid(dirInfo.st_gid);
            
            printf(" %20s", pass->pw_name);
            printf(" %20s", group->gr_name);
            printf(" %7ld", dirInfo.st_size);

            char time_val[256];

            // for(int i=0;i<256;i++)
            // {
            //     time_val[i]='\0';
            // }

            time_t present = time(NULL);
            struct tm time_last, time_present;

            localtime_r(&dirInfo.st_mtime, &time_last);
            localtime_r(&present, &time_present);

            if (time_last.tm_year != time_present.tm_year)
            {
                strftime(time_val, sizeof(time_val), "%b %e %Y", localtime(&dirInfo.st_mtime));
            }
            else
            {
                strftime(time_val, sizeof(time_val), "%b %e %H:%M", localtime(&dirInfo.st_mtime));
            }
            printf(" %s ", time_val);

            printf("\t%s\n", contents[i]->d_name);
        }
    }
    else
    {
        if(count>1)
        {
            printf("%s:\n",dir_name);
        }

        int printed=0;
        for (int i = 0; i < dir_count; i++)
        {
            if (flag % 2 == 0)
            {
                if (contents[i]->d_name[0] == '.')
                {
                    continue;
                }
            }
            printed=1;
            printf("%s ",  contents[i]->d_name);
        }
        if(printed==1)
        {
            printf("\n");
        }
    }

    memset(dir_path,0,16376);
    memset(curr_dir,0,4096);

    return;
}

void ls(char *in, char *shell_dir)
{
    char pwd[4096];
    getcwd(pwd, 4096);

    char out[4096];
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

    char *flags = malloc(64 * sizeof(char));
    char * dir[64];
    int f=0, dir_count=0, arg_flag = 0;

    for(int i=0;i<strlen(out);i++)
    {
        if(out[i]=='-')
        {
            i++;
            while(out[i]!=' ')
            {
                if(out[i]!='a' && out[i]!='l')
                {
                    fprintf(stderr, "ls: invalid option -- \'%c\'\n",out[i]);
                    memset(flags, 0, 64);
                    memset(pwd, 0, 4096);
                    memset(out, 0, strlen(in));
                    return;
                }
                flags[f]=out[i];
                i++;
                if(i>=strlen(out))
                {
                    break;
                }
                f++;
            }
        }

        else if(out[i]==' ')
        {
            continue;
        }

        else
        {
            char *temp = malloc(4096 * sizeof(char));
            for(int i=0;i<4096;i++)
            {
                temp[i]='\0';
            }
            
            int k=0;
            while(out[i]!=' ' && out[i]!='\0')
            {
                if(out[i]!='~')
                {
                    temp[k] = out[i];
                    i++;
                    k++;
                    if (i >= strlen(out))
                    {
                        break;
                    }
                }
                else
                {
                    strcat(temp,shell_dir);
                    k+=strlen(shell_dir);
                    i++;
                    if(i >= strlen(out))
                    {
                        break;
                    }
                }
                
            } 
            temp[k]='\0';

            char the_way[4096]="";
            // printf("temp:%s###\n",temp);

            if(temp[0]!='/')
            {
                strcat(the_way,pwd);
                strcat(the_way,"/");
                strcat(the_way,temp);
            }
            else
            {
                strcat(the_way,temp);
            }
            
            // printf("the_way:%s###\n", the_way);

            struct stat checker;
            if(stat(the_way,&checker)<0)
            {
                arg_flag=1;
                fprintf(stderr, "ls: No such file or directory \'%s\'\n", temp);
            }
            else if (((checker.st_mode & S_IRUSR) ? 0 : 1)==1)
            {
                arg_flag=1;
                fprintf(stderr, "ls: cannot open directory \'%s\': Permission denied\n", temp);
            }
            else
            {
                dir[dir_count] = malloc(4096 * sizeof(char));  
                dir[dir_count] = temp;
                dir_count++;
            }

            memset(the_way,0,4096);
        }
    }

    flags[f+1]='\0';

    if(dir_count==0&&arg_flag==0)
    {
        dir_count++;
        dir[0]=malloc(4096 * sizeof(char));
        dir[0]=".";
    }

    // for(int i=0;i<dir_count;i++)
    // {
    //     printf("ls%d: %s\n", i+1, dir[i]);
    // }

    for(int i=0;i<dir_count;i++)
    {
        display(dir[i],flags,dir_count);
    }

    memset(flags,0,64);
    memset(pwd,0,4096);
    memset(out,0,strlen(in));

    return;
}