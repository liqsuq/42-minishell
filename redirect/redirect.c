// redirect.c

#include "../minishell.h"

static void	open_redirect(t_node *redi, int srcfd, int flags, mode_t mode)
{
	int	dstfd;

	dstfd = open(redi->args->word, flags, mode);
	if (dstfd < 0)
		fatal_error("open");
	redi->stashed_fd = dup(srcfd);
	if (redi->stashed_fd < 0)
		fatal_error("dup");
	if (dup2(dstfd, srcfd) < 0)
		fatal_error("dup2");
	close(dstfd);
}

void redirect(t_node *redi, t_env **env)
{
	if (redi == NULL)
		return;
	if (redi->kind == ND_REDIR_OUT)
		open_redirect(redi, STDOUT_FILENO, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redi->kind == ND_REDIR_IN)
		open_redirect(redi, STDIN_FILENO, O_RDONLY, 0644);
	else if (redi->kind == ND_REDIR_APPEND)
		open_redirect(redi, STDOUT_FILENO, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redi->kind == ND_REDIR_HEREDOC)
	setup_heredoc_input(redi);
	return (redirect(redi->next, env));
}

void	reset_redirect(t_node *redi)
{
	int	fd;

	if (redi == NULL)
		return ;
	reset_redirect(redi->next);
	if (redi->kind == ND_REDIR_IN || redi->kind == ND_REDIR_HEREDOC)
		fd = STDIN_FILENO;
	else
		fd = STDOUT_FILENO;
	if (dup2(redi->stashed_fd, fd) < 0)
		fatal_error("dup2");
	close(redi->stashed_fd);
}
