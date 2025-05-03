/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:43:05 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/03 19:27:33 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_data *data, t_node *node)
{
	char	**argv;
	char	path[PATH_MAX];
	char	**envp;
	int		error;

	argv = new_argv(node->args);
	if (argv == NULL)
		fatal_error("new_argv", strerror(errno));
	if (find_path(data->env, path, argv[0]) == NULL)
		(void)(free_argv(&argv), exit_shell(data, ERROR_NOFILE));
	envp = dump_environ(data->env);
	if (envp == NULL)
		fatal_error("dump_environ", strerror(errno));
	if (setup_redirect(node->redirects) != 0)
		fatal_error("open", strerror(errno));
	execve(path, argv, envp);
	error = errno;
	reset_redirect(node->redirects);
	(void)(free_argv(&argv), free_environ(&envp));
	ft_dprintf(STDERR, HEADER "%s\n", strerror(error));
	if (error == ENOENT)
		exit_shell(data, ERROR_NOFILE);
	else if (errno == EACCES || errno == ENOEXEC)
		exit_shell(data, ERROR_NOPERM);
	exit_shell(data, EXIT_FAILURE);
}

int	is_builtin(t_token *args)
{
	char *const	cmd[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	size_t		i;

	if (args == NULL)
		return (0);
	i = -1;
	while (++i < sizeof(cmd) / sizeof(*cmd))
		if (ft_strcmp(args->word, cmd[i]) == 0)
			return (1);
	return (0);
}

void	execute_builtin(t_data *data, t_node *node)
{
	char	**argv;

	argv = new_argv(node->args);
	if (argv == NULL)
		fatal_error("new_argv", strerror(errno));
	if (setup_redirect(node->redirects) != 0)
	{
		data->exit_status = EXIT_FAILURE;
		return ((void)(reset_redirect(node->redirects), free_argv(&argv)));
	}
	if (ft_strcmp(node->args->word, "echo") == 0)
		builtin_echo(data, argv);
	else if (ft_strcmp(node->args->word, "cd") == 0)
		builtin_cd(data, argv);
	else if (ft_strcmp(node->args->word, "pwd") == 0)
		builtin_pwd(data);
	else if (ft_strcmp(node->args->word, "export") == 0)
		builtin_export(data, argv);
	else if (ft_strcmp(node->args->word, "unset") == 0)
		builtin_unset(data, argv);
	else if (ft_strcmp(node->args->word, "env") == 0)
		builtin_env(data);
	else if (ft_strcmp(node->args->word, "exit") == 0)
		builtin_exit(data, argv);
	(void)(reset_redirect(node->redirects), free_argv(&argv));
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
					ft_dprintf(STDERR, "Quit\n");
				else if (WTERMSIG(status) == SIGINT)
					ft_dprintf(STDERR, "\n");
				data->exit_status = WTERMSIG(status) + 128;
			}
		}
		else if (wpid < 0 && errno == ECHILD)
			break ;
		else if (wpid < 0 && errno != EINTR)
			fatal_error("wait", strerror(errno));
	}
}

void	execute(t_data *data, t_node *node)
{
	pid_t	pid;

	if (node == NULL || node->args == NULL || node->args->word == NULL)
	{
		data->exit_status = EXIT_SUCCESS;
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
