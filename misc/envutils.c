/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:59:24 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/01 18:20:32 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*env;

	if (!key || !value)
		return (NULL);
	env = ft_calloc(1, sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->key = ft_strdup(key);
	if (env->key == NULL)
		return (free_env(&env), NULL);
	env->value = ft_strdup(value);
	if (env->value == NULL)
		return (free_env(&env), NULL);
	env->next = NULL;
	return (env);
}

void	free_env(t_env **env)
{
	t_env	*next;

	if (env == NULL)
		return ;
	while (*env)
	{
		next = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = next;
	}
	*env = NULL;
}

char	*get_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	set_env(t_env **env, char *key, char *value)
{
	t_env	*cur;
	t_env	*prev;

	if (!env || !key || !value)
		return (1);
	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			free(cur->value);
			cur->value = ft_strdup(value);
			if (!cur->value)
				return (1);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	if (prev)
		prev->next = new_env(key, value);
	else
		*env = new_env(key, value);
	return (0);
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env;
	char	*eq_pos;
	char	*key;

	if (envp == NULL)
		return (NULL);
	env = NULL;
	i = -1;
	while (envp[++i] != NULL)
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos == NULL)
			continue ;
		key = ft_substr(envp[i], 0, (eq_pos - envp[i]) / sizeof(char));
		if (key == NULL)
			return (NULL);
		if (set_env(&env, key, eq_pos + 1))
			return (free_env(&env), free(key), NULL);
		free(key);
	}
	return (env);
}
