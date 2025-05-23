/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:44:29 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/03 15:02:03 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_quote(t_token *token)
{
	char	*new_word;
	char	*cur;
	char	c;

	new_word = ft_calloc(1, sizeof(char));
	if (new_word == NULL)
		fatal_error("ft_calloc", strerror(errno));
	cur = token->word;
	while (*cur != '\0')
	{
		if (*cur == '\'' || *cur == '\"')
		{
			c = *cur;
			while (*++cur != c)
				append_char(&new_word, *cur);
			cur++;
		}
		else
			append_char(&new_word, *cur++);
	}
	free(token->word);
	token->word = new_word;
}

void	expand_quote_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->kind == TK_WORD && token->word != NULL)
		remove_quote(token);
	expand_quote_token(token->next);
}

void	expand_quote(t_data *data, t_node *node)
{
	if (node == NULL || data->is_abort)
		return ;
	if (node->kind != ND_REDIR_HEREDOC)
		expand_quote_token(node->args);
	expand_quote(data, node->redirects);
	expand_quote(data, node->next);
}
