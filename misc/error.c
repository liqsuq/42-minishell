// error.c

#include "minishell.h"

void	fatal_error(const char *msg)
{
	ft_dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

void	assert_error(const char *msg)
{
	ft_dprintf(STDERR_FILENO, "Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

void	tokenize_error(const char *msg, t_data *data, char **line)
{
	char	*cur;

	cur = *line;
	data->syntax_error = 1;
	ft_dprintf(STDERR_FILENO, HEADER "syntax error: %s\n", msg);
	while (*cur != '\0')
		cur++;
	*line = cur;
}

void	parse_error(const char *msg, t_data *data, t_token **token)
{
	t_token	*cur;

	cur = *token;
	data->syntax_error = 1;
	ft_dprintf(STDERR_FILENO, HEADER "syntax error: %s\n", msg);
	while (cur != NULL)
		cur = cur->next;
	*token = cur;
}
