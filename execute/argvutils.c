// argvutils.c

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
