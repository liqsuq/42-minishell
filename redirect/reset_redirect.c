// reset_redirect.c

#include "minishell.h"

void	reset_redirect(t_node *node)
{
	if (node->kind == ND_REDIR_OUT || node->kind == ND_REDIR_APPEND)
	{
		if (dup2(node->stashed_std_fd, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	else if (node->kind == ND_REDIR_IN || node->kind == ND_REDIR_HEREDOC)
	{
		if (dup2(node->stashed_std_fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	close(node->stashed_std_fd);
}

void	reset_all_redirects(t_node *redirects)
{
	int		count;
	int		i;
	t_node	*tmp;
	t_node	**array;

	count = 0;
	tmp = redirects;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(t_node*) * count);
	if (!array)
		fatal_error("malloc");
	tmp = redirects;
	i = 0;
	while (tmp)
	{
		array[i++] = tmp;
		tmp = tmp->next;
	}
	i = count - 1;
	while (i >= 0)
	{
		reset_redirect(array[i]);
		i--;
	}
	free(array);
}
