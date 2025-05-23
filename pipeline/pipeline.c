/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:46:27 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/01 15:51:56 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_pipe(t_node *node)
{
	return (node->next != NULL);
}

static void	move_fd(int src, int dst)
{
	int	retval;

	retval = dup2(src, dst);
	if (retval < 0)
		fatal_error("dup2", strerror(errno));
	retval = close(src);
	if (retval < 0)
		fatal_error("close", strerror(errno));
}

static void	attach_pipe(t_node *node, int prev_pipeout, int *pipefd)
{
	int	retval;

	if (prev_pipeout != -1)
	{
		move_fd(prev_pipeout, STDIN);
	}
	if (has_pipe(node))
	{
		retval = close(pipefd[0]);
		if (retval < 0)
			fatal_error("close", strerror(errno));
		move_fd(pipefd[1], STDOUT);
	}
}

static void	detach_pipe(t_node *node, int prev_pipeout, int *pipefd)
{
	int	retval;

	if (prev_pipeout != -1)
	{
		retval = close(prev_pipeout);
		if (retval < 0)
			fatal_error("close", strerror(errno));
	}
	if (has_pipe(node))
	{
		retval = close(pipefd[1]);
		if (retval < 0)
			fatal_error("close", strerror(errno));
	}
}

int	pipeline(t_data *data, t_node *node, int prev_pipeout)
{
	int		pipefd[2];
	pid_t	pid;

	if (has_pipe(node))
		if (pipe(pipefd) < 0)
			fatal_error("pipe", strerror(errno));
	pid = fork();
	if (pid < 0)
		fatal_error("fork", strerror(errno));
	if (pid == 0)
	{
		attach_pipe(node, prev_pipeout, pipefd);
		reset_signal();
		if (!is_builtin(node->args))
			execute_command(data, node);
		execute_builtin(data, node);
		exit_shell(data, data->exit_status);
	}
	detach_pipe(node, prev_pipeout, pipefd);
	if (has_pipe(node))
		return (pipeline(data, node->next, pipefd[0]));
	return (pid);
}
