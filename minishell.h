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

# define NAME "minishell"
# define HEADER "minishell: "
# define PROMPT "minish$ "
# define SQUOTE '\''
# define DQUOTE '\"'
# define ERROR_SYNTAX 258

typedef enum e_token_kind
{
	TK_WORD,
	TK_OP,
}	t_token_kind;

typedef struct s_token
{
	t_token_kind	kind;
	char			*word;
	struct s_token	*next;
}					t_token;

typedef enum e_node_kind
{
	ND_SIMPLE_CMD,		// 単純なコマンド
	ND_REDIR_OUT,		// 標準出力リダイレクト
	ND_REDIR_IN,		// 標準入力リダイレクト
	ND_REDIR_APPEND,	// 出力の追加リダイレクト
	ND_REDIR_HEREDOC,	// ヒアドキュメント
	ND_PIPELINE,		// パイプライン
}	t_node_kind;

// コマンドやリダイレクトを表すノード構造体
typedef struct s_node
{
	t_node_kind		kind;				// ノードの種類
	t_token			*args;				// 引数リスト
	struct s_node	*redirects;			// リダイレクト
	t_token			*filename;			// ファイル名
	t_token			*delimiter;			// ヒアドキュメントの区切り文字
	int				stashed_std_fd;		// 保持している標準ファイルディスクリプタ
	bool			is_delimiter_quote;	// 区切り文字がクオートされているかどうか
	struct s_node	*next;				// 次のノード
}					t_node;

typedef struct s_redir
{
	int				fd;
	t_token			*filename;
	int				stashed_fd;
	t_token			*delimiter;
	int				is_quoted;
	struct s_redir	*next;
}					t_redir;

// 環境変数のキーと値を格納するリスト構造体
typedef struct s_env
{
	char			*key;	// 環境変数のキー
	char			*value;	// 環境変数の値
	struct s_env	*next;	// 次の環境変数
}					t_env;

typedef struct s_data
{
	int	exit_status;
}		t_data;

extern int	syntax_error;

// tokenize/tokenize.c
int		is_metacharacter(char c);
t_token	*tokenize(char *line);

// tokenize/tokenuils.c
int		tokensize(t_token *token);
t_token	*new_token(char *word, t_token_kind kind);
void	add_token(t_token **head, t_token *new);
void	free_token(t_token *token);

// parse/parse.c
t_node	*parse(t_token *tok);

// parse/nodeutils.c
t_node	*new_node(t_node_kind kind);
void	add_node(t_node **head, t_node *new);
void	append_token(t_token **tokens, t_token *tok);
t_token	*tokdup(t_token *tok);
void	free_node(t_node *node);

// expand/expand.c
void	expand(t_node *node);
void	append_char(char **s, char c);

// expand/expand_variable.c
void	expand_variable(t_node *node);

// execute/execute.c
int		execute(t_node *node);
void	execute_command(t_node *node);

// execute/argvutils.c
char	**new_argv(t_token *tokens);
void	free_argv(char **argv);

// execute/pathutils.c
char	*resolve_path(char *line);

// redirect/redirect.c
void	redirect(t_node *node, t_env **env);
void	reset_redirect(t_node *node);

// pipeline/pipeline.c
int		pipeline(t_node *node, int prev_pipeout);

// misc/error.c
void	fatal_error(const char *msg);
void	assert_error(const char *msg);
void	tokenize_error(const char *msg, char **rest, char *line);
void	parse_error(const char *msg, t_token **rest, t_token *token);

// misc/debug.c
void	print_token(t_token *token);

// misc/ft_strcmp.c
int		ft_strcmp(const char *s1, const char *s2);

// misc/ft_realloc.c
void	*ft_realloc(void *ptr, size_t size);

#endif
