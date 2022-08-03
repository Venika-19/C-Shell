#include "headers.h"
#include "history.h"

void init_hist_q(char *shell_dir)
{
    char path[4096] = {'\0'};
    strcat(path, shell_dir);
    strcat(path, "/hist_info.txt");
    int fd = open(path, O_CREAT | O_RDONLY, 0666);


    char contents[4000100]={'\0'};
    int bytes = read(fd,contents,4000000);

    for(int i=0;i<strlen(contents);i++)
    {
        char comm[4096]={'\0'};
        

        int k=0;
        while(contents[i]!='\n')
        {
            // printf("i: %d\n", i);
            comm[k]=contents[i];
            i++;
            k++;
        }
        // printf("contents: %s\n\n\n", comm);
        if(hist_head->after==0)
        {
            hist_head->next=NULL;
            hist_head->prev=NULL;
            for(int j=0;j<4096;j++)
            {
                hist_head->name[j]=comm[j];
            }
            hist_head->after++;
        }
        else
        {
            struct q* curr = malloc(sizeof(struct q));
            curr->next=hist_head;
            hist_head->prev=curr;
            curr->after=hist_head->after+1;
            hist_head=curr;
            for (int j = 0; j < 4096; j++)
            {
                hist_head->name[j] = comm[j];
            }
        }
    }

    return;
}

void history(char *in, char *shell_dir)
{
    char path[4096] = {'\0'};
    strcat(path, shell_dir);
    strcat(path, "/hist_info.txt");
    int fd = open(path, O_RDONLY);
    char count[100]={'\0'};
    int val;
    for(int i=8;i<strlen(in);i++)
    {
        if(in[i]!=' ')
        {
            count[i-8]=in[i];
        }
    }

    if(count[0]=='\0')
    {
        val=10;
    }
    else
    {
        val=atoi(count);
    }
    
    if(val>20)
    {
        fprintf(stderr ,"history: invalid arguments: number of requested commands cannot exceed 20\n");
        return;
    }
    // printf("VAL: %d###\n", val);

    // if()

    char info[4000100]={'\0'};
    int size = read(fd,info,4000000);

    close(fd);

    char hist_comm[20][4096];
    
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<4096;j++)
        {
            hist_comm[i][j]='\0';
        }
    }

    int k=0, p=0;
    
    for(int j=0;j<size;j++)
    {
        hist_comm[k][p]=info[j];
        p++;
        if(info[j]=='\n')
        {
            p=0;
            k++;
        }
    }

    if(k<val)
    {
        for(int i=0;i<k;i++)
        {
            printf("%s",hist_comm[i]);
        }
    }
    else
    {
        for(int i=0;i<k;i++)
        {
            if(i>=k-val)
            {
                printf("%s",hist_comm[i]);
            }
        }
    }
    

    return;
}

void add_comm(char *in, char *shell_dir)
{
    char path[4096]={'\0'};
    strcat(path,shell_dir);
    strcat(path,"/hist_info.txt");
    // printf("path: %s\n\n\n\n", path);



    if(hist_head->after==20)
    {
        struct q *curr = malloc(sizeof(struct q));
        
        curr->next=hist_head;
        curr->prev=NULL;
        hist_head->prev=curr;

        for(int i=0;i<4096;i++)
        {
            curr->name[i]='\0';
        }
        for(int i=0;i<strlen(in);i++)
        {
            curr->name[i]=in[i];
        }
        hist_head=curr;

        while(curr->next!=NULL)
        {
            curr->after=curr->next->after;
            curr=curr->next;
        }
        curr->prev->next=NULL;
        free(curr);
    }
    else if(hist_head->after==0)
    {
        hist_head->next=NULL;
        hist_head->prev=NULL;
        for (int i = 0; i < 4096; i++)
        {
            hist_head->name[i] = '\0';
        }
        for (int i = 0; i < strlen(in); i++)
        {
            hist_head->name[i] = in[i];
        }
        hist_head->after++;
    }
    else
    {
        struct q *curr = malloc(sizeof(struct q));

        curr->next = hist_head;
        curr->prev = NULL;
        hist_head->prev = curr;
        curr->after=hist_head->after+1;

        for (int i = 0; i < 4096; i++)
        {
            curr->name[i] = '\0';
        }
        for (int i = 0; i < strlen(in); i++)
        {
            curr->name[i] = in[i];
        }
        hist_head = curr;
    }
    
    char file_content[4000100]={'\0'};
    struct q *curr=hist_head;

    while(curr->next!=NULL)
    {
        curr=curr->next;
    }

    while(curr!=NULL)
    {
        strcat(file_content,curr->name);
        strcat(file_content,"\n");
        curr=curr->prev;
    }

    int fd = open (path,O_WRONLY | O_TRUNC | O_CREAT, 0777);
    int bytes = write(fd,file_content,strlen(file_content));
    close(fd);


    return;
}