// error.c

#include "minishell.h"

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
