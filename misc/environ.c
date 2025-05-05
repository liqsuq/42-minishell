/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:45:36 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/05 16:25:22 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_env(t_env *env)
{
	size_t	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**dump_environ(t_env *env)
{
	size_t	count;
	char	**envp;
	size_t	i;
	size_t	len;

	if (env == NULL)
		return (NULL);
	count = count_env(env);
	envp = xcalloc(count + 1, sizeof(char *));
	i = 0;
	while (i < count)
	{
		len = ft_strlen(env->key) + 1 + ft_strlen(env->value) + 1;
		envp[i] = xcalloc(len, sizeof(char));
		ft_strlcpy(envp[i], env->key, len);
		ft_strlcat(envp[i], "=", len);
		ft_strlcat(envp[i++], env->value, len);
		env = env->next;
	}
	envp[count] = NULL;
	return (envp);
}

void	free_environ(char ***envp)
{
	char	**cur;

	if (*envp == NULL)
		return ;
	cur = *envp;
	while (*cur)
		free(*cur++);
	free(*envp);
	*envp = NULL;
}
