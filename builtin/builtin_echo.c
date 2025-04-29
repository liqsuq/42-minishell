// builtin_echo.c

#include "minishell.h"

static int	is_opt_newline(char *str)
{
	int	i;

	if (str != NULL && ft_strncmp(str, "-n", 2) == 0)
	{
		i = 2;
		while (str[i] != '\0' && str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

void	builtin_echo(t_data *data, char **argv)
{
	int	opt_newline;
	int	done_optparse;
	int	i;

	opt_newline = 0;
	done_optparse = 0;
	i = 0;
	while (argv[++i] != NULL)
	{
		if (!done_optparse && is_opt_newline(argv[i]))
		{
			opt_newline = 1;
			continue ;
		}
		done_optparse = 1;
		ft_putstr_fd(argv[i], STDOUT);
		if (argv[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT);
	}
	if (!opt_newline)
		ft_putchar_fd('\n', STDOUT);
	data->exit_status = 0;
}
