// parse.c

#include "minishell.h"

static int	is_redirect(t_token *token)
{
	char *const	ops[] = {">>", "<<", ">", "<"};
	size_t		i;

	i = -1;
	if (token->next == NULL || token->next->kind != TK_WORD)
		return (0);
	while (++i < sizeof(ops) / sizeof(*ops))
		if (!ft_strcmp(token->word, ops[i]))
			return (1);
	return (0);
}

static void	read_heredoc_into_node(t_node *heredoc_node, const char *delim, bool is_quoted, t_env *env)
{
	char *line;
	char *buf;
	(void)is_quoted;
	(void)env;

	heredoc_node->heredoc_content = ft_calloc(1, sizeof(char));
	if (!heredoc_node->heredoc_content)
		fatal_error("malloc heredoc_content");
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (!ft_strcmp(line, delim))
		{
			free(line);
			break;
		}
		buf = ft_strjoin(heredoc_node->heredoc_content, line);
		free(heredoc_node->heredoc_content);
		heredoc_node->heredoc_content = buf;
		buf = ft_strjoin(heredoc_node->heredoc_content, "\n");
		free(heredoc_node->heredoc_content);
		heredoc_node->heredoc_content = buf;
		free(line);
	}
}

t_token *parse_redirect_heredoc(t_data *data, t_node *node, t_token *token)
{
	t_token *delim_token = token->next;
	bool is_quoted = false;

	(void)data;
	if (ft_strchr(delim_token->word, SQUOTE) == NULL && ft_strchr(delim_token->word, DQUOTE) == NULL)
		is_quoted = false;
	else
		is_quoted = true;

	read_heredoc_into_node(node, delim_token->word, !is_quoted, NULL);
	return (delim_token->next);
}

static t_token	*parse_redirect(t_data *data, t_node *node, t_token *token)
{
	t_node	*nd;	
	t_token	*tk;

	tk = token;
	if (!ft_strcmp(tk->word, ">"))
		nd = add_node(&node->redirects, new_node(ND_REDIR_OUT));
	else if (!ft_strcmp(tk->word, ">>"))
		nd = add_node(&node->redirects, new_node(ND_REDIR_APPEND));
	else if (!ft_strcmp(tk->word, "<"))
		nd = add_node(&node->redirects, new_node(ND_REDIR_IN));
	else
		nd = add_node(&node->redirects, new_node(ND_REDIR_HEREDOC));
	tk = tk->next; // 次のトークンがデリミタ or ファイル名
	nd->args = dup_token(tk);
	if (nd->kind == ND_REDIR_HEREDOC)
	tk = parse_redirect_heredoc(data, nd, token);
	else
		tk = tk->next;
	return (tk);
}

static t_token	*parse_simple_cmd(t_data *data, t_node **node, t_token *token)
{
	t_node	*nd;
	t_token	*tk;

	tk = token;
	nd = add_node(node, new_node(ND_SIMPLE_CMD));
	while (tk != NULL)
	{
		if (tk->kind == TK_WORD)
		{
			add_token(&nd->args, dup_token(tk));
			tk = tk->next;
		}
		else if (is_redirect(tk))
			tk = parse_redirect(data, nd, tk);
		else
			break ;
	}
	return (tk);
}

static t_token	*parse_pipeline(t_data *data, t_node **node, t_token *token)
{
	t_token	*tk;

	tk = token;
	if (tk && (tk->kind == TK_WORD || is_redirect(tk)))
	{
		tk = parse_simple_cmd(data, node, tk);
		if (tk && tk->kind == TK_OP && !ft_strcmp(tk->word, "|"))
		{
			if (tk->next)
				tk = parse_pipeline(data, node, tk->next);
			else
				parse_error("unexpected end of file", data, &tk);
		}
	}
	else
		parse_error("unexpected token", data, &tk);
	return (tk);
}

t_node	*parse(t_data *data, t_token *token)
{
	t_node	*node;

	node = NULL;
	if (token == NULL)
		return (NULL);
	parse_pipeline(data, &node, token);
	return (node);
}
