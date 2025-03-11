// execute.c

#include "minishell.h"

static int	exec_command(char *path, char **argv)
{
	extern char	**environ;
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error:");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(path, argv, environ);
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES || errno == ENOEXEC)
			exit(126);
		else
			exit(EXIT_FAILURE);
	}
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}

int	execute(t_node *node)
{
	int	status;

	status = 0;
	if (!node)
		return (0);
	if (has_pipe(node))
		return (exec_pipeline(node));
	else
	{
		perform_all_redirects(node->redirects);
		char	**argv = new_argv(node->args);
		if (!argv[0])
		{
			reset_all_redirects(node->redirects);
			free_argv(argv);
			return (0);
		}
		char	*path = resolve_path(argv[0]);
		if (!path)
			status = 127;
		else
		{
			status = exec_command(path, argv);
			free(path);
		}
		free_argv(argv);
		reset_all_redirects(node->redirects);
		return (status);
	}
}
