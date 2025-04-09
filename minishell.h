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

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define NAME "minishell"
# define HEADER "minishell: "
# define PROMPT "minish$ "
# define PROMPT_HEREDOC "> "
# define SQUOTE '\''
# define DQUOTE '\"'
# define ERROR_GENERAL 1
# define ERROR_SYNTAX 2
# define ERROR_NOPERM 126
# define ERROR_NOFILE 127
# define ERROR_INVALID 128

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
}	t_node_kind;

// コマンドやリダイレクトを表すノード構造体
// args: arguments of the command or redirection
//       NOTE: if node is a heredoc, args->next contains heredoc contents
typedef struct s_node
{
	t_node_kind		kind;				// ノードの種類
	t_token			*args;				// 引数リスト・リダイレクトの引数
	struct s_node	*redirects;			// リダイレクトリスト
	int				stashed_fd;			// 保持している標準ファイルディスクリプタ
	struct s_node	*next;				// 次のノード
}					t_node;

// 環境変数のキーと値を格納するリスト構造体
typedef struct s_env
{
	char			*key;	// 環境変数のキー
	char			*value;	// 環境変数の値
	struct s_env	*next;	// 次の環境変数
}					t_env;

typedef struct s_data
{
	int				exit_status;
	int				is_abort;
}					t_data;

extern volatile sig_atomic_t	g_signal;

// tokenize/tokenize.c
int		is_blank(char c);
int		is_metacharacter(char c);
t_token	*tokenize(t_data *data, char *line);

// tokenize/tokenuils.c
int		tokenlen(t_token *token);
t_token	*new_token(char *word, t_token_kind kind);
t_token	*add_token(t_token **head, t_token *new);
t_token	*dup_token(t_token *token);
void	free_token(t_token *token);

// parse/parse.c
t_node	*parse(t_data *data, t_token *token);

// parse/nodeutils.c
t_node	*new_node(t_node_kind kind);
t_node	*add_node(t_node **head, t_node *new);
void	free_node(t_node *node);

// expand/expand.c
void	expand(t_data *data, t_node *node);
void	append_char(char **s, char c);

// expand/expand_variable.c
void	expand_variable(t_data *data, t_node *node);
void	expand_variable_token(t_token *token, int force);

// expand/expand_parameter.c
void	expand_parameter(t_data *data, t_node *node);
void	expand_parameter_token(t_data *data, t_token *token, int force);

// expand/expand_word.c
void	expand_word(t_data *data, t_node *node);

// expand/expand_quote.c
void	expand_quote(t_data *data, t_node *node);
void	expand_quote_token(t_token *token);

// expand/expand_heredoc.c
void	expand_heredoc(t_data *data, t_node *node);

// execute/execute.c
void	execute(t_data *data, t_node *node);
void	execute_command(t_node *node);

// execute/argvutils.c
char	**new_argv(t_token *args);
void	free_argv(char **argv);

// execute/pathutils.c
char	*resolve_path(char *line);

// redirect/redirect.c
void	redirect(t_node *redi, t_env **env);
void	reset_redirect(t_node *redi);

// pipeline/pipeline.c
int		pipeline(t_node *node, int prev_pipeout);

// misc/error.c
void	fatal_error(const char *msg);
void	assert_error(const char *msg);
void	tokenize_error(const char *msg, t_data *data, char **line);
void	parse_error(const char *msg, t_data *data, t_token **token);
void	expand_error(const char *msg, t_data *data);

// misc/debug.c
void	print_argv(char **str);
void	print_token(t_token *token);
void	print_env(t_env *env);
void	print_redir(t_node *redir);
void	print_node(t_node *node);

// misc/ft_funcs.c
int		ft_strcmp(const char *s1, const char *s2);
// void	*ft_realloc(void *ptr, size_t size);

// misc/signal.c
int		check_signal_main(void);
int		check_signal_heredoc(void);
void	setup_signal(void);
void	reset_signal(void);

#endif
