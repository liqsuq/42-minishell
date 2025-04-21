// execute.c

#include "minishell.h"

void	execute_command(t_data *data, t_node *node)
{
	char	**argv;
	char	*path;
	char 	**envp;

	argv = new_argv(node->args);
	if (argv == NULL)
		exit(EXIT_FAILURE);
	path = resolve_path(data->env, argv[0]);
	if (path == NULL)
	{
		free_argv(argv);
		exit(ERROR_NOFILE);
	}
	envp = dump_env(data->env);
	redirect(node->redirects, &data->env);
	execve(path, argv, envp);
	reset_redirect(node->redirects);
	free_argv(argv);
	free_envp(envp);
	free(path);
	if (errno == ENOENT)
		exit(ERROR_NOFILE);
	else if (errno == EACCES || errno == ENOEXEC)
		exit(ERROR_NOPERM);
	else
		exit(EXIT_FAILURE);
}

int	is_builtin(t_token *args)
{
	char *const	cmd[] = {"exit", "echo", "unset", "env", "export"};
	size_t		i;

	if (args == NULL)
		return (0);
	i = -1;
	while (++i < sizeof(cmd) / sizeof(*cmd))
		if (ft_strncmp(args->word, cmd[i], ft_strlen(cmd[i])) == 0)
			return (1);
	return (0);
}

void	execute_builtin(t_data *data, t_node *node)
{
	char	**argv;

	(void)data;
	argv = new_argv(node->args);
	if (argv == NULL)
		exit(EXIT_FAILURE);
	redirect(node->redirects, NULL);
	if (ft_strncmp(node->args->word, "exit", 5) == 0)
		builtin_exit(data, argv);
	else if (ft_strncmp(node->args->word, "export", 7) == 0)
		builtin_export(data, argv);
	else if (ft_strncmp(node->args->word, "echo", 5) == 0)
		builtin_echo(data, argv);
	else if (ft_strncmp(node->args->word, "unset", 6) == 0)
		builtin_unset(data, argv);
	else if (ft_strncmp(node->args->word, "env", 4) == 0)
		builtin_env(data);
	reset_redirect(node->redirects);
	free_argv(argv);
}

static void	wait_pids(t_data *data, pid_t pid)
{
	pid_t	wpid;
	int		status;

	while (1)
	{
		wpid = wait(&status);
		if (wpid == pid)
		{
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					ft_dprintf(STDERR_FILENO, "Quit\n");
				data->exit_status = WTERMSIG(status) + 128;
			}
		}
		else if (wpid < 0)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				ft_dprintf(STDERR_FILENO, "\n");
		}
	}
}

void	execute(t_data *data, t_node *node)
{
	pid_t	pid;

	if (node == NULL)
	{
		data->exit_status = 1;
		return ;
	}
	if (node->next == NULL && is_builtin(node->args))
		execute_builtin(data, node);
	else 
	{	
		pid = pipeline(data, node, -1);
		wait_pids(data, pid);
	}
}
