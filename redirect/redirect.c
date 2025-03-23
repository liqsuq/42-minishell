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

	if (pipe(pipefd) < 0)
		fatal_error("pipe");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (is_quoted)
		{
		    if (ft_strcmp(line, delim) == 0)
		    {
		      free(line);
		      break ;
		    }
		}
		else
		{
		  // char *expanded = expand_variables(line); // 環境変数展開
		  // if (ft_strcmp(expanded, delim) == 0)
		  // {
		  //     free(expanded);
		  //     free(line);
		  //     break ;
		  // }
		  // free(expanded);
			// printf("Delimiter: [%s]\n", delim);
			// printf("Line: [%s]\n", line);
			if (ft_strcmp(line, delim) == 0)
      {
        free(line);
        break;
      }
		}
		// ヒアドキュメントの内容をパイプに書き込む
		if (*line != '\0')
		  ft_dprintf(pipefd[1], "%s\n", line);
		else
		  ft_dprintf(pipefd[1], "\n");
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

// node->args->word にはヒアドキュメントのデリミタが入っている想定
// 例: "EOF" など
// heredocで入力をpipeにためて、その読み口をSTDINに差し替え
// printf("%s\n", node->args->word);
static void open_heredoc(t_node *redi, t_env **env)
{
  int fd;
	(void)env;

  // 例: node->args->word に "<< XXX" の XXX 部分が入っている
  const char *delim = redi->args->word;

  // 「実装例として、シングルクオート含むかどうかだけで判定」
  // もちろん厳密には parse 時に is_quoted をセットする方法が正確
  bool quoted = false;
  if (delim[0] == '\'' || delim[0] == '"')
    quoted = true;

	// printf("Delimiter: [%s]\n", delim);
	// printf("quoted: [%d]\n", quoted);

  fd = read_heredoc(delim, quoted, NULL);
	// printf("-----------------");
	// printf("fd: [%d]\n", fd);
  if (fd < 0)
    fatal_error("read_heredoc");

  // ↓以下は既存の通り
  redi->stashed_fd = dup(STDIN_FILENO);
  if (redi->stashed_fd < 0)
    fatal_error("dup");
  if (dup2(fd, STDIN_FILENO) < 0)
    fatal_error("dup2");
  close(fd);
}

void redirect(t_node *redi, t_env **env)
{
	if (redi == NULL)
		return;

	// デバッグ出力：現在処理しているリダイレクトの種類
	printf("Processing redirect: kind = %d, args = %s\n",
		redi->kind, redi->args ? redi->args->word : "(null)");

	if (redi->kind == ND_REDIR_OUT)
		open_redirect(redi, STDOUT_FILENO, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redi->kind == ND_REDIR_IN)
		open_redirect(redi, STDIN_FILENO, O_RDONLY, 0644);
	else if (redi->kind == ND_REDIR_APPEND)
		open_redirect(redi, STDOUT_FILENO, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redi->kind == ND_REDIR_HEREDOC)  // 明示的にヒアドキュメントを処理
	{
		printf("Processing heredoc for [%s]\n", redi->args->word);
		open_heredoc(redi, env);
	}

	// 再帰的に次のリダイレクトを処理
	redirect(redi->next, env);
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
