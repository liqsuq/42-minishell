/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:44:58 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/04 20:09:27 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*split_word(t_token *token, char *end, char *next)
{
	char	*str;
	t_token	*new;

	if (token == NULL || end == NULL || next == NULL)
		return (NULL);
	if (*next != '\0')
	{
		str = ft_strdup(next);
		if (str == NULL)
			return (NULL);
		new = new_token(str, TK_WORD);
		if (new == NULL)
		{
			free(str);
			return (NULL);
		}
		new->next = token->next;
		token->next = new;
	}
	str = ft_substr(token->word, 0, end - token->word);
	if (str == NULL)
		return (NULL);
	free(token->word);
	token->word = str;
	return (token);
}

static t_token	*split_word_tail(t_token *token)
{
	char	*end;
	char	*cur;
	char	c;

	cur = token->word;
	while (*cur != '\0')
	{
		if (is_blank(*cur))
		{
			end = cur;
			while (is_blank(*cur))
				cur++;
			return (split_word(token, end, cur));
		}
		if (*cur == '\'' || *cur == '\"')
		{
			c = *cur++;
			while (*cur != c)
				cur++;
		}
		cur++;
	}
	return (token);
}

static t_token	*split_word_head(t_token *token)
{
	char	*cur;
	char	*new;

	cur = token->word;
	while (is_blank(*cur))
		cur++;
	if (cur != token->word)
	{
		new = ft_strdup(cur);
		if (new == NULL)
			return (NULL);
		free(token->word);
		token->word = new;
	}
	return (token);
}

static void	expand_word_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->kind == TK_WORD && token->word != NULL)
	{
		if (split_word_head(token) == NULL)
			fatal_error("split_word_head", strerror(errno));
		if (split_word_tail(token) == NULL)
			fatal_error("split_word_tail", strerror(errno));
	}
	expand_word_token(token->next);
}

void	expand_word(t_data *data, t_node *node)
{
	t_token	*cur;
	t_token	*next;

	if (node == NULL || data->is_abort)
		return ;
	expand_word_token(node->args);
	cur = node->args;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->word != NULL && ft_strlen(cur->word) == 0)
			pop_token(&node->args, cur, NULL);
		cur = next;
	}
	expand_word(data, node->next);
}
