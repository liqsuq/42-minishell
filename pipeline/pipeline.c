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

int	pipeline(t_data *data, t_node *node, int prev_pipeout)
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
		reset_signal();
		if (prev_pipeout != -1)
			move_fd(prev_pipeout, STDIN_FILENO);
		if (has_pipe(node))
		{
			close_fd(pipefd[0]);
			move_fd(pipefd[1], STDOUT_FILENO);
		}
		if (is_builtin(node->args))
			execute_builtin(data, node);
		else
		execute_command(data, node);
	}
	if (prev_pipeout != -1)
		close_fd(prev_pipeout);
	if (has_pipe(node))
		close_fd(pipefd[1]);
	if (has_pipe(node))
		return (pipeline(data, node->next, pipefd[0]));
	return (pid);
}
