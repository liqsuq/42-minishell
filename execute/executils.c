/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:43:18 by kadachi           #+#    #+#             */
/*   Updated: 2025/04/29 18:43:22 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	trans_args(char **argv, t_token *args)
{
	if (args == NULL)
		return ;
	*argv = ft_strdup(args->word);
	trans_args(argv + 1, args->next);
}

char	**new_argv(t_token *args)
{
	char	**argv;
	size_t	len;
	t_token	*cur;

	len = 0;
	cur = args;
	while (cur != NULL)
	{
		len++;
		cur = cur->next;
	}
	argv = ft_calloc((len + 1), sizeof(char *));
	if (argv == NULL)
		fatal_error("ft_calloc", strerror(errno));
	trans_args(argv, args);
	return (argv);
}

void	free_argv(char **argv)
{
	char	**cur;

	cur = argv;
	while (*cur != NULL)
		free(*cur++);
	free(argv);
}

char	*find_path(t_env *env, char *line)
{
	char	path[PATH_MAX];
	char	*env_value;
	char	*end;

	if (ft_strchr(line, '/'))
		return (ft_strdup(line));
	env_value = get_env(env, "PATH");
	while (line && *line && env_value && *env_value)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(env_value, ':');
		if (end != NULL)
			ft_strlcpy(path, env_value, end - env_value + 1);
		else
			ft_strlcpy(path, env_value, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, line, PATH_MAX);
		if (access(path, X_OK) == 0)
			return (ft_strdup(path));
		if (end == NULL)
			break ;
		env_value = end + 1;
	}
	return (NULL);
}
