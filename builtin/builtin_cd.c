// builtin_cd.c
#include "minishell.h"

static void	change_directory(t_data *data, char *path)
{
	char	cwd[PATH_MAX];

	if (path == NULL)
		return ;
	if (chdir(path) < 0)
	{
		ft_dprintf(STDERR, HEADER "cd: %s\n", strerror(errno));
		data->exit_status = 1;
		return ;
	}
	if (get_env(data->env, "PWD") != NULL)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			ft_dprintf(STDERR, HEADER "cd: getcwd: %s\n", strerror(errno));
			data->exit_status = 1;
			return ;
		}
		set_env(&data->env, "PWD", cwd);
	}
	data->exit_status = 0;
}

static void change_relative(t_data *data, const char *relpath)
{
	char	*wd;
	char	cwd[PATH_MAX];
	char	buf[PATH_MAX];

	wd = get_env(data->env, "PWD");
	if (wd == NULL)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			ft_dprintf(STDERR, HEADER "cd: getcwd: %s\n", strerror(errno));
			data->exit_status = 1;
			return ;
		}
		wd = cwd;
	}
	ft_strlcpy(buf, wd, PATH_MAX);
	ft_strlcat(buf, "/", PATH_MAX);
	ft_strlcat(buf, relpath, PATH_MAX);
	change_directory(data, buf);
}

static void change_homedir(t_data *data)
{
	char	*home;

	home = get_env(data->env, "HOME");
	if (home == NULL)
	{
		ft_dprintf(STDERR, HEADER "cd: HOME not set\n");
		data->exit_status = 1;
		return ;
	}
	change_directory(data, home);
}

void	builtin_cd(t_data *data, char **argv)
{
	if (data == NULL || argv == NULL || *argv == NULL)
		return ;
	if (argv[1] == NULL)
		change_homedir(data);
	else if (argv[2] != NULL)
	{
		ft_dprintf(STDERR, HEADER "cd: too many arguments\n");
		data->exit_status = 1;
	}
	else if (argv[1][0] == '/')
		change_directory(data, argv[1]);
	else
		change_relative(data, argv[1]);
}
