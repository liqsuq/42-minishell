// builtin_env.c

#include "minishell.h"

void	builtin_env(t_data *data)
{
	t_env	*cur;

	cur = data->env;
	while (cur)
	{
		if (cur->key && cur->value)
			ft_printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	data->exit_status = 0;
}
