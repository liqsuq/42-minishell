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
# include "libft/libft.h"

# define NAME "minishell"
# define HEADER NAME ": "
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
	char			*word;
	t_token_kind	kind;
	struct s_token	*next;
}					t_token;

typedef enum e_node_kind
{
	ND_SIMPLE_CMD,    // 単純なコマンド
}	t_node_kind;


// コマンドやリダイレクトを表すノード構造体
typedef struct s_node
{
	t_node_kind		kind;     // ノードの種類
	struct s_node	*next;    // 次のノード
	t_token			*args;    // 引数リスト
}					t_node;	

typedef struct s_data
{
	int	exit_status;
}		t_data;

extern int syntax_error;

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
t_token	*new_token(char *word, t_token_kind kind);
void	add_token(t_token **head, t_token *new);
void	free_tokens(t_token *token);
void	print_tokens(t_token *tokens);

// expand.c
void	expand(t_node *node);

// error.c
void	fatal_error(const char *msg);
void	assert_error(const char *msg);
void	tokenize_error(const char *msg, char **rest, char *line);
void	parse_error(const char *msg, t_token **rest, t_token *token);

// parse.c
t_node	*parse(t_token *tok);

// nodeutils.c
t_node	*new_node(t_node_kind kind);
void	add_node(t_node **head, t_node *new);
void	append_token(t_token **tokens, t_token *tok);
t_token	*tokdup(t_token *tok);
void	free_nodes(t_node *node);
void	print_nodes(t_node *nodes);

#endif
