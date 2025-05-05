/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:51:30 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/05 13:07:55 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define NAME "minishell"
# define HEADER "minishell: "
# define PROMPT "minish$ "
# define PROMPT_HEREDOC "> "
# define BUFFER_SIZE 1024
# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO
# define ERROR_SYNTAX 2
# define ERROR_NOPERM 126
# define ERROR_NOFILE 127
# define ERROR_INVALID 128
# define WARN_NONDELIM "warning: here-document delimited by end-of-file\n"

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
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
}	t_node_kind;

typedef struct s_node
{
	t_node_kind		kind;
	t_token			*args;
	struct s_node	*redirects;
	int				stashed_fd;
	struct s_node	*next;
}					t_node;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_path
{
	char			*name;
	struct s_path	*next;
}					t_path;

typedef struct s_data
{
	int				exit_status;
	int				is_abort;
	t_env			*env;
}					t_data;

extern volatile sig_atomic_t	g_signal;

// main.c

// tokenize/tokenize.c
int		is_blank(char c);
int		is_metacharacter(char c);
t_token	*tokenize(t_data *data, char *line);
// tokenize/tokenize_operator.c
int		is_operator(const char *s);
t_token	*tokenize_operator(t_data *data, char **line);
// tokenize/tokenize_word.c
int		is_word(const char *s);
t_token	*tokenize_word(t_data *data, char **line);
// tokenize/tokenuils.c
t_token	*new_token(char *word, t_token_kind kind);
t_token	*add_token(t_token **head, t_token *new);
void	free_token(t_token **token);
t_token	*dup_token(t_token *token);
void	pop_token(t_token **head, t_token *token, t_token *prev);

// parse/parse.c
t_node	*parse(t_data *data, t_token *token);
// parse/nodeutils.c
t_node	*new_node(t_node_kind kind);
t_node	*add_node(t_node **head, t_node *new);
void	free_node(t_node **node);

// expand/expand.c
void	expand(t_data *data, t_node *node);
void	append_char(char **s, char c);
// expand/expand_variable.c
void	expand_variable(t_data *data, t_node *node);
void	expand_variable_token(t_token *token, int force, t_env *env);
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
void	execute_command(t_data *data, t_node *node);
int		is_builtin(t_token *args);
void	execute_builtin(t_data *data, t_node *node);
// execute/argvutils.c
char	**new_argv(t_token *args);
void	free_argv(char ***argv);
// execute/find_path.c
char	*find_path(t_env *env, char path[PATH_MAX], char *line);

// redirect/redirect.c
int		setup_redirect(t_node *redi);
void	reset_redirect(t_node *redi);

// pipeline/pipeline.c
int		pipeline(t_data *data, t_node *node, int prev_pipeout);

// builtin
void	builtin_echo(t_data *data, char **argv);
void	builtin_cd(t_data *data, char **argv);
void	builtin_pwd(t_data *data, char **argv);
void	builtin_export(t_data *data, char **argv);
void	builtin_unset(t_data *data, char **argv);
void	builtin_env(t_data *data, char **argv);
void	builtin_exit(t_data *data, char **argv);
// builtin/pathutils.c
t_path	*new_path(char *name, size_t len);
t_path	*push_path(t_path **head, t_path *new);
void	pop_path(t_path **head, t_path *prev);
char	*dump_path(t_path *head);
void	free_path(t_path **path);

// misc/signal.c
int		check_signal_main(void);
int		check_signal_heredoc(void);
void	setup_signal(void);
void	reset_signal(void);
// misc/environ.c
char	**dump_environ(t_env *env);
void	free_environ(char ***envp);
// misc/envutils.c
t_env	*new_env(char *key, char *value);
void	free_env(t_env **env);
char	*get_env(t_env *env, char *key);
int		set_env(t_env **env, char *key, char *value);
t_env	*init_env(char **envp);
// misc/error.c
void	fatal_error(const char *msg, const char *errstr);
void	tokenize_error(t_data *data, const char *msg, char **line);
void	parse_error(t_data *data, const char *msg, t_token **token);
void	expand_error(t_data *data, const char *msg, t_node **node);
void	bltin_error(t_data *data, const char *msg, const char *errstr);
// misc/ft_funcs.c
int		ft_strcmp(const char *s1, const char *s2);
char	*get_next_line_nonl(int fd);
// misc/xfuncs_fd.c
void	xwrite(int fd, const void *buf, size_t count);
void	xclose(int fd);
void	xpipe(int *fd);
int		xdup(int oldfd);
void	xdup2(int oldfd, int newfd);
// misc/xfuncs_sys.c
void	*xcalloc(size_t count, size_t size);
pid_t	xfork(void);
void	xsigaction(int sig, const struct sigaction *new, struct sigaction *old);

#endif
