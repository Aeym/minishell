#include "minishell.h"

int	cmd_exit(t_min *s)
{
	free(s->line);
	freetab(s->split);
	freetab(s->envcp);
	return (0);
}

int	cmd_echo(t_min *s)
{
	s->i = 1;
	while (s->i < s->nbw)
	{
		ft_putstr(s->split[s->i]);
		if (s->i != s->nbw - 1)
			write(1, " ", 1);
		else
			write(1, "\n", 1);
		s->i++;
	}
	return (1);
}

int cmd_env(t_min *s, char ***envp)
{
	s->i = 0;
	s->nbenv = countab(*envp);
	printf("nbv=env = %d\n", s->nbenv);
	while (s->i < s->nbenv)
	{
		ft_putstr(s->envcp[s->i]);
		write(1, "\n", 1);
		s->i++;
	}
	return (1);
}

int cmd_setenv(t_min *s, char ***envp)
{
	if ((s->nbc = checkequal(s->split[1])) != 0)
	{
		s->envname = ft_strsub(s->split[1], 0, s->nbc);
		if ((s->ret = envexist(s->envcp, s->envname)) != -1)
		{
			free(s->envcp[s->ret]);
			s->envcp[s->ret] = ft_strdup(s->split[1]);
			*envp = s->envcp;

		}
		else
		{
			ft_addenvar(&s->envcp, s->split[1]);
			*envp = s->envcp;
		}
		free(s->envname);
	}
	return (1);
}

int cmd_unsetenv(t_min *s, char ***envp)
{
	s->envname = s->split[1];
	//printf("%s\n", envname);

	if ((s->ret = envexist(s->envcp, s->envname)) != -1)
	{
		//printf("ret = %d\n", ret);
		ft_removenvar(&s->envcp, s->ret);
		*envp = s->envcp;
	}
	else
	{
		printf("error\n");
	}
	return (1);
}