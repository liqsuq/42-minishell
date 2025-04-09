// expand_heredoc.c

#include "minishell.h"

static int	is_delim_quoted(char *str)
{
	return (ft_strchr(str, SQUOTE) || ft_strchr(str, DQUOTE));
}

static t_token	*read_heredoc(t_node *node)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT_HEREDOC);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, node->args->word) == 0)
		{
			free(line);
			break ;
		}
		add_token(&node->args, new_token(line, TK_WORD));
	}
	return (node->args->next);
}

// expand_heredoc()
// This function handles the expansion of heredoc nodes in the tree.
// It checks if the node is a heredoc and if so, it reads and expands the input.
// Note that the read input is stored in the heardoc node args->next.
// Args contains the delimiter of heredoc and the input is linked to the next.
void	expand_heredoc(t_data *data, t_node *node)
{
	int	is_quoted;

	if (node == NULL)
		return ;
	if (node->kind == ND_REDIR_HEREDOC && node->args != NULL)
	{
		is_quoted = is_delim_quoted(node->args->word);
		expand_quote_token(node->args);
		read_heredoc(node);
		if (!is_quoted)
		{
			expand_variable_token(node->args->next, 1);
			expand_parameter_token(data, node->args->next, 1);
		}
	}
	expand_heredoc(data, node->redirects);
	expand_heredoc(data, node->next);
}
