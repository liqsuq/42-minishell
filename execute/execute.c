/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:43:05 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/05 13:09:02 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_data *data, t_node *node)
{
	char	**argv;
	char	path[PATH_MAX];
	char	**envp;
	int		error;

	if (setup_redirect(node->redirects) != 0)
		exit(EXIT_FAILURE);
	if (node->args == NULL || node->args->word == NULL)
		exit(EXIT_SUCCESS);
	argv = new_argv(node->args);
	if (argv == NULL)
		fatal_error("new_argv", strerror(errno));
	if (find_path(data->env, path, argv[0]) == NULL)
		exit(ERROR_NOFILE);
	envp = dump_environ(data->env);
	if (envp == NULL)
		fatal_error("dump_environ", strerror(errno));
	execve(path, argv, envp);
	error = errno;
	ft_dprintf(STDERR, HEADER "%s\n", strerror(error));
	if (error == ENOENT)
		exit(ERROR_NOFILE);
	else if (errno == EACCES || errno == ENOEXEC)
		exit(ERROR_NOPERM);
	exit(EXIT_FAILURE);
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
			return (i + 1);
	return (0);
}

void	execute_builtin(t_data *data, t_node *node)
{
	char	**argv;
	void	(*func[7])(t_data *, char **);

	func[0] = builtin_echo;
	func[1] = builtin_cd;
	func[2] = builtin_pwd;
	func[3] = builtin_export;
	func[4] = builtin_unset;
	func[5] = builtin_env;
	func[6] = builtin_exit;
	argv = new_argv(node->args);
	if (argv == NULL)
		fatal_error("new_argv", strerror(errno));
	if (setup_redirect(node->redirects) == 0)
		func[is_builtin(node->args) - 1](data, argv);
	else
		data->exit_status = EXIT_FAILURE;
	reset_redirect(node->redirects);
	free_argv(&argv);
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

	if (node == NULL)
		return ;
	if (node->next == NULL && is_builtin(node->args))
		execute_builtin(data, node);
	else
	{
		pid = pipeline(data, node, -1);
		wait_pids(data, pid);
	}
}
