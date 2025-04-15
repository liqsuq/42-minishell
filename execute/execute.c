// execute.c

#include "minishell.h"

void	execute_command(t_data *data, t_node *node)
{
	char	**argv;
	char	*path;
	char 	**envp;

	argv = new_argv(node->args);
	if (argv == NULL)
		exit(1);
	path = resolve_path(data->env, argv[0]);
	if (path == NULL)
	{
		free_argv(argv);
		exit(127);
	}
	envp = dump_env(data->env);
	redirect(node->redirects, &data->env);
	execve(path, argv, envp);
	reset_redirect(node->redirects);
	free_argv(argv);
	free_envp(envp);
	free(path);
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES || errno == ENOEXEC)
		exit(126);
	else
		exit(EXIT_FAILURE);
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
	pid = pipeline(data, node, -1);
	wait_pids(data, pid);
}
