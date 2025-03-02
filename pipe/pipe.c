#include "minishell.h"

int exec_pipeline(t_node *node)
{
	// パイプでつないだ子プロセスの pid を管理する配列 (最大256コマンド想定)
	pid_t pids[256];
	pid_t pid = fork();
	int cmd_count = 0;
	int status = 0;
	int in_fd = STDIN_FILENO;
	char **argv = tokens2argv(node->args);

	while (node)
  {
		int pipefd[2];

		// 次のコマンドがあるならパイプを作る
		if (node->next)
		{
			if (pipe(pipefd) < 0)
			{
				perror("pipe");
				exit(1);
			}
		}

		if (pid < 0)
		{
			perror("fork");
			exit(1);
		}

		if (pid == 0)
    {
			// 前のパイプの読み口を標準入力に差し替え
			if (in_fd != STDIN_FILENO)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			// 次のコマンドがあるなら、出力を pipefd[1] に差し替え
			if (node->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			// コマンド実行 (execvp)
			execvp(argv[0], argv);
			// 失敗時
			perror("execvp");
			exit(127);
		}
    else
    {
			pids[cmd_count++] = pid;
			// 使い終わった fd を閉じる
			if (in_fd != STDIN_FILENO)
			{
				close(in_fd);
			}
			// 次のコマンドがあるなら pipefd[0] が次の in_fd
			if (node->next)
			{
				close(pipefd[1]);
				in_fd = pipefd[0];
			}
			node = node->next;
		}
	}

	// 全ての子プロセスが終了するのを待つ
	for (int i = 0; i < cmd_count; i++)
  {
		int wstatus;
		waitpid(pids[i], &wstatus, 0);
		if (i == cmd_count - 1)
			status = WEXITSTATUS(wstatus);
	}
	return status;
}
