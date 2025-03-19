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

static int	read_heredoc(const char *delim, bool is_quoted, void *env)
{
	int		pipefd[2];
	char	*line;

	// 今は使わないので無視
	(void)env;
	(void)is_quoted;
	if (pipe(pipefd) < 0)
		fatal_error("pipe");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_dprintf(pipefd[1], "%s\n", line);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

// node->args->word にはヒアドキュメントのデリミタが入っている想定
// 例: "EOF" など
// heredocで入力をpipeにためて、その読み口をSTDINに差し替え
// printf("%s\n", node->args->word);
static void	open_heredoc(t_node *redi, t_env **env)
{
	int	fd;

	fd = read_heredoc("EOF", false, env); // "EOF あとで置き換える元々(node->delimiter->word)
	if (fd < 0)
		fatal_error("read_heredoc");
	redi->stashed_fd = dup(STDIN_FILENO);
	if (redi->stashed_fd < 0)
		fatal_error("dup");
	if (dup2(fd, STDIN_FILENO) < 0)
		fatal_error("dup2");
	close(fd);
}

void	redirect(t_node *redi, t_env **env)
{
	if (redi == NULL)
		return ;
	if (redi->kind == ND_REDIR_OUT)
		open_redirect(redi, STDOUT_FILENO, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redi->kind == ND_REDIR_IN)
		open_redirect(redi, STDIN_FILENO, O_RDONLY, 0644);
	else if (redi->kind == ND_REDIR_APPEND)
		open_redirect(redi, STDOUT_FILENO, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redi->kind == ND_REDIR_HEREDOC)
		open_heredoc(redi, env);
	return (redirect(redi->next, env));
}

void	reset_redirect(t_node *redi)
{
	int	fd;

	if (redi == NULL)
		return ;
	reset_redirect(redi->next);
	if (redi->kind == ND_REDIR_OUT || redi->kind == ND_REDIR_APPEND)
		fd = STDOUT_FILENO;
	else if (redi->kind == ND_REDIR_IN || redi->kind == ND_REDIR_HEREDOC)
		fd = STDIN_FILENO;
	if (dup2(redi->stashed_fd, fd) < 0)
		fatal_error("dup2");
	close(redi->stashed_fd);
}
