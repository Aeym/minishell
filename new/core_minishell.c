#include "minishell.h"

int	core_minishell(t_min *s, char ***envp)
{
	s->split = splitmaison(s->line);
	s->nbw = countab(s->split);
	//ft_putstr(split[1]);
	if (ft_strcmp(s->split[0], "exit") == 0)
		return (cmd_exit(s));
	else if (ft_strcmp(s->split[0], "echo") == 0)
		return (cmd_echo(s));
	else if (ft_strcmp(s->split[0], "env") == 0)
		return (cmd_env(s, envp));
	else if (ft_strcmp(s->split[0], "setenv") == 0)
		return (cmd_setenv(s, envp));
	else if (ft_strcmp(s->split[0], "unsetenv") == 0)
		return (cmd_unsetenv(s, envp));
	free(s->line);
	freetab(s->split);
	return (1);
}