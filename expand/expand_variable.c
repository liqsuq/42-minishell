// expand_variable.c

#include "minishell.h"

static int	is_variable(const char *s)
{
	return (s[0] == '$' && (ft_isalpha(s[1]) || s[1] == '_'));
}

static void	append_variable(char **dst, char **str, t_env *env)
{
	char	*name;
	char	*value;
	char	*cur;

	name = NULL;
	cur = *str + 1;
	append_char(&name, *cur++);
	while (ft_isalpha(*cur) || ft_isdigit(*cur) || *cur == '_')
		append_char(&name, *cur++);
	value = get_env(env, name);
	free(name);
	if (value)
		while (*value)
			append_char(dst, *value++);
	*str = cur;
}

static void	append_quote_var(char **dst, char **str, t_env *env)
{
	char	c;
	char	*cur;

	c = **str;
	cur = *str;
	append_char(dst, *cur++);
	while (*cur != c)
	{
		if (c == '\"' && is_variable(cur))
			append_variable(dst, &cur, env);
		else
			append_char(dst, *cur++);
	}
	append_char(dst, *cur++);
	*str = cur;
}

void	expand_variable_token(t_token *token, int force, t_env *env)
{
	char	*new_word;
	char	*str;

	if (token == NULL)
		return ;
	if (token->kind == TK_WORD && token->word != NULL)
	{
		str = token->word;
		new_word = ft_calloc(1, sizeof(char));
		if (new_word == NULL)
			fatal_error("ft_calloc", strerror(errno));
		while (*str != '\0')
		{
			if (!force && (*str == '\'' || *str == '\"'))
				append_quote_var(&new_word, &str, env);
			else if (is_variable(str))
				append_variable(&new_word, &str, env);
			else
				append_char(&new_word, *str++);
		}
		free(token->word);
		token->word = new_word;
	}
	expand_variable_token(token->next, force, env);
}

void	expand_variable(t_data *data, t_node *node)
{
	if (node == NULL || data->is_abort)
		return ;
	if (node->kind != ND_REDIR_HEREDOC)
		expand_variable_token(node->args, 0, data->env);
	expand_variable(data, node->redirects);
	expand_variable(data, node->next);
}
