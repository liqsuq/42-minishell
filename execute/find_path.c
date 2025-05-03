/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:45:37 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/03 18:02:25 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(t_env *env, char path[PATH_MAX], char *line)
{
	char	*env_value;
	char	*end;

	if (ft_strchr(line, '/'))
		return (ft_strlcpy(path, line, PATH_MAX), path);
	env_value = get_env(env, "PATH");
	while (line && *line && env_value && *env_value)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(env_value, ':');
		if (end == NULL)
			end = env_value + ft_strlen(env_value);
		ft_strlcpy(path, env_value, end - env_value + 1);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, line, PATH_MAX);
		if (access(path, F_OK) == 0)
			return (path);
		if (*end == '\0')
			break ;
		env_value = end + 1;
	}
	ft_dprintf(STDERR, HEADER "command not found\n");
	return (NULL);
}
