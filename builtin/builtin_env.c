/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:41:53 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/04 11:05:55 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_data *data, char **argv)
{
	t_env	*cur;

	(void)argv;
	cur = data->env;
	while (cur)
	{
		if (cur->key && cur->value)
			ft_printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	data->exit_status = 0;
}
