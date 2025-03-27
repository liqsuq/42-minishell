// main.c

#include "minishell.h"

static void	init_data(t_data *data)
{
	data->exit_status = 0;
	data->syntax_error = 0;
}

static void	process_line(t_data *data, char *line)
{
	t_token	*token;
	t_node	*node;

	data->syntax_error = 0;
	token = tokenize(data, line);
	node = parse(data, token);
	expand(data, node);
	if (data->syntax_error == 1)
		data->exit_status = ERROR_SYNTAX;
	else
		execute(data, node);
	free_node(node);
	free_token(token);
}

int	main(void)
{
	t_data	data;
	char	*line;

	g_signal = 0;
	rl_outstream = stderr;
	init_data(&data);
	while (1)
	{
		setup_signal();
		if (isatty(STDIN_FILENO))
			rl_event_hook = check_signal_main;
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (*line)
		{
			add_history(line);
			process_line(&data, line);
		}
		free(line);
	}
	return (data.exit_status);
}
