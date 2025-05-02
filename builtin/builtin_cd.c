/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:41:14 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/02 16:05:27 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_directory(t_data *data, t_path *path)
{
	char	*s;

	s = dump_path(path);
	if (s == NULL)
		return (bltin_error(data, "cd: dump_path", strerror(errno)));
	if (chdir(s) < 0)
		return (free(s), bltin_error(data, "cd: chdir", strerror(errno)));
	if (get_env(data->env, "PWD") != NULL && set_env(&data->env, "PWD", s) < 0)
		return (free(s), bltin_error(data, "cd: set_env", strerror(errno)));
	free(s);
	data->exit_status = 0;
}

static int	stuck_path(t_data *data, t_path **path, char *arg)
{
	char	*slash;
	size_t	len;

	while (*arg != '\0')
	{
		if (*arg == '/' || (*arg == '.' && (*(arg + 1) == '/' || !*(arg + 1))))
			arg += 1;
		else if (*arg == '.' && *(arg + 1) == '.'
			&& (*(arg + 2) == '/' || !*(arg + 2)))
			arg += (pop_path(path, NULL), 2);
		else
		{
			slash = ft_strchr(arg, '/');
			if (slash != NULL)
				len = slash - arg;
			else
				len = ft_strlen(arg);
			if (push_path(path, new_path(arg, len)) == NULL)
				return (bltin_error(data, "cd: push_path", strerror(errno)), 1);
			arg += len;
		}
	}
	return (0);
}

static t_path	*stuck_home(t_data *data, t_path **path)
{
	char	*home;

	home = get_env(data->env, "HOME");
	if (home == NULL)
		return (bltin_error(data, "cd: HOME not set", NULL), NULL);
	if (stuck_path(data, path, home))
		return (bltin_error(data, "cd: stuck_path", strerror(errno)), NULL);
	return (*path);
}

static t_path	*stuck_wd(t_data *data, t_path **path)
{
	char	*wd;
	char	cwd[PATH_MAX];

	wd = get_env(data->env, "PWD");
	if (wd == NULL)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
			return (bltin_error(data, "cd: getcwd", strerror(errno)), NULL);
		wd = cwd;
	}
	if (stuck_path(data, path, wd))
		return (bltin_error(data, "cd: stuck_path", strerror(errno)), NULL);
	return (*path);
}

void	builtin_cd(t_data *data, char **argv)
{
	char	*str;
	t_path	*path;

	if (data == NULL || argv == NULL || *argv == NULL)
		return ;
	str = NULL;
	path = NULL;
	if (argv[1] == NULL)
	{
		if (stuck_home(data, &path) == NULL)
			return ;
	}
	else if (argv[2] != NULL)
		return (bltin_error(data, "cd: too many arguments", NULL));
	else if (argv[1][0] == '/')
		str = argv[1];
	else if (stuck_wd(data, &path) != NULL)
		str = argv[1];
	else
		return ;
	if (str != NULL && stuck_path(data, &path, str))
		bltin_error(data, "cd: stuck_path", strerror(errno));
	change_directory(data, path);
	free_path(&path);
}
