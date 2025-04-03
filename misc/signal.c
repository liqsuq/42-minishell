// signal.c

#include "minishell.h"

volatile sig_atomic_t	g_signal;

static void signal_handler(int sig)
{
	g_signal = sig;
	write(2, "\n", 1);
}

int check_signal_main(void)
{
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (0);
}

int check_signal_heredoc(void)
{
	if (g_signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}

void setup_signal(void)
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigact.sa_handler = signal_handler;
	if (sigaction(SIGINT, &sigact, NULL) < 0)
		fatal_error("sigaction");
	sigact.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sigact, NULL) < 0)
		fatal_error("sigaction");
}

void reset_signal(void)
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigact.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sigact, NULL) < 0)
		fatal_error("sigaction");
	if (sigaction(SIGQUIT, &sigact, NULL) < 0)
		fatal_error("sigaction");
}
