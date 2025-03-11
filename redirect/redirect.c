// redirect.c

#include "../minishell.h"

static void open_redirect(t_node *node, int srcfd, int flags, mode_t mode)
{
	int dstfd;

	dstfd = open(node->filename->word, flags, mode);
	if (dstfd < 0)
		fatal_error("open");
	node->stashed_std_fd = dup(srcfd);
	if (node->stashed_std_fd < 0)
		fatal_error("dup");
	if (dup2(dstfd, srcfd) < 0)
		fatal_error("dup2");
	close(dstfd);
}

static int	read_heredoc(const char *delimiter, bool is_delimiter_quote, void *env)
{
	int		pipefd[2];
	char	*line;

	(void)env;                 // 今は使わないので無視
	(void)is_delimiter_quote;  // 今は使わないので無視
	if (pipe(pipefd) < 0)
		fatal_error("pipe");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		ft_dprintf(pipefd[1], "%s\n", line);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

// node->filename(or node->delimiter)->word にはヒアドキュメントのデリミタが入っている想定
// 例: "EOF" など
// heredocで入力をpipeにためて、その読み口をSTDINに差し替え
// printf("%s\n", node->delimiter->word);
static void	open_heredoc(t_node *node, t_env **env)
{
	int fd;

	fd = read_heredoc("EOF", false, env); // "EOF あとで置き換える元々(node->delimiter->word)
	if (fd < 0)
		fatal_error("read_heredoc");
	node->stashed_std_fd = dup(STDIN_FILENO);
	if (node->stashed_std_fd < 0)
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
