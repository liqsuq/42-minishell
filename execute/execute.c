// execute.c

#include "minishell.h"

// static void execcmd(t_node *node)
// {
// 	char **argv;
// 	char *path;
	
// 	argv = new_argv(node->args);
// 	if (!argv[0])
// 	{
// 		free_argv(argv);
// 		return (0);
// 	}
// 	path = resolve_path(argv[0]);
// 	if (!path)
// 	{
// 		free_argv(argv);
// 		return (127);
// 	}
// 	if (execve(path, argv, NULL))
// 	{
// 		if (errno == ENOENT)
// 			exit(127);
// 		else if (errno == EACCES || errno == ENOEXEC)
// 			exit(126);
// 		else
// 			exit(EXIT_FAILURE);
// 	}
// }

static int	exec_command(char *path, char **argv)
{
	extern char	**environ;
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	if (pid == 0)
	{
		execve(path, argv, environ);
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES || errno == ENOEXEC)
			exit(126);
		else
			exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	execute(t_node *node)
{
	int	status;
	char **argv;

	if (!node)
		return (0);
	argv = new_argv(node->args);
	if (!argv[0])
	{
		free_argv(argv);
		return (0);
	}
	status = 0;
	if (has_pipe(node))
		return (exec_pipeline(node));
	else
	{
		redirect(node->redirects, NULL);
		char	*path = resolve_path(argv[0]);
		if (!path)
			status = 127;
		else
		{
			status = exec_command(path, argv);
			free(path);
		}
		free_argv(argv);
		reset_redirect(node->redirects);
		return (status);
	}
}
