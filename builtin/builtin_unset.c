/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:42:54 by kadachi           #+#    #+#             */
/*   Updated: 2025/04/29 18:42:57 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_env(t_env **env, char *key)
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

void	builtin_unset(t_data *data, char **argv)
{
	while (*++argv != NULL)
		unset_env(&data->env, *argv);
	data->exit_status = 0;
}
