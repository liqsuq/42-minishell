// parse.c

#include "minishell.h"

t_node	*parse(t_token *token)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	while (token)
	{
		if (token->kind == TK_WORD)
		{
			append_token(&node->args, tokdup(token));
			token = token->next;
		}
		else
			parse_error("unexpected token", &token, token);
	}
	return (node);
}
