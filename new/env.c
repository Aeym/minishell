#include "minishell.h"

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
	countab(tmp);
	freetab(*envcp);
	*envcp = tmp;
}

void ft_removenvar(char ***envcp, int i)
{
	char **tmp;
	int nbl;

	//printf("i = %d\n", i);

	nbl = countab(*envcp);

	//printf("nbl = %d\n", nbl);
	tmp = cptab(*envcp, 0, 1, i);
	freetab(*envcp);
	*envcp = tmp;
}