// main.c
#include "minishell.h"

static int	get_next_dir(const char **env_path, char *buf)
{
	const char	*start;
	const char	*p;
	size_t		len;

	start = *env_path;
	if (!*start)
		return (0);
	p = start;
	while (*p && *p != ':')
		p++;
	len = p - start;
	if (len >= PATH_MAX)
		len = PATH_MAX - 1;
	ft_memcpy(buf, start, len);
	buf[len] = '\0';
	if (*p == ':')
		*env_path = p + 1;
	else
		*env_path = p;
	return (1);
}

static void	join_filename(char *dir, const char *filename)
{
	size_t	i;
	size_t	fn;

	i = 0;
	fn = 0;
	while (dir[i] != '\0' && i < PATH_MAX - 1)
		i++;
	if (i < PATH_MAX - 1)
		dir[i++] = '/';
	while (filename[fn] && i < PATH_MAX - 1)
	{
		dir[i] = filename[fn];
		i++;
		fn++;
	}
	dir[i] = '\0';
}

char	*search_path(const char *filename)
{
	char		dir[PATH_MAX];
	const char	*env_value;

	env_value = getenv("PATH");
	if (!env_value || !*env_value)
		return (NULL);
	while (1)
	{
		ft_memset(dir, 0, PATH_MAX);
		if (!get_next_dir(&env_value, dir))
			break ;
		join_filename(dir, filename);
		if (access(dir, X_OK) == 0)
		{
			char	*dup_path;
			dup_path = ft_strdup(dir);
			if (!dup_path)
				fatal_error("strdup");
			return (dup_path);
		}
	}
	return (NULL);
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

int	exec_command(char *path, char **argv)
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

char	**tokens2argv(t_token *tokens)
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

void	free_argv(char **argv)
{
	char	**cur;

	cur = argv;
	while (*cur != NULL)
		free(*cur++);
	free(argv);
}

int	interpret(char *line)
{
	int		status;
	t_token	*tokens;
	t_node	*nodes;

	status = 0;
	tokens = tokenize(line);
	nodes = parse(tokens);
	if (syntax_error == 1)
		status = ERROR_SYNTAX;
	else
	{
		status = exec_nodes(nodes);
	}
	free_nodes(nodes);
	free_tokens(tokens);
	return (status);
}

int	main(void)
{
	char	*line;
	int		last_status;

	last_status = 0;
	rl_outstream = stderr;
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (*line)
		{
			add_history(line);
			last_status = interpret(line);
		}
		free(line);
	}
	return (last_status);
}
