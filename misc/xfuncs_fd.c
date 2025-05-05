/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfuncs_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:14:41 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/05 13:03:01 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	xwrite(int fd, const void *buf, size_t count)
{
	if (write(fd, buf, count) < 0)
		fatal_error("write", strerror(errno));
}

void	xclose(int fd)
{
	if (fd >= 0 && close(fd) < 0)
		fatal_error("close", strerror(errno));
}

void	xpipe(int *fd)
{
	if (pipe(fd) < 0)
		fatal_error("pipe", strerror(errno));
}

int	xdup(int oldfd)
{
	int	fd;

	fd = dup(oldfd);
	if (fd < 0)
		fatal_error("dup", strerror(errno));
	return (fd);
}

void	xdup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
		fatal_error("dup2", strerror(errno));
}
