#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include "../libft/libft.h"
# include <limits.h>


typedef struct 	s_min
{
	char cwd[PATH_MAX];
	char *line;
	char **split;
	int nbw;
	int i;
	int nbenv;
	int ret; // recupere l'emplacement de la variable d'env dans le tab envp
	char *envname; // nom de la variable d'env quon veut set
	int nbc; //nb char before '='
	char **envcp;
}				t_min;

int countab(char **tab);
int countwordquote(char *str);
int countletter(char *str);
char **splitmaison(char *str);
void	freetab(char **tab);
char **cptab(char **tab, int add, int del, int m);
int	checkequal(char *str);
int envexist(char **tab, char *str);
void ft_addenvar(char ***envcp, char *str);
void ft_removenvar(char ***envcp, int i);

# endif