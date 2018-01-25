#include <stdlib.h>
#include "../FDF/libft/libft.h"
#include <limits.h>


int countab(char **tab)
{
	int i = 0;

	while (tab[i])
		i++;
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


char **splitmaison(char *str)
{
	int i = 0;
	int j;
	int k;
	int l = 0;
	int m;
	int nbw;
	char **tab;

	nbw = countwordquote(str);
	if (!(tab = (char **)malloc(sizeof(char *) * (nbw + 1))))
		return NULL;
	tab[nbw] = NULL;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!(tab[l] = (char *)malloc(sizeof(char) * (countletter(&str[i]) + 1))))
			return NULL;
		tab[l][countletter(&str[i])] = '\0';
		m = 0;
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i])
			{
				tab[l][m]= str[i];
				i++;
				m++;
			}
			i++;
		}
		else if (str[i] != '\0')
		{
			while (str[i] != ' ' && str[i] != '\t' && str[i])
			{
				tab[l][m]= str[i];
				i++;
				m++;
			}
		}
		l++;
	}
	return tab;
}

int main(int ac, char **av, char **envp)
{
	char cwd[PATH_MAX];
	char *line;
	char **split;
	int nbw;
	int nbenv;
	int i = 1;
	char str[] =  "salut \"     salut ca va\"";

	while(1)
	{
		// ft_putstr("alrick>");
		getcwd(cwd, PATH_MAX);
		ft_putstr(ft_strcat(cwd, ">"));
		get_next_line(0, &line);
		if (ft_strlen(line) == 0)
			free(line);
		split = splitmaison(line);
		nbw = countab(split);
		//ft_putstr(split[1]);
		if (ft_strcmp(split[0], "exit") == 0)
			return 0;
		else if (ft_strcmp(split[0], "echo") == 0)
		{
			while (i < nbw)
			{
				ft_putstr(split[i]);
				if (i != nbw - 1)
					write(1, " ", 1);
				else
					write(1, "\n", 1);
				i++;
			}
		}
			else if (ft_strcmp(split[0], "env") == 0)
			{
				i = 0;
				nbenv = countab(envp);
				while (i < nbenv)
				{
					ft_putstr(envp[i]);
					write(1, "\n", 1);
					i++;
				}
			}
			else if (ft_strcmp(split[0], "setenv") == 0)
			{

			}
			else if (ft_strcmp(split[0], "unsetenv") == 0)
			{

			} 


	}
	//printf("%s\n", line);
}