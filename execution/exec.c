// exec.c

#include "minishell.h"

static int exec_simple_cmd(t_node *node, t_env **env)
{
  (void)env;

  int wstatus;
  char **argv = tokens2argv(node->args);
  pid_t pid = fork();

  if (pid < 0)
  {
    perror("fork");
    return 1;
  }
  if (pid == 0)
  {
    // 子プロセス: 実行
    execvp(argv[0], argv);
    perror("execvp");
    exit(127);
  }
  else
  {
    // 親が待機
    waitpid(pid, &wstatus, 0);
    int status = WEXITSTATUS(wstatus);
    return status;
  }
}

static int exec_pipeline_tree(t_node *node)
{
  if (!node)
    return 0;

  // パイプ作成
  int pipefd[2];
  if (pipe(pipefd) < 0)
  {
    perror("pipe");
    return 1;
  }

  pid_t pid = fork();
  if (pid < 0)
  {
    perror("fork");
    return 1;
  }

  if (pid == 0)
  {
    // 子プロセス: left のコマンドを実行
    // stdout -> pipefd[1]
    close(pipefd[0]);
    if (dup2(pipefd[1], STDOUT_FILENO) < 0)
    {
        perror("dup2");
        exit(1);
    }
    close(pipefd[1]);

    // leftを再帰実行する => exec()呼び出し
    exit(exec(node->left, NULL));
  }
  else
  {
    // 親プロセス: right を実行
    // まず子プロセスの終了を待たずに標準入力をパイプに繋ぐパターン
    close(pipefd[1]);
    if (dup2(pipefd[0], STDIN_FILENO) < 0)
    {
        perror("dup2");
        return 1;
    }
    close(pipefd[0]);

    int status;
    waitpid(pid, &status, 0);
    // 子プロセスが終了したら、rightを再帰実行
    return exec(node->right, NULL);
  }
}


int exec(t_node *node, t_env **env)
{
  // ノードがNULLなら何もしない
  if (!node)
    return 0;

  if (node->kind == ND_PIPELINE)
  {
    // ツリー形式のパイプライン
    return exec_pipeline_tree(node);
  }
  else if (node->kind == ND_SIMPLE_CMD)
  {
    // 単純コマンド
    return exec_simple_cmd(node, env);
  }
  else
  {
    // たとえばリダイレクトのみのノードなどの可能性があれば対応
    // 今回は最小限例
    return 0;
  }
}
