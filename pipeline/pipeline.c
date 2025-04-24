// pipeline.c

#include "minishell.h"

static int	has_pipe(t_node *node)
{
	return (node->next != NULL);
}

static void	move_fd(int src, int dst)
{
	int	retval;

	retval = dup2(src, dst);
	if (retval < 0)
		fatal_error("dup2");
	retval = close(src);
	if (retval < 0)
		fatal_error("close");
}

static void	attach_pipe(t_node *node, int prev_pipeout, int *pipefd)
{
	int	retval;

	if (prev_pipeout != -1)
	{
		move_fd(prev_pipeout, STDIN_FILENO);
	}
	if (has_pipe(node))
	{
		retval = close(pipefd[0]);
		if (retval < 0)
			fatal_error("close");
		move_fd(pipefd[1], STDOUT_FILENO);
	}
}

static void	detach_pipe(t_node *node, int prev_pipeout, int *pipefd)
{
	int	retval;

	if (prev_pipeout != -1)
	{
		retval = close(prev_pipeout);
		if (retval < 0)
			fatal_error("close");
	}
	if (has_pipe(node))
	{
		retval = close(pipefd[1]);
		if (retval < 0)
			fatal_error("close");
	}
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
