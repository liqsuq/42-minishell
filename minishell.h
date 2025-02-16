// minisehll.h
>>>>>>> main

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdnoreturn.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "libft/libft.h"

# define PROMPT "minish$ "

typedef enum e_kind
{
	WORD,
	META,
	EOL,
}	t_kind;

typedef struct s_token
{
	char			*word;
	t_kind			kind;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	int	exit_status;
}		t_data;

// interpret.c
int				interpret(char *line);
void	fatal_error(const char *msg);

// search_path.c
char    *search_path(const char *filename);
#endif
