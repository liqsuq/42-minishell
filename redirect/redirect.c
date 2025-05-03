/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:46:34 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/03 19:32:04 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_redirect(t_node *redi, int srcfd, int flags, mode_t mode)
{
	int	dstfd;

	dstfd = open(redi->args->word, flags, mode);
	if (dstfd < 0)
	{
		ft_dprintf(STDERR, HEADER "open: %s\n", strerror(errno));
		return (errno);
	}
	redi->stashed_fd = dup(srcfd);
	if (redi->stashed_fd < 0)
		fatal_error("dup", strerror(errno));
	if (dup2(dstfd, srcfd) < 0)
		fatal_error("dup2", strerror(errno));
	if (close(dstfd) < 0)
		fatal_error("close", strerror(errno));
	return (0);
}

static void	write_heredoc(int fd, t_token *token)
{
	if (token == NULL)
		return ;
	if (write(fd, token->word, ft_strlen(token->word)) < 0)
		fatal_error("write", strerror(errno));
	if (write(fd, "\n", 1) < 0)
		fatal_error("write", strerror(errno));
	write_heredoc(fd, token->next);
}

static void	open_heredoc(t_node *redi)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		fatal_error("pipe", strerror(errno));
	write_heredoc(pipefd[1], redi->args->next);
	if (close(pipefd[1]) < 0)
		fatal_error("close", strerror(errno));
	redi->stashed_fd = dup(STDIN);
	if (redi->stashed_fd < 0)
		fatal_error("dup", strerror(errno));
	if (dup2(pipefd[0], STDIN) < 0)
		fatal_error("dup2", strerror(errno));
	if (close(pipefd[0]) < 0)
		fatal_error("close", strerror(errno));
}

int	setup_redirect(t_node *redi)
{
	int	ret;

	ret = 0;
	if (redi == NULL)
		return (0);
	if (redi->kind == ND_REDIR_OUT)
		ret = open_redirect(redi, STDOUT, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redi->kind == ND_REDIR_IN)
		ret = open_redirect(redi, STDIN, O_RDONLY, 0644);
	else if (redi->kind == ND_REDIR_APPEND)
		ret = open_redirect(redi, STDOUT, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redi->kind == ND_REDIR_HEREDOC)
		open_heredoc(redi);
	if (ret != 0)
		return (ret);
	return (setup_redirect(redi->next));
}

void	reset_redirect(t_node *redi)
{
	int	fd;

	if (redi == NULL || redi->stashed_fd < 0)
		return ;
	reset_redirect(redi->next);
	if (redi->kind == ND_REDIR_IN || redi->kind == ND_REDIR_HEREDOC)
		fd = STDIN;
	else
		fd = STDOUT;
	if (dup2(redi->stashed_fd, fd) < 0)
		fatal_error("dup2", strerror(errno));
	if (close(redi->stashed_fd) < 0)
		fatal_error("close", strerror(errno));
}
