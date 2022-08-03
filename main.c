#include "headers.h"
// #include<string.h>

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
#include "run.h"
#include "pipe.h"
#include "env.h"
#include "jobs.h"
#include "kjob.h"
#include "overkill.h"
#include "bg.h"
#include "fg.h"
#include "ctrlz.h"
// Functions end

int main()
{
	signal(SIGINT, ctrlc);

	signal(SIGTSTP, ctrlz);

	pid_fore=-1;

	stdinCopy = dup(STDIN_FILENO);
	stdoutCopy = dup(STDOUT_FILENO);

	head = malloc(sizeof(struct proc_info));
	head->next = NULL;
	head->size = 0;

	hist_head = malloc(sizeof(struct q));
	hist_head->after = 0;
	hist_head->next = NULL;
	hist_head->prev = NULL;

	for(int i=0;i<4096;i++)
	{
		previous[i]='\0';
	}

	char *shell_dir = malloc(4096 * sizeof(char));
	getcwd(shell_dir, 4096);

	char *prompt_dir = malloc(4096 * sizeof(char));
	prompt_dir = pwd2(shell_dir);

	init_hist_q(shell_dir);


	while (1)
	{
		prompt(prompt_dir);

		char *input;
		size_t insize = 4096;
		size_t characters;

		input = (char *)malloc(insize * sizeof(char));

		if (input == NULL)
		{
			perror("Unable to take input");
			exit(1);
		}

		characters = getline(&input, &insize, stdin);

		// printf("chars: %lu\n",characters);

		if (characters == (unsigned long)-1)
		{
			fprintf(stderr, "\n");
			exit(1);
		}

		int inlen = strlen(input);
		input[inlen - 1] = '\0';

		char out[1024][4096];
		int input_count = 0;
		int j = 0;
		char prev = ' ';
		for (int i = 0; i < strlen(input); i++)
		{
			char curr = input[i];
			if (curr == ';')
			{
				if (out[0][0] != ' ')
				{
					out[input_count][j] = '\0';
					if (out[input_count][j - 1] == ' ')
					{
						out[input_count][j - 1] = '\0';
					}
					j = 0;
					prev = ' ';
					input_count++;
				}
			}
			else if ((curr == ' ' || curr == '\t' || curr == '\r') && (prev == ' ' || prev == '\t' || prev == '\r'))
			{
				continue;
			}
			else
			{
				out[input_count][j] = curr;
				j++;
				prev = curr;
			}
		}

		out[input_count][j] = '\0';
		if (out[input_count][j - 1] == ' ')
		{
			out[input_count][j - 1] = '\0';
		}

		char hist_text[4096]={'\0'};

		char prev2 = ' ', curr2;

		int jj = 0;
		for (int i = 0; i < strlen(input); i++)
		{
			curr2 = input[i];
			if ((curr2 == ' ' || curr2 == '\t' || curr2 == '\r') && (prev2 == ' ' || prev2 == '\t' || prev2 == '\r'))
			{
				continue;
			}
			else
			{
				hist_text[jj] = curr2;
				jj++;
				prev2 = curr2;
			}
		}
		hist_text[j] = '\0';

		add_comm(hist_text, shell_dir);
		
		for (int i = 0; i <= input_count; i++)
		{

			if (out[i][0] == '\0' || out[i][0] == ' ' || out[i][0] == '\t' || out[i][0] == '\r')
			{
				continue;
			}

			prompt_dir = piping(out[i],shell_dir,prompt_dir);

			if (dup2(stdoutCopy, STDOUT_FILENO) < 0)
			{
				write(STDERR_FILENO, "This is a flag\n", strlen("This is a flag\n"));
				perror("Unable to duplicate file descriptor.");
				exit(1);
			}

			if (dup2(stdinCopy, STDIN_FILENO) < 0)
			{
				write(STDERR_FILENO, "This is a flag\n", strlen("This is a flag\n"));
				perror("Unable to duplicate file descriptor.");
				exit(1);
			}
		}
	}
}
