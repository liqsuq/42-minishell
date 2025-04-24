// argvutils.c

#include "minishell.h"

static void	trans_args(char **argv, t_token *args)
{
	if (args == NULL)
		return ;
	*argv = ft_strdup(args->word);
	trans_args(argv + 1, args->next);
}

char	**new_argv(t_token *args)
{
	char	**argv;
	size_t	len;
	t_token	*cur;

	len = 0;
	cur = args;
	while (cur != NULL)
	{
		len++;
		cur = cur->next;
	}
	argv = ft_calloc((len + 1), sizeof(char *));
	if (argv == NULL)
		fatal_error("ft_calloc");
	trans_args(argv, args);
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
