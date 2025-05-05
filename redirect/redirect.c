/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:46:34 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/06 00:03:31 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_heredoc(int fd, t_token *token)
{
	if (token == NULL)
		return ;
	xwrite(fd, token->word, ft_strlen(token->word));
	xwrite(fd, "\n", 1);
	write_heredoc(fd, token->next);
}

static int	open_heredoc(t_node *redi)
{
	int	pipefd[2];

	xpipe(pipefd);
	write_heredoc(pipefd[1], redi->args->next);
	xclose(pipefd[1]);
	return (pipefd[0]);
}

int	open_redirect(t_node *re)
{
	if (re == NULL)
		return (0);
	if (re->kind == ND_REDIR_OUT)
		re->dstfd = open(re->args->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (re->kind == ND_REDIR_IN)
		re->dstfd = open(re->args->word, O_RDONLY, 0644);
	else if (re->kind == ND_REDIR_APPEND)
		re->dstfd = open(re->args->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (re->kind == ND_REDIR_HEREDOC)
		re->dstfd = open_heredoc(re);
	if (re->dstfd < 0)
		return (ft_dprintf(STDERR, HEADER "open: %s\n", strerror(errno)), 1);
	return (open_redirect(re->next));
}

void	setup_redirect(t_node *redi)
{
	int	fd;

	if (redi == NULL)
		return ;
	if (redi->kind == ND_REDIR_OUT || redi->kind == ND_REDIR_APPEND)
		fd = STDOUT;
	else
		fd = STDIN;
	redi->bakfd = xdup(fd);
	xdup2(redi->dstfd, fd);
	xclose(redi->dstfd);
	setup_redirect(redi->next);
}

void	reset_redirect(t_node *redi)
{
	int	fd;

	if (redi == NULL || redi->bakfd < 0)
		return ;
	reset_redirect(redi->next);
	if (redi->kind == ND_REDIR_IN || redi->kind == ND_REDIR_HEREDOC)
		fd = STDIN;
	else
		fd = STDOUT;
	xdup2(redi->bakfd, fd);
	xclose(redi->bakfd);
}
