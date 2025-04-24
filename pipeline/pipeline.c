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

static void open_pipe(t_node *node, int *pipefd)
{
	if (has_pipe(node))
		if (pipe(pipefd) < 0)
			fatal_error("setup_pipe");
}

static void attach_pipe(t_node *node, int prev_pipeout, int *pipefd)
{
	if (prev_pipeout != -1)
		move_fd(prev_pipeout, STDIN_FILENO);
	if (has_pipe(node))
	{
		close_fd(pipefd[0]);
		move_fd(pipefd[1], STDOUT_FILENO);
	}
}

static void detach_pipe(t_node *node, int prev_pipeout, int *pipefd)
{
	if (prev_pipeout != -1)
		close_fd(prev_pipeout);
	if (has_pipe(node))
		close_fd(pipefd[1]);
}

int	pipeline(t_data *data, t_node *node, int prev_pipeout)
{
	int		pipefd[2];
	pid_t	pid;

	open_pipe(node, pipefd);	
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	if (pid == 0)
	{
		attach_pipe(node, prev_pipeout, pipefd);
		reset_signal();
		if (!is_builtin(node->args))
			execute_command(data, node);
		execute_builtin(data, node);
		exit(data->exit_status);
	}
	detach_pipe(node, prev_pipeout, pipefd);
	if (has_pipe(node))
		return (pipeline(data, node->next, pipefd[0]));
	return (pid);
}
