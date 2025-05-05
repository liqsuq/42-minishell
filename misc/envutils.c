/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:59:24 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/05 16:30:24 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*env;

	env = xcalloc(1, sizeof(t_env));
	env->key = xstrdup(key);
	env->value = xstrdup(value);
	env->next = NULL;
	return (env);
}

void	free_env(t_env **env)
{
	t_env	*next;

	if (*env == NULL)
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

void	set_env(t_env **env, char *key, char *value, t_env *prev)
{
	if (*env == NULL)
	{
		if (prev != NULL)
			prev->next = new_env(key, value);
		else
			*env = new_env(key, value);
		return ;
	}
	if (ft_strcmp((*env)->key, key) == 0)
	{
		free((*env)->value);
		(*env)->value = xstrdup(value);
		return ;
	}
	set_env(&(*env)->next, key, value, *env);
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env;
	char	*eq_pos;
	char	*key;

	env = NULL;
	i = -1;
	while (envp[++i] != NULL)
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos == NULL)
			continue ;
		key = xsubstr(envp[i], 0, (eq_pos - envp[i]) / sizeof(char));
		set_env(&env, key, eq_pos + 1, NULL);
		free(key);
	}
	return (env);
}
