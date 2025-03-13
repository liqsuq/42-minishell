// execute.c

#include "minishell.h"

void execute_command(t_node *node)
{
	char **argv;
	char *path;

	argv = new_argv(node->args);
	if (!argv[0])
	{
		free_argv(argv);
		exit (1);
	}
	path = resolve_path(argv[0]);
	if (!path)
	{
		free_argv(argv);
		exit (127);
	}
	redirect(node->redirects, NULL);
	execve(path, argv, NULL);
	reset_redirect(node->redirects);
	free_argv(argv);
	free(path);
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES || errno == ENOEXEC)
		exit(126);
	else
		exit(EXIT_FAILURE);
}

int	execute(t_node *node)
{
	pid_t	pid;
	int		status;

	if (node == NULL)
		return (1);
	pid = pipeline(node, -1);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
