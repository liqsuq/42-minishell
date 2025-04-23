// main.c

#include "minishell.h"

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

static void	setup_shell(t_data *data, char **envp)
{
	rl_outstream = stderr;
	setup_signal();
	data->exit_status = 0;
	data->is_abort = 0;
	data->env = init_env_list(envp);
}

static void	reset_shell(t_data *data)
{
	free_env(&data->env);
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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	(void)argc, (void)argv;
	setup_shell(&data, envp);
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
		if (*line != '\0')
		{
			add_history(line);
			process_line(&data, line);
		}
		free(line);
	}
	if (isatty(STDIN_FILENO))
		ft_dprintf(STDERR_FILENO, "exit\n");
	return (reset_shell(&data), data.exit_status);
}
