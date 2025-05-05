/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:59:24 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/05 14:46:49 by kadachi          ###   ########.fr       */
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

	if (env == NULL || *env == NULL)
		return ;
	next = (*env)->next;
	free((*env)->key);
	free((*env)->value);
	free(*env);
	*env = next;
	free_env(env);
}

char	*get_env(t_env *env, char *key)
{
	if (env == NULL)
		return (NULL);
	if (ft_strcmp(env->key, key) == 0)
		return (env->value);
	return (get_env(env->next, key));
}

int	set_env(t_env **env, char *key, char *value, t_env *prev)
{
	if (env == NULL || key == NULL || value == NULL)
		return (1);
	if (*env == NULL)
	{
		if (prev != NULL)
			return (prev->next = new_env(key, value), 0);
		else
			return (*env = new_env(key, value), 0);
	}
	if (ft_strcmp((*env)->key, key) == 0)
	{
		free((*env)->value);
		(*env)->value = ft_strdup(value);
		if ((*env)->value == NULL)
			return (1);
		return (0);
	}
	return (set_env(&(*env)->next, key, value, *env));
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
		if (set_env(&env, key, eq_pos + 1, NULL) != 0)
			return (free_env(&env), free(key), NULL);
		free(key);
	}
	return (env);
}
