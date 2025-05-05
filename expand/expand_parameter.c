/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:44:20 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/06 00:14:51 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_status(t_data *data, char **dst, char **str)
{
	char	*stat;
	char	*cur;

	stat = xitoa(data->exit_status);
	cur = stat;
	while (*cur != '\0')
		append_char(dst, *cur++);
	free(stat);
	*str += 2;
}

static void	append_quote_para(t_data *data, char **dst, char **str)
{
	char	c;
	char	*cur;

	c = **str;
	cur = *str;
	append_char(dst, *cur++);
	while (*cur != c)
	{
		if (c == '\"' && cur[0] == '$' && cur[1] == '?')
			append_status(data, dst, &cur);
		else
			append_char(dst, *cur++);
	}
	append_char(dst, *cur++);
	*str = cur;
}

void	expand_parameter_token(t_data *data, t_token *token, int force)
{
	char	*new_word;
	char	*str;

	if (token == NULL)
		return ;
	if (token->kind == TK_WORD && token->word != NULL)
	{
		str = token->word;
		new_word = xcalloc(1, sizeof(char));
		while (*str != '\0')
		{
			if (!force && (*str == '\'' || *str == '\"'))
				append_quote_para(data, &new_word, &str);
			else if (str[0] == '$' && str[1] == '?')
				append_status(data, &new_word, &str);
			else
				append_char(&new_word, *str++);
		}
		free(token->word);
		token->word = new_word;
	}
	expand_parameter_token(data, token->next, force);
}

void	expand_parameter(t_data *data, t_node *node)
{
	if (node == NULL || data->abort)
		return ;
	if (node->kind != ND_REDIR_HEREDOC)
		expand_parameter_token(data, node->args, 0);
	expand_parameter(data, node->redirects);
	expand_parameter(data, node->next);
}
