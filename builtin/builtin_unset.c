// builtin_unset.c

#include "minishell.c"

void	builtin_unset(t_data *data, char **argv)
{
	while (*++argv != NULL)
		unset_env(data->env, *argv)
	data->exit_status = 0;
}
