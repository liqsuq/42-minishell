// parse.c

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

static void	parse_redirect(t_data *data, t_node *node, t_token **token)
{
	t_node	*redir;
	t_token	*tok;

	tok = *token;
	if (!ft_strcmp(tok->word, ">"))
		redir = add_node(&node->redirects, new_node(ND_REDIR_OUT));
	else if (!ft_strcmp(tok->word, ">>"))
		redir = add_node(&node->redirects, new_node(ND_REDIR_APPEND));
	else if (!ft_strcmp(tok->word, "<"))
		redir = add_node(&node->redirects, new_node(ND_REDIR_IN));
	else if (!ft_strcmp(tok->word, "<<"))
		redir = add_node(&node->redirects, new_node(ND_REDIR_HEREDOC));
	tok = tok->next;
	if (redir->kind == ND_REDIR_HEREDOC)
	{
		if (ft_strcmp(tok->word, "EOF") != 0)
			parse_error("minishell only supports '<<EOF'", data, token);
		//redir->delimiter = dup_token(tok);
	}
	else
		redir->filename = dup_token(tok);
	tok = tok->next;
	*token = tok;
}

t_node	*parse(t_data *data, t_token *token)
{
	t_node	*head;
	t_node	*cur;

	if (!token)
		return (NULL);
	head = new_node(ND_SIMPLE_CMD);
	cur = head;
	while (token)
	{
		if (token->kind == TK_WORD)
		{
			add_token(&cur->args, dup_token(token));
			token = token->next;
		}
		else if (token->kind == TK_OP)
		{
			if (!ft_strcmp(token->word, "|"))
			{
				cur = add_node(&head, new_node(ND_SIMPLE_CMD));
				token = token->next;
			}
			else if (is_redirect(token))
				parse_redirect(data, cur, &token);
			else
				parse_error("unexpected token", data, &token);
		}
		else
			parse_error("unexpected token", data, &token);
	}
	return (head);
}
