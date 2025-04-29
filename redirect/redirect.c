// redirect.c

#include "../minishell.h"

static void	open_redirect(t_node *redi, int srcfd, int flags, mode_t mode)
{
	int	dstfd;

	dstfd = open(redi->args->word, flags, mode);
	if (dstfd < 0)
		fatal_error(redi->args->word);
	redi->stashed_fd = dup(srcfd);
	if (redi->stashed_fd < 0)
		fatal_error("dup");
	if (dup2(dstfd, srcfd) < 0)
		fatal_error("dup2");
	close(dstfd);
}

static void	write_heredoc(int fd, t_token *token)
{
	if (token == NULL)
		return ;
	write(fd, token->word, ft_strlen(token->word));
	write(fd, "\n", 1);
	write_heredoc(fd, token->next);
}

static void	open_heredoc(t_node *redi)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		fatal_error("pipe");
	write_heredoc(pipefd[1], redi->args->next);
	close(pipefd[1]);
	redi->stashed_fd = dup(STDIN);
	if (redi->stashed_fd < 0)
		fatal_error("dup");
	if (dup2(pipefd[0], STDIN) < 0)
		fatal_error("dup2");
	close(pipefd[0]);
}

void	setup_redirect(t_node *redi, t_env **env)
{
	if (redi == NULL)
		return ;
	if (redi->kind == ND_REDIR_OUT)
		open_redirect(redi, STDOUT, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redi->kind == ND_REDIR_IN)
		open_redirect(redi, STDIN, O_RDONLY, 0644);
	else if (redi->kind == ND_REDIR_APPEND)
		open_redirect(redi, STDOUT, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redi->kind == ND_REDIR_HEREDOC)
		open_heredoc(redi);
	return (setup_redirect(redi->next, env));
}

void	reset_redirect(t_node *redi)
{
	int	fd;

	if (redi == NULL)
		return ;
	reset_redirect(redi->next);
	if (redi->kind == ND_REDIR_IN || redi->kind == ND_REDIR_HEREDOC)
		fd = STDIN;
	else
		fd = STDOUT;
	if (dup2(redi->stashed_fd, fd) < 0)
		fatal_error("dup2");
	close(redi->stashed_fd);
}
