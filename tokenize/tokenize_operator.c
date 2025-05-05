/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:46:42 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/05 15:42:59 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(const char *s)
{
	char *const	ops[] = {">>", "<<", ">", "<", "|"};
	size_t		i;

	i = -1;
	while (++i < sizeof(ops) / sizeof(*ops))
		if (ft_strncmp(s, ops[i], ft_strlen(ops[i])) == 0)
			return (1);
	return (0);
}

t_token	*tokenize_operator(t_data *data, char **line)
{
	char *const	ops[] = {">>", "<<", ">", "<", "|"};
	char		*cur;
	size_t		i;
	char		*op;	

	cur = *line;
	i = -1;
	while (++i < sizeof(ops) / sizeof(*ops))
	{
		if (ft_strncmp(cur, ops[i], ft_strlen(ops[i])) == 0)
		{
			op = xstrdup(ops[i]);
			*line = cur + ft_strlen(op);
			return (new_token(op, TK_OP));
		}
	}
	return (tokenize_error(data, "unexpected operator", line), NULL);
}
