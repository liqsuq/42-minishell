// builtin_cd.c
#include "minishell.h"

static void	change_directory(t_data *data, char *path)
{
	char	cwd[PATH_MAX];

	if (path == NULL)
		return ;
	if (chdir(path) < 0)
	{
		builtin_error("cd: chdir", data, strerror(errno));
		return ;
	}
	if (get_env(data->env, "PWD") != NULL)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			builtin_error("cd: getcwd", data, strerror(errno));
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
			builtin_error("cd: getcwd", data, strerror(errno));
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
		builtin_error("cd: HOME not set", data, NULL);
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
		builtin_error("cd: too many arguments", data, NULL);
	else if (argv[1][0] == '/')
		change_directory(data, argv[1]);
	else
		change_relative(data, argv[1]);
}
