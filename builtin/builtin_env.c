// builtin_env.c

#include "minishell.h"

static void	print_env_builtin(t_env *env)
{
	if (env == NULL)
		return ;
	printf("%s=%s\n", env->key, env->value);
	print_env_builtin(env->next);
}

void	builtin_env(t_data *data)
{
	print_env_builtin(data->env);
	data->exit_status = 0;
}
