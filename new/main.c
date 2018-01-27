#include "minishell.h"

void	core_minishell(t_min *s, char ***envp)
{
	s->split = splitmaison(s->line);
	s->nbw = countab(s->split);
	//ft_putstr(split[1]);
	if (ft_strcmp(s->split[0], "exit") == 0)
	{
		free(s->line);
		freetab(s->split);
		freetab(s->envcp);
		return;
	}
	else if (ft_strcmp(s->split[0], "echo") == 0)
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
	}
	else if (ft_strcmp(s->split[0], "env") == 0)
	{
		s->i = 0;
		s->nbenv = countab(*envp);
		while (s->i < s->nbenv)
		{
			ft_putstr(*envp[s->i]);
			write(1, "\n", 1);
			s->i++;
		}
	}
	else if (ft_strcmp(s->split[0], "setenv") == 0)
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
	}
	else if (ft_strcmp(s->split[0], "unsetenv") == 0)
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
	}
	free(s->line);
	freetab(s->split);

}


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
			core_minishell(&s, &envp);
		}
	}
	return (0);
}