#include "headers.h"
#include "pwd.h"

int comp(char *a, char *b, int len)
{
	if(strlen(a)<len || strlen(b)<len)
	{
		return -1;
	}
	else
	{
		for(int i=0;i<len;i++)
		{
			if(a[i]!=b[i])
			{
				return 1;
			}
		}
		return 0;
	}
	
}

void pwd(char *shell_dir)
{
	int SDlen = strlen(shell_dir);
	char *pwd = malloc(4096 * sizeof(char));
	getcwd(pwd, 4096);

	printf("%s\n", pwd);
}