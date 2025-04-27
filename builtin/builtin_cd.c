// builtin_cd.c
#include "minishell.h"

static void	do_chdir_with_error(t_data *data, const char *path, const char *arg)
{
	if (chdir(path) < 0)
	{
		ft_dprintf(STDERR_FILENO, HEADER "cd: ");
		perror(arg);
		data->exit_status = 1;
		return ;
	}
	data->exit_status = 0;
}

static void	update_pwd_if_needed(t_data *data)
{
	char	cwd[PATH_MAX];

	if (get_env(data->env, "PWD") != NULL)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			ft_dprintf(STDERR_FILENO, "cd: getcwd: %s\n", strerror(errno));
			data->exit_status = 1;
			return ;
		}
		set_env(&data->env, "PWD", cwd);
	}
}

static bool	handle_empty_or_abs(t_data *data, char **argv)
{
	char	*home;

	if (!argv[1] || argv[1][0] == '\0')
	{
		home = get_env(data->env, "HOME");
		if (!home)
		{
			ft_dprintf(STDERR_FILENO, HEADER "HOME not set\n");
			data->exit_status = 1;
		}
		else
		{
			do_chdir_with_error(data, home, home);
			if (data->exit_status == 0)
				update_pwd_if_needed(data);
		}
		return (true);
	}
	return (false);
}

static void	get_workdir_and_cd(t_data *data, const char *relpath)
{
	char		*pwd;
	static char	buf[PATH_MAX];
	char		tmp[PATH_MAX];

	pwd = get_env(data->env, "PWD");
	if (!pwd)
	{
		if (getcwd(buf, sizeof(buf)) == NULL)
		{
			ft_dprintf(STDERR_FILENO, HEADER "getcwd: %s\n", strerror(errno));
			data->exit_status = 1;
			return ;
		}
		pwd = buf;
	}
	ft_strlcpy(tmp, pwd, sizeof(tmp));
	ft_strlcat(tmp, "/", sizeof(tmp));
	ft_strlcat(tmp, relpath, sizeof(tmp));
	do_chdir_with_error(data, tmp, relpath);
	if (data->exit_status == 0)
		update_pwd_if_needed(data);
}

void	builtin_cd(t_data *data, char **argv)
{
	if (argv[1] == NULL)
	{
		handle_empty_or_abs(data, argv);
		return ;
	}
	if (argv[2] != NULL)
	{
		ft_dprintf(STDERR_FILENO, HEADER "cd: too many arguments\n");
		data->exit_status = 1;
		return ;
	}
	if (handle_empty_or_abs(data, argv))
		return ;
	if (argv[1][0] == '/')
	{
		do_chdir_with_error(data, argv[1], argv[1]);
		if (data->exit_status == 0)
			update_pwd_if_needed(data);
		return ;
	}
	get_workdir_and_cd(data, argv[1]);
}
