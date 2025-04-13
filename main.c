// main.c

#include "minishell.h"

static void	init_data(t_data *data)
{
	data->exit_status = 0;
	data->is_abort = 0;
	data->env = NULL;
}

static void	process_line(t_data *data, char *line)
{
	t_token	*token;
	t_node	*node;

	data->is_abort = 0;
	token = tokenize(data, line);
	node = parse(data, token);
	expand(data, node);
	if (!data->is_abort)
		execute(data, node);
	free_node(node);
	free_token(token);
}

static t_env *init_env_list(char **envp)
{
	t_env *env_list = NULL;
	int    i = 0;

	while (envp[i])
	{
		char *equal_pos = strchr(envp[i], '=');
		if (equal_pos)
		{
			size_t keylen = equal_pos - envp[i];
			char  *key = strndup(envp[i], keylen);
			char  *val = strdup(equal_pos + 1);

			set_env(&env_list, key, val);

			free(key);
			free(val);
		}
		i++;
	}
	return (env_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	(void)argc;
	(void)argv;

	g_signal = 0;
	rl_outstream = stderr;
	init_data(&data);
	data.env = init_env_list(envp);
	setup_signal();
	while (1)
	{
		g_signal = 0;
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
	ft_dprintf(STDERR_FILENO, "exit\n");
	return (data.exit_status);
}
