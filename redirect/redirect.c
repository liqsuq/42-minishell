// redirect.c

#include "../minishell.h"

static void open_redirect(t_node *node, int fd, int flags, mode_t mode)
{
	node->filefd = open(node->filename->word, flags, mode);
	if (node->filefd < 0)
		fatal_error("open");
	node->stashed_std_fd = dup(fd);
	if (node->stashed_std_fd < 0)
		fatal_error("dup");
	if (dup2(node->filefd, fd) < 0)
		fatal_error("dup2");
	close(node->filefd);
	node->filefd = -1;
}

static int	read_heredoc(const char *delimiter, bool is_delimiter_quote, void *env)
{
	int		pipefd[2];
	char	*line;

	(void)env;                 // 今は使わないので無視
	(void)is_delimiter_quote;  // 今は使わないので無視
	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		dprintf(pipefd[1], "%s\n", line);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

static void	redirect_heredoc(t_node *node, t_env **env)
{
	// node->filename(or node->delimiter)->word にはヒアドキュメントのデリミタが入っている想定
	// 例: "EOF" など
	// heredocで入力をpipeにためて、その読み口をSTDINに差し替え
	// printf("%s\n", node->delimiter->word);
	node->filefd = read_heredoc("EOF", false, env); // "EOF あとで置き換える元々(node->delimiter->word)
	if (node->filefd < 0)
	{
		perror("heredoc");
		exit(EXIT_FAILURE);
	}
	node->stashed_std_fd = dup(STDIN_FILENO);
	if (node->stashed_std_fd < 0)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
	if (dup2(node->filefd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(node->filefd);
	node->filefd = -1;
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
		redirect_heredoc(redi, env);
	return (redirect(redi->next, env));
}
