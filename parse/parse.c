/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nateshim <nateshim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:46:20 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/03 03:43:06 by nateshim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirect(t_token *token)
{
	char *const	ops[] = {">>", "<<", ">", "<"};
	size_t		i;

	i = -1;
	if (token->next == NULL || token->next->kind != TK_WORD)
		return (0);
	while (++i < sizeof(ops) / sizeof(*ops))
		if (!ft_strcmp(token->word, ops[i]))
			return (1);
	return (0);
}

static t_token	*parse_redirect(t_node *node, t_token *token)
{
	t_node	*nd;
	t_token	*tk;

	tk = token;
	if (!ft_strcmp(tk->word, ">"))
		nd = add_node(&node->redirects, new_node(ND_REDIR_OUT));
	else if (!ft_strcmp(tk->word, ">>"))
		nd = add_node(&node->redirects, new_node(ND_REDIR_APPEND));
	else if (!ft_strcmp(tk->word, "<"))
		nd = add_node(&node->redirects, new_node(ND_REDIR_IN));
	else
		nd = add_node(&node->redirects, new_node(ND_REDIR_HEREDOC));
	if (nd == NULL)
		fatal_error("add_node", strerror(errno));
	tk = tk->next;
	nd->args = dup_token(tk);
	tk = tk->next;
	return (tk);
}

static t_token	*parse_simple_cmd(t_data *data, t_node **node, t_token *token)
{
	t_node	*nd;

	nd = add_node(node, new_node(ND_SIMPLE_CMD));
	while (token != NULL)
	{
		if (token->kind == TK_WORD)
		{
			if (add_token(&nd->args, dup_token(token)) == NULL)
				fatal_error("add_token", strerror(errno));
			token = token->next;
		}
		else if (is_redirect(token))
			token = parse_redirect(nd, token);
		else
		{
			if (token->kind == TK_OP && ft_strcmp(token->word, "|") == 0)
				break ;
			if (token->kind == TK_OP)
				parse_error(data, "newline", &token);
			else
				parse_error(data, token->word, &token);
			break ;
		}
	}
	return (token);
}

static t_token	*parse_pipeline(t_data *data, t_node **node, t_token *token)
{
	t_token		*tk;
	const char	*msg;

	tk = token;
	if (tk && (tk->kind == TK_WORD || is_redirect(tk)))
	{
		tk = parse_simple_cmd(data, node, tk);
		if (tk && tk->kind == TK_OP && !ft_strcmp(tk->word, "|"))
		{
			if (tk->next)
				tk = parse_pipeline(data, node, tk->next);
			else
				parse_error(data, "unexpected end of file", &tk);
		}
	}
	else
	{
		if (tk == NULL || tk->word == NULL)
			msg = "newline";
		else
			msg = tk->word;
		parse_error(data, msg, &tk);
	}
	return (tk);
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
