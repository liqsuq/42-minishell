/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfuncs_sys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:37:53 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/05 14:48:44 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*xcalloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (ptr == NULL)
		fatal_error("malloc", strerror(errno));
	return (ptr);
}

pid_t	xfork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		fatal_error("fork", strerror(errno));
	return (pid);
}

void	xsigaction(int sig, const struct sigaction *new, struct sigaction *old)
{
	if (sigaction(sig, new, old) < 0)
		fatal_error("sigaction", strerror(errno));
}
