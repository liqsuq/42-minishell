/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:46:04 by kadachi           #+#    #+#             */
/*   Updated: 2025/04/29 18:46:06 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal;

static void	signal_handler(int sig)
{
	g_signal = sig;
}

int	check_signal_main(void)
{
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (0);
}

int	check_signal_heredoc(void)
{
	if (g_signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}

void	setup_signal(void)
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigact.sa_handler = signal_handler;
	if (sigaction(SIGINT, &sigact, NULL) < 0)
		fatal_error("sigaction", strerror(errno));
	sigact.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sigact, NULL) < 0)
		fatal_error("sigaction", strerror(errno));
}

void	reset_signal(void)
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigact.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sigact, NULL) < 0)
		fatal_error("sigaction", strerror(errno));
	if (sigaction(SIGQUIT, &sigact, NULL) < 0)
		fatal_error("sigaction", strerror(errno));
}
