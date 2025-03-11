// main.c

#include "minishell.h"

static int	process_line(char *line)
{
	int		status;
	t_token	*token;
	t_node	*node;

	status = 0;
	token = tokenize(line);
	node = parse(token);
	expand(node);
	if (syntax_error == 1)
		status = ERROR_SYNTAX;
	else
		status = exec_nodes(node);
	free_node(node);
	free_token(token);
	return (status);
}

int	main(void)
{
	char	*line;
	int		last_status;

	last_status = 0;
	rl_outstream = stderr;
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (*line)
		{
			add_history(line);
			last_status = process_line(line);
		}
		free(line);
	}
	return (last_status);
}
