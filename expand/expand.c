/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:45:07 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/05 15:57:52 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s != NULL)
		size += ft_strlen(*s);
	new = xcalloc(size, sizeof(char));
	if (*s != NULL)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s != NULL)
		free(*s);
	*s = new;
}

void	expand(t_data *data, t_node *node)
{
	expand_variable(data, node);
	expand_parameter(data, node);
	expand_word(data, node);
	expand_quote(data, node);
	expand_heredoc(data, node);
}
