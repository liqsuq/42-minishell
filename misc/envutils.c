// envutils.c

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		fatal_error("malloc");
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = NULL;
	return (env);
}

t_env	*free_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
	return (NULL);
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
	t_env	*prev = NULL;

	if (!env || !key || !value)
		return (1);

	cur = *env;
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

int	unset_env(t_env **env, char *key)
{
	t_env	*cur;
	t_env	*prev = NULL;

	if (!env || !key || !(*env))
		return (1);

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (1);
}
