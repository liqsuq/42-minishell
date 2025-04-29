// expand_heredoc.c

#include "minishell.h"

static int	is_delim_quoted(char *str)
{
	return (ft_strchr(str, '\'') || ft_strchr(str, '\"'));
}

static void	interrupt_heredoc(t_data *data)
{
	g_signal = 0;
	data->is_abort = 1;
	data->exit_status = SIGINT + 128;
}

static void	read_heredoc(t_data *data, t_node **node)
{
	char	*line;

	while (1)
	{
		g_signal = 0;
		rl_event_hook = check_signal_heredoc;
		if (isatty(STDIN))
			line = readline(PROMPT_HEREDOC);
		else
			line = get_next_line_nonl(STDIN);
		if (line == NULL)
		{
			ft_dprintf(STDERR,
				HEADER "warning: here-document delimited by end-of-file\n");
			break ;
		}
		if (ft_strcmp(line, (*node)->args->word) == 0 || g_signal == SIGINT)
		{
			free(line);
			break ;
		}
		add_token(&(*node)->args, new_token(line, TK_WORD));
	}
	if (g_signal == SIGINT)
		interrupt_heredoc(data);
}

/**
 * expand_heredoc - Expand heredocumant in the tree.
 * @data: The data structure containing the environment variables and state.
 * @node: The current node in the tree.
 * This function handles the expansion of heredoc nodes in the tree.
 * It checks if the node is a heredoc and if so, it reads and expands the input.
 * Note that the read input is stored in the heardoc node args->next.
 * Args contains the delimiter of heredoc and the input is linked to the next.
 */
void	expand_heredoc(t_data *data, t_node *node)
{
	int	is_quoted;

	if (node == NULL || data->is_abort)
		return ;
	if (node->kind == ND_REDIR_HEREDOC && node->args != NULL)
	{
		is_quoted = is_delim_quoted(node->args->word);
		expand_quote_token(node->args);
		read_heredoc(data, &node);
		if (!is_quoted && !data->is_abort)
		{
			expand_variable_token(node->args->next, 1, data->env);
			expand_parameter_token(data, node->args->next, 1);
		}
	}
	expand_heredoc(data, node->redirects);
	expand_heredoc(data, node->next);
}
