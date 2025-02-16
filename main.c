// main.c

#include "minishell.h"

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (*line)
		{
			add_history(line);
			interpret(line);
		}
		free(line);
	}
	return (0);
}
