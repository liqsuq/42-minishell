//debug_print.c

#include "minishell.h"

// print_argv 関数
// この関数は、引数のリストである `str` を受け取り、その内容を一行ずつ表示します。
// str 配列の要素を順番に printf で出力します。配列の終端は NULL で表現されています。
// この関数はデバッグ用であり、コメントアウトされているため、実行されません。
void	print_argv(char **str)
{
	int	i = 0;

	// str 配列の各要素を順に表示
	while (str[i])
	{
		printf("str[%d]:%s\n", i, str[i]);
		i++;
	}
}

// print_token 関数
// 与えられたトークンリストを順番に表示します。トークンの word プロパティを表示します。
// `TK_EOF`（トークンの終端）までループし、各トークンの `word` を出力します。
// この関数もデバッグ用であり、コメントアウトされています。
void	print_token(t_token *token)
{
	// トークンリストをループして各トークンの `word` を表示
	while (token != NULL)
	{
		printf("token_word: %s\n", token->word);
		token = token->next;
	}
}

// print_env 関数
// 与えられた環境変数リストを表示します。
// `env` 構造体の `key` と `value` を順番に表示します。
// デバッグ用で、環境変数の内容を確認するために使われますが、コメントアウトされています。
void	print_env(t_env *env)
{
	// 環境変数のリストの先頭から順に key と value を表示
	printf("start print_env\n");
	printf("=======================================================\n");
	while (env)
	{
		printf("env->key:%s, env->value:%s\n", env->key, env->value);
		env = env->next;
	}
}

void print_node(t_node *node)
{
  if (!node)
    return;

  // ノード種別表示 (パイプなのか単純コマンドか)
  printf("Node kind: %d\n", node->kind);

  // このノードの引数 (node->args) を表示
  // node->command ではなく node->args から印字する
  if (node->args)
  {
    printf("Arguments:\n");
    print_token(node->args);
  }

  // リダイレクトがあるなら表示
  if (node->redirects)
  {
    printf("Redirects:\n");
    // それぞれの redirect ノードの filename を表示する等
    // 省略可
  }

  // ツリー形式なら、パイプラインの left/right を再帰表示
  if (node->kind == ND_PIPELINE)
  {
    printf("Left side:\n");
    print_node(node->left);
    printf("Right side:\n");
    print_node(node->right);
  }

  // node->next を使う実装なら、それを辿る
  // (今はツリー形式なら next は使わないはず)
  if (node->next)
  {
    printf("Next node:\n");
    print_node(node->next);
  }
}
