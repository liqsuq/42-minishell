// main.c
#include "minishell.h"

char	**tokens2argv(t_token *tokens)
{
	t_token	*cur;
	char	**argv;
	int		i;

	i = 0;
	cur = tokens;
	while (cur != NULL)
	{
		cur = cur->next;
		i++;
	}
	argv = malloc((i + 1) * sizeof(char *));
	if (argv == NULL)
		fatal_error("malloc");
	i = 0;
	cur = tokens;
	while (cur != NULL)
	{
		argv[i++] = ft_strdup(cur->word);
		cur = cur->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	free_argv(char **argv)
{
	char	**cur;

	cur = argv;
	while (*cur != NULL)
		free(*cur++);
	free(argv);
}

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
