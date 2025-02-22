// minisehll.h

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdnoreturn.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdbool.h>
# include "libft/libft.h"

# define PROMPT "minish$ "
# define SQUOTE '\''
# define DQUOTE '\"'

typedef enum e_kind
{
	TK_WORD,
	TK_OP,
}	t_kind;

typedef struct s_token
{
	char			*word;
	t_kind			kind;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	int	exit_status;
}		t_data;

typedef enum e_node_kind
{
	ND_SIMPLE_CMD,    // 単純なコマンド
	ND_REDIR_OUT,     // 標準出力リダイレクト
	ND_REDIR_IN,      // 標準入力リダイレクト
	ND_REDIR_APPEND,  // 出力の追加リダイレクト
	ND_REDIR_HEREDOC, // ヒアドキュメント
	ND_PIPELINE       // パイプライン
}						t_node_kind;

// コマンドやリダイレクトを表すノード構造体
typedef struct s_node
{
	t_node_kind kind;         // ノードの種類
	struct s_node *next;      // 次のノード
	t_token *args;            // 引数リスト
	struct s_node *redirects; // リダイレクト
	int std_fd;               // 標準ファイルディスクリプタ
	t_token *filename;        // ファイル名
	t_token *delimiter;       // ヒアドキュメントの区切り文字
	int filefd;               // ファイルディスクリプタ
	int stashed_std_fd;       // 保持している標準ファイルディスクリプタ
	bool is_delimiter_quote;  // 区切り文字がクオートされているかどうか
	struct s_node *command;   // コマンドノード
	int inpipe[2];            // パイプの入力
	int outpipe[2];           // パイプの出力
}							t_node;	
// 環境変数のキーと値を格納するリスト構造体
typedef struct s_env
{
	char *key;          // 環境変数のキー
	char *value;        // 環境変数の値
	struct s_env *next; // 次の環境変数
}							 t_env;

// interpret.c
int		interpret(char *line);
char	**tokens2argv(t_token *tokens);
void	free_argv(char **argv);

// search_path.c
char	*search_path(const char *filename);

// tokenizer.c
int		is_metacharacter(char c);
t_token	*tokenize(char *line);

// tokenuil.c
t_token	*new_token(char *word, t_kind kind);
void	add_token(t_token **head, t_token *new);
void	free_tokens(t_token *token);
void	print_tokens(t_token *tokens);

// expand.c
void	expand(t_token *tokens);

// error.c
void	fatal_error(const char *msg);
void	assert_error(const char *msg);

// redirection.c
void reset_redirection(t_node *node);
void perform_redirection(t_node *node, t_env **env);

#endif
