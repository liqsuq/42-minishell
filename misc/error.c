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

void	tokenize_error(const char *msg, char **rest, char *line)
{
	syntax_error = 1;
	ft_dprintf(STDERR_FILENO, HEADER "syntax error: %s\n", msg);
	while (*line)
		line++;
	*rest = line;
}

void	parse_error(const char *msg, t_token **rest, t_token *token)
{
	syntax_error = 1;
	ft_dprintf(STDERR_FILENO, HEADER "syntax error: %s\n", msg);
	while (token != NULL)
		token = token->next;
	*rest = token;
}
