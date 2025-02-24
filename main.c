// main.c

#include "minishell.h"

int	main(void)
{
	char	*line;
	int	last_status;
	
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
			last_status = interpret(line);
		}
		free(line);
	}
	return (last_status);
}
