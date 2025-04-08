// expand_heredoc.c

#include "minishell.h"

static int	is_delim_quoted(char *str)
{
	return (ft_strchr(str, SQUOTE) || ft_strchr(str, DQUOTE));
}

static void interrupt_heredoc(t_data *data)
{
	g_signal = 0;
	data->abort = 1;
	data->exit_status = SIGINT + 128;
}

static void	read_heredoc(t_data *data, t_node **node)
{
	char	*line;

	while (1)
	{
		g_signal = 0;
		if (isatty(STDIN_FILENO))
			rl_event_hook = check_signal_heredoc;
		line = readline(PROMPT_HEREDOC);
		if (line == NULL)
		{
			ft_dprintf(STDERR_FILENO,
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

void	expand_heredoc(t_data *data, t_node *node)
{
	int	is_quoted;

	if (node == NULL || data->abort)
		return ;
	if (node->kind == ND_REDIR_HEREDOC && node->args != NULL)
	{
		is_quoted = is_delim_quoted(node->args->word);
		expand_quote_token(node->args);
		read_heredoc(data, &node);
		if (!is_quoted && !data->abort)
		{
			expand_variable_token(node->args->next, 1);
			expand_parameter_token(data, node->args->next, 1);
		}
	}
	expand_heredoc(data, node->redirects);
	expand_heredoc(data, node->next);
}
