/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:46:27 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/05 23:56:42 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_pipe(t_node *node)
{
	return (node->next != NULL);
}

static void	attach_pipe(t_node *node, int prev_pipeout, int *pipefd)
{
	if (prev_pipeout != -1)
	{
		xdup2(prev_pipeout, STDIN);
		xclose(prev_pipeout);
	}
	if (has_pipe(node))
	{
		xclose(pipefd[0]);
		xdup2(pipefd[1], STDOUT);
		xclose(pipefd[1]);
	}
}

static void	detach_pipe(t_node *node, int prev_pipeout, int *pipefd)
{
	if (prev_pipeout != -1)
		xclose(prev_pipeout);
	if (has_pipe(node))
		xclose(pipefd[1]);
}

int	pipeline(t_data *data, t_node *node, int prev_pipeout)
{
	int		pipefd[2];
	pid_t	pid;

	if (has_pipe(node))
		xpipe(pipefd);
	pid = xfork();
	if (pid == 0)
	{
		attach_pipe(node, prev_pipeout, pipefd);
		reset_signal();
		if (open_redirect(node->redirects))
			exit(EXIT_FAILURE);
		if (!is_builtin(node->args))
			execute_command(data, node);
		execute_builtin(data, node);
		exit(data->exit_status);
	}
	detach_pipe(node, prev_pipeout, pipefd);
	if (has_pipe(node))
		return (pipeline(data, node->next, pipefd[0]));
	return (pid);
}
