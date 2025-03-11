// pipe.c

#include "minishell.h"

int	has_pipe(t_node *node)
{
	while (node != NULL)
	{
		if (node->next != NULL)
			return (1);
		node = node->next;
	}
	return (0);
}

int	exec_pipeline(t_node *node)
{
	int		pipefd[2];
	int		prev_fd;
	int		status;
	pid_t	pid;

	prev_fd = -1;
	status = 0;
	while (node != NULL)
	{
		if (node->next != NULL)
		{
			if (pipe(pipefd) < 0)
			{
				perror("pipe");
				return (1);
			}
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (1);
		}
		else if (pid == 0)
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
			perform_all_redirects(node->redirects);
			expand(node);
			char	**argv = tokens2argv(node->args);
			if (!argv[0])
				_exit(0);
			char	*path = resolve_path(argv[0]);
			if (!path)
				_exit(127);
			execve(path, argv, NULL);
			perror("execve");
			_exit(1);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (prev_fd != -1)
				close(prev_fd);
			if (node->next != NULL)
			{
				close(pipefd[1]);
				prev_fd = pipefd[0];
			}
		}
		node = node->next;
	}
	return (WEXITSTATUS(status));
}
