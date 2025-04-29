// builtin_pwd.c
#include "minishell.h"

void	builtin_pwd(t_data *data)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	pwd = get_env(data->env, "PWD");
	if (pwd)
	{
		ft_printf("%s\n", pwd);
		// ft_putendl_fd(pwd_env, STDOUT);
		data->exit_status = 0;
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			return (builtin_error(data, "pwd: getcwd", strerror(errno)));
		ft_printf("%s\n", cwd);
		// ft_putendl_fd(cwd, STDOUT);
		data->exit_status = 0;
	}
}
