// debug.c

#include "minishell.h"

// print_argv 関数
// この関数は、引数のリストである `str` を受け取り、その内容を一行ずつ表示します。
// str 配列の要素を順番に printf で出力します。配列の終端は NULL で表現されています。
// この関数はデバッグ用であり、コメントアウトされているため、実行されません。
void	print_argv(char **str)
{
	int	i;

	i = 0;
	// str 配列の各要素を順に表示
	while (str[i])
	{
		ft_printf("str[%d]: %s\n", i, str[i]);
		i++;
	}
}

void	print_token(t_token *token)
{
	if (token == NULL)
		return ;
	ft_printf("kind: %d, word: %s\n", token->kind, token->word);
	print_token(token->next);
}

// print_env 関数
// 与えられた環境変数リストを表示します。
// `env` 構造体の `key` と `value` を順番に表示します。
// デバッグ用で、環境変数の内容を確認するために使われますが、コメントアウトされています。
void	print_env(t_env *env)
{
	// 環境変数のリストの先頭から順に key と value を表示
	ft_printf("start print_env\n");
	ft_printf("=======================================================\n");
	while (env)
	{
		ft_printf("env->key: %s, env->value: %s\n", env->key, env->value);
		env = env->next;
	}
}

void	print_redir(t_node *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind == ND_REDIR_HEREDOC)
		ft_printf("kind: %d, delim: %s\n", redir->kind, redir->delimiter->word);
	else
		ft_printf("kind: %d, fname: %s\n", redir->kind, redir->filename->word);	
	print_redir(redir->next);
}

// print_node 関数
// ノード構造体のコマンドとリダイレクトを表示します。
// コマンド引数とリダイレクトを持つノードが与えられた場合、それらの情報をデバッグ出力します。
// デバッグ用に使用される関数で、コメントアウトされています。
void	print_node(t_node *node)
{
	if (node == NULL)
		return ;
	// コマンドの引数が存在する場合、引数を表示
	if (node->args)
	{
		printf("node->args:\n");
		print_token(node->args);
	}
	// コマンドのリダイレクトが存在する場合、リダイレクト情報を表示
	if (node->redirects)
	{
		printf("node->redirects:\n");
		print_redir(node->redirects);
	}
	// 再帰的に呼び出して表示
	print_node(node->next);
}
