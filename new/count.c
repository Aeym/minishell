#include "minishell.h"

int countab(char **tab)
{
	int i = 0;

	//printf("test2\n");
	while (tab[i])
	{
		//printf("countab tab[%d] = %s\n", i, tab[i]);
		i++;
	}
	//printf("test3\n");
	return i;
}

int countwordquote(char *str)
{
	int i = 0;
	int j = 0;
	int count = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i])
				i++;
			count++;
			i++;
		}
		else if (str[i] != '\0')
		{
			while (str[i] != ' ' && str[i] != '\t' && str[i])
				i++;
			count++;
		}

	}
	return count;
}

int countletter(char *str)
{
	int i = 0;
	int nbl = 0;

	if (str[i] == '"')
	{
		i++;
		while (str[i] != '"')
		{
			i++;
			nbl++;
		}
	}
	else
	{
		while (str[i] != ' ' && str[i] != '\t' && str[i])
		{
			i++;
			nbl++;
		}
	}
	return nbl;
}