// pipeline.c

#include "minishell.h"

static int	has_pipe(t_node *node)
{
	return (node->next != NULL);
}

static void	close_fd(int fd)
{
	close(fd);
}

static void	move_fd(int src, int dst)
{
	dup2(src, dst);
	close_fd(src);
}

int	pipeline(t_node *node, int prev_pipeout)
{
	int		pipefd[2];
	pid_t	pid;

	if (has_pipe(node))
		if (pipe(pipefd) < 0)
			fatal_error("pipe");
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	if (pid == 0)
	{
		if (prev_pipeout != -1)
			move_fd(prev_pipeout, STDIN_FILENO);
		if (has_pipe(node))
		{
			close_fd(pipefd[0]);
			move_fd(pipefd[1], STDOUT_FILENO);
		}
		execute_command(node);
	}
	if (prev_pipeout != -1)
		close_fd(prev_pipeout);
	if (has_pipe(node))
		close_fd(pipefd[1]);
	if (has_pipe(node))
		return (pipeline(node->next, pipefd[0]));
	return (pid);
}
