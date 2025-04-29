// environ.c

#include "minishell.h"

static size_t envcount(t_env *env)
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


	count = envcount(env);
	envp = malloc((count + 1) * sizeof(char *));
	if (!envp)
		fatal_error("malloc");
	i = 0;
	while (i < count)
	{
		len = ft_strlen(env->key) + 1 + ft_strlen(env->value) + 1;
		envp[i] = malloc(len * sizeof(char));
		if (!envp[i])
			fatal_error("malloc");
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
	if (*envp == NULL)
		return ;
	while (**envp)
		free(*(*envp++));
	free(*envp);
	*envp = NULL;
}
