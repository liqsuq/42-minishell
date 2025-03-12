// pipeline.c

#include "minishell.h"

int	has_pipe(t_node *node)
{
	return (node->next != NULL);
}

int	exec_pipeline(t_node *node)
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
	int		status;

	prev_fd = -1;
	status = 0;
	while (node != NULL)
	{
		if (node->next != NULL)
			if (pipe(pipefd) < 0)
				fatal_error("pipe");
		redirect(node->redirects, NULL);
		pid = fork();
		if (pid < 0)
			fatal_error("fork");
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (node->next != NULL)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			execcmd(node);
		}
		waitpid(pid, &status, 0);
		reset_redirect(node->redirects);
		if (prev_fd != -1)
			close(prev_fd);
		if (node->next != NULL)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		node = node->next;
	}
	return (WEXITSTATUS(status));
}
