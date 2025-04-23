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
	// print_token(token);
	node = parse(data, token);
	// print_node(node);
	expand(data, node);
	if (!data->is_abort)
		execute(data, node);
	free_node(node);
	free_token(token);
}

static t_env	*init_env_list(char **envp)
{
	int		i;
	t_env	*env;
	char	*eq_pos;
	char	*key;

	env = NULL;
	if (envp == NULL)
		return (NULL);
	i = -1;
	while (envp[++i] != NULL)
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos == NULL)
			continue ;
		key = ft_substr(envp[i], 0, (eq_pos - envp[i]) / sizeof(char));
		if (key == NULL)
			return (NULL);
		if (set_env(&env, key, eq_pos + 1))
			return (free_env(&env), free(key), NULL);
		free(key);
	}
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	init_data(&data);
	data.env = init_env_list(envp);
	setup_signal();
	while (1)
	{
		g_signal = 0;
		rl_event_hook = check_signal_main;
		if (isatty(STDIN_FILENO))
			line = readline(PROMPT);
		else
			line = get_next_line_nonl(STDIN_FILENO);
		if (line == NULL)
			break ;
		if (*line)
		{
			add_history(line);
			process_line(&data, line);
		}
		free(line);
	}
	if (isatty(STDIN_FILENO))
		ft_dprintf(STDERR_FILENO, "exit\n");
	return (data.exit_status);
}
