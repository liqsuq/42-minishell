// builtin_pwd.c
#include "minishell.h"

void	builtin_pwd(t_data *data, char **argv)
{
	char	*pwd_env;
	char	cwd[PATH_MAX];

	(void)argv;
	pwd_env = get_env(data->env, "PWD");
	if (pwd_env)
	{
		ft_putendl_fd(pwd_env, STDOUT_FILENO);
		data->exit_status = 0;
		return ;
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			ft_dprintf(STDERR_FILENO, HEADER "pwd: getcwd: %s\n",
				strerror(errno));
			data->exit_status = 1;
			return ;
		}
		ft_putendl_fd(cwd, STDOUT_FILENO);
		data->exit_status = 0;
	}
}
