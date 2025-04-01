// expand_heredoc.c

#include "minishell.h"

static t_token *parse_heredoc(t_data *data, t_node *node, t_token *token)
{
	char *delim;
	char *line;

	(void)data;
	delim = token->word;
	if (ft_strchr(delim, SQUOTE) || ft_strchr(delim, DQUOTE))
		node->is_quoted = 1;
	while (1)
	{
		line = readline(PROMPT_HEREDOC);
		if (line == NULL)
			break;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break;
		}
		add_token(&node->heredoc, new_token(line, TK_WORD));
	}
	return (token->next);
}


static void	expand_quote_redirects(t_node *redirects)
{
	if (redirects == NULL)
		return ;
	expand_quote_token(redirects->args);
	expand_quote_redirects(redirects->next);
}

void	expand_quote(t_node *node)
{
	if (node == NULL)
		return ;
	expand_quote_redirects(node->redirects);
	expand_quote(node->next);
}
