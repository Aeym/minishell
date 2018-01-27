#include "minishell.h"

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
	//printf("test1\n");
	if (!(tmp = (char **)malloc(sizeof(char *) * (nbl + 1 + add - del))))
		return NULL;
	//printf("nbl +add - del = %d\n", nbl + add - del);
	tmp[nbl + add - del] = NULL;
	while (k < nbl)
	{
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
		if (i == m)
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