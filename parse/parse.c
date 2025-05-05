/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:46:20 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/05 15:57:26 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirect(t_token *token)
{
	char *const	ops[] = {">>", "<<", ">", "<"};
	size_t		i;

	i = -1;
	while (++i < sizeof(ops) / sizeof(*ops))
		if (!ft_strcmp(token->word, ops[i]))
			return (1);
	return (0);
}

static t_token	*parse_redirect(t_data *data, t_node *node, t_token *token)
{
	t_node	*nd;

	if (!ft_strcmp(token->word, ">"))
		nd = add_node(&node->redirects, new_node(ND_REDIR_OUT));
	else if (!ft_strcmp(token->word, ">>"))
		nd = add_node(&node->redirects, new_node(ND_REDIR_APPEND));
	else if (!ft_strcmp(token->word, "<"))
		nd = add_node(&node->redirects, new_node(ND_REDIR_IN));
	else
		nd = add_node(&node->redirects, new_node(ND_REDIR_HEREDOC));
	token = token->next;
	if (token == NULL || token->kind != TK_WORD)
		return (parse_error(data, "unexpected token", &token), token);
	nd->args = dup_token(token);
	token = token->next;
	return (token);
}

static t_token	*parse_simple_cmd(t_data *data, t_node **node, t_token *token)
{
	t_node	*nd;

	nd = add_node(node, new_node(ND_SIMPLE_CMD));
	while (token != NULL)
	{
		if (token->kind == TK_WORD)
		{
			add_token(&nd->args, dup_token(token));
			token = token->next;
		}
		else if (is_redirect(token))
			token = parse_redirect(data, nd, token);
		else
			break ;
	}
	return (token);
}

static t_token	*parse_pipeline(t_data *data, t_node **node, t_token *token)
{
	if (token && (token->kind == TK_WORD || is_redirect(token)))
	{
		token = parse_simple_cmd(data, node, token);
		if (token && token->kind == TK_OP && !ft_strcmp(token->word, "|"))
		{
			if (token->next)
				token = parse_pipeline(data, node, token->next);
			else
				parse_error(data, "unexpected end of file", &token);
		}
	}
	else
		parse_error(data, "unexpected token", &token);
	return (token);
}

t_node	*parse(t_data *data, t_token *token)
{
	t_node	*node;

	node = NULL;
	if (token == NULL)
		return (NULL);
	parse_pipeline(data, &node, token);
	return (node);
}
