// execute.c

#include "minishell.h"

static void execcmd(t_node *node)
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
	if (execve(path, argv, NULL))
	{
		free_argv(argv);
		free(path);
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES || errno == ENOEXEC)
			exit(126);
		else
			exit(EXIT_FAILURE);
	}
}

int	execute(t_node *node)
{
	pid_t	pid;
	int		status;

	if (!node)
		return (0);
	status = 0;
	if (has_pipe(node))
		return (exec_pipeline(node));
	redirect(node->redirects, NULL);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	if (pid == 0)
		execcmd(node);
	waitpid(pid, &status, 0);
	reset_redirect(node->redirects);
	return (WEXITSTATUS(status));
}
