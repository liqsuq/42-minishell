/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:42:13 by kadachi           #+#    #+#             */
/*   Updated: 2025/04/29 18:42:17 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *name, size_t len)
{
	size_t	i;

	if (len == 0)
		return (0);
	if (!ft_isalpha((unsigned char)name[0]) && name[0] != '_')
		return (0);
	i = 0;
	while (++i < len)
		if (!ft_isalnum((unsigned char)name[i]) && name[i] != '_')
			return (0);
	return (1);
}

static int	check_name(t_data *data, char *arg)
{
	char	*eq;
	size_t	key_len;

	eq = ft_strchr(arg, '=');
	if (eq)
		key_len = (size_t)(eq - arg);
	else
		key_len = ft_strlen(arg);
	if (!is_valid_identifier(arg, key_len))
		return (builtin_error(data, "export: not a valid identifier", NULL), 0);
	return (1);
}

static void	export_arg(t_data *data, char *arg)
{
	char	*eq;
	size_t	key_len;

	eq = ft_strchr(arg, '=');
	if (eq == NULL)
		return ;
	key_len = (size_t)(eq - arg);
	arg[key_len] = '\0';
	set_env(&data->env, arg, eq + 1);
	arg[key_len] = '=';
}

void	builtin_export(t_data *data, char **argv)
{
	data->exit_status = 0;
	while (*++argv)
		if (check_name(data, *argv))
			export_arg(data, *argv);
}
