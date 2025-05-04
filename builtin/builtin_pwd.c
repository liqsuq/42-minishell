/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:42:29 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/04 11:05:56 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_data *data, char **argv)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	(void)argv;
	pwd = get_env(data->env, "PWD");
	if (pwd != NULL)
	{
		ft_printf("%s\n", pwd);
		data->exit_status = 0;
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			return (bltin_error(data, "pwd: getcwd", strerror(errno)));
		ft_printf("%s\n", cwd);
		data->exit_status = 0;
	}
}
