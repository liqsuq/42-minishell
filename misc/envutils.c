// envutils.c

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*env;

	if (!key || !value)
		return (NULL);
	env = calloc(1, sizeof(t_env));
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

int	unset_env(t_env **env, char *key)
{
	t_env	*cur;
	t_env	*prev;

	if (!env || !key || !(*env))
		return (1);
	cur = *env;
	prev = NULL;
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

char	**dump_env(t_env *env)
{
	int		count;
	t_env	*cur;
	char	**envp;
	size_t	len;
	int		i;

	i = 0;
	count = 0;
	cur = env;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!envp)
		fatal_error("malloc");
	cur = env;
	while (i < count)
	{
		len = ft_strlen(cur->key) + 1 + ft_strlen(cur->value) + 1;
		envp[i] = (char *)malloc(sizeof(char) * len);
		if (!envp[i])
			fatal_error("malloc");
		sprintf(envp[i], "%s=%s", cur->key, cur->value);
		cur = cur->next;
		i++;
	}
	envp[count] = NULL;
	return (envp);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
