// error.c

#include "minishell.h"

int	syntax_error = 0;

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

void	assert_error(const char *msg)
{
	ft_dprintf(STDERR_FILENO, "Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

void	tokenize_error(const char *msg, char **line)
{
	char *cur;

	cur = *line;
	syntax_error = 1;
	ft_dprintf(STDERR_FILENO, HEADER "syntax error: %s\n", msg);
	while (*cur != '\0')
		cur++;
	*line = cur;
}

void	parse_error(const char *msg, t_token **token)
{
	t_token *cur;

	cur = *token;
	syntax_error = 1;
	ft_dprintf(STDERR_FILENO, HEADER "syntax error: %s\n", msg);
	while (cur != NULL)
		cur = cur->next;
	*token = cur;
}
