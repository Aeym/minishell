#include <stdlib.h>
#include "../libft/libft.h"
#include <limits.h>


int countab(char **tab)
{
	int i = 0;

	printf("test2\n");
	while (tab[i])
	{
		printf("countab tab[%d] = %s\n", i, tab[i]);
		i++;
	}
	printf("test3\n");
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

void	freetab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

char **cptab(char **tab, int add, int del, int m)
{
	int i;
	int j;
	int k;
	int nbl;
	int nbc;
	char **tmp;

	i = 0;
	k = 0;
	nbl = countab(tab);
	printf("test1\n");
	if (!(tmp = (char **)malloc(sizeof(char *) * (nbl + 1 + add - del))))
		return NULL;
	printf("nbl +add - del = %d\n", nbl + add - del);
	tmp[nbl + add - del] = NULL;
	while (k < nbl)
	{
		if (i == m)
			k++;
		nbc = ft_strlen(tab[k]);
		if (!(tmp[i] = (char *)malloc(sizeof(char) * (nbc + 1))))
			return NULL;
		tmp[i][nbc] = '\0';
		j = 0;
		while (j < nbc)
		{
			tmp[i][j] = tab[k][j];
			j++;
		}
		//printf("tmp[%d] = %s\n", i, tmp[i]);
		i++;
		k++;
	}
	return tmp;
}

int	checkequal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && i != 0 && i != ft_strlen(str) - 1)
			return i;
		i++;
	}
	return 0;
}



int envexist(char **tab, char *str)
{
	char *tmp;
	int i;

	i = 0;
	while (tab[i])
	{
		if (ft_strstr(tab[i], str))
			return i;
		i++;
	}
	return -1;
}

void ft_addenvar(char ***envcp, char *str)
{
	int nbl;
	char **tmp;

	nbl = countab(*envcp);
	tmp = cptab(*envcp, 1, 0, -1);
	tmp[nbl] = ft_strdup(str);
	
	*envcp = tmp;
}

void ft_removenvar(char ***envcp, int i)
{
	char **tmp;
	int nbl;

	printf("i = %d\n", i);

	nbl = countab(*envcp);

	printf("nbl = %s\n", nbl);
	tmp = cptab(*envcp, 0, 1, i);
	*envcp = tmp;
}

int main(int ac, char **av, char **envp)
{
	char cwd[PATH_MAX];
	char *line;
	char **split;
	int nbw;
	int nbenv;
	int ret; // recupere l'emplacement de la variable d'env dans le tab envp
	char *envname; // nom de la variable d'env quon veut set
	int nbc; //nb char before '='
	char str[] =  "salut \"     salut ca va\"";

	char **envcp = cptab(envp, 0, 0, -1);
	while(1)
	{
		int i = 1;
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
			if ((nbc = checkequal(split[1])) != 0)
			{
				envname = ft_strsub(split[1], 0, nbc);
				if ((ret = envexist(envcp, envname)) != -1)
				{
					free(envcp[ret]);
					envcp[ret] = ft_strdup(split[1]);
					envp = envcp;
				}
				else
				{
					ft_addenvar(&envcp, split[1]);
					envp = envcp;
				}
			}
		}
		else if (ft_strcmp(split[0], "unsetenv") == 0)
		{
			envname = split[1];
			printf("%s\n", envname);
			if ((ret = envexist(envcp, envname)) != -1)
			{
				printf("ret = %d\n", ret);
				ft_removenvar(&envcp, ret);
				envp = envcp;
			}
			else
			{
				printf("error\n");
			}
		}
		free(line);
		freetab(split);
	}
	printf("%s\n", line);
}