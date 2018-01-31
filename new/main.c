#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	t_min s;

	s.envcp = cptab(envp, 0, 0, -1);
	while(1)
	{
		getcwd(s.cwd, PATH_MAX);
		ft_putstr(ft_strcat(s.cwd, ">"));
		get_next_line(0, &s.line);
		if (ft_strlen(s.line) == 0)
			free(s.line);
		else
		{
			if (core_minishell(&s, &envp) == 0)
				return (0);
		}
	}
	return (0);
}