// interpret.c

#include "minishell.h"

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

int exec_command(char *path, char **argv)
{
	pid_t pid;
	int wstatus;

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

char **tokens2argv(t_token *tokens)
{
	t_token	*cur;
	char	**argv;
	int		i;

	i = 0;
	cur = tokens;
	while (cur != NULL)
	{
		cur = cur->next;
		i++;
	}
	argv = malloc((i + 1) * sizeof(char *));
	if (argv == NULL)
		fatal_error("malloc");
	i = 0;
	cur = tokens;
	while (cur != NULL)
	{
		argv[i++] = ft_strdup(cur->word);
		cur = cur->next;
	}
	argv[i] = NULL;
	return (argv);
}

void free_argv(char **argv)
{
	char **cur;

	cur = argv;
	while (*cur != NULL)
		free(*cur++);
	free(argv);
}

int interpret(char *line)
{
	char	*path;
	int 	status;
	t_token	*tokens;
	char	**argv;

	tokens = tokenize(line);
	if (syntax_error == 1)
		status = ERROR_TOKENIZE;
	else
	{
		expand(tokens);
		argv = tokens2argv(tokens);
		path = resolve_path(argv[0]);
		if (!path)
			return (127);
		status = exec_command(path, argv);
		free(path);
		free_argv(argv);
	}
	free_tokens(tokens);
	return (status);
}
