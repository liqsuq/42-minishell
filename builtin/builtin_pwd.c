/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:42:29 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/01 18:12:51 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_data *data)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	pwd = get_env(data->env, "PWD");
	if (pwd != NULL)
	{
		ft_printf("%s\n", pwd);
		data->exit_status = 0;
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			return (builtin_error(data, "pwd: getcwd", strerror(errno)));
		ft_printf("%s\n", cwd);
		data->exit_status = 0;
	}
}
