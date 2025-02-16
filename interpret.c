// interpret.c

#include "minishell.h"

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(EXIT_FAILURE);
}


char	*resolve_path(char *line)
{
	char	*path;

	if (ft_strchr(line, '/'))
	{
		path = ft_strdup(line);
		if (!path)
			return (NULL);
	}
	else
	{
		path = search_path(line);
		if (!path)
		{
			dprintf(STDERR_FILENO, "%s: command not found\n", line);
			return (NULL);
		}
	}
	return (path);
}

int exec_command(char *path)
{
	pid_t pid;
	int wstatus;
	char *argv[2];

	argv[0] = path;
	argv[1] = NULL;
	pid = fork();
	if (pid < 0)
	{
    perror("fork error:");
		exit(EXIT_FAILURE);
  }
	else if (pid == 0)
  {
		execve(path, argv, NULL);
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES || errno == ENOEXEC)
			exit(126);
		else
			exit(EXIT_FAILURE);
	} else {
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}

int interpret(char *line)
{
	char *path;
	int status;

	path = resolve_path(line);
	if (!path)
		return (127);

	status = exec_command(path);
	free(path);
	return (status);
}