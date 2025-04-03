// expand_variable.c

#include "minishell.h"

static int	is_namehead(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static int	is_namebody(char c)
{
	return (is_namehead(c) || ft_isdigit(c));
}

static int	is_variable(const char *s)
{
	return (s[0] == '$' && is_namehead(s[1]));
}

static void	append_variable(char **dst, char **str)
{
	char	*name;
	char	*value;
	char	*cur;

	name = NULL;
	cur = *str + 1;
	append_char(&name, *cur++);
	while (is_namebody(*cur))
		append_char(&name, *cur++);
	value = getenv(name);
	free(name);
	if (value)
		while (*value)
			append_char(dst, *value++);
	*str = cur;
}

static void	append_quote_var(char **dst, char **str)
{
	char	c;
	char	*cur;

	c = **str;
	cur = *str;
	append_char(dst, *cur++);
	while (*cur != c)
	{
		if (c == DQUOTE && is_variable(cur))
			append_variable(dst, &cur);
		else
			append_char(dst, *cur++);
	}
	append_char(dst, *cur++);
	*str = cur;
}

void	expand_variable_token(t_token *token, int force)
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
			fatal_error("ft_calloc");
		while (*str != '\0')
		{
			if (!force &&(*str == SQUOTE || *str == DQUOTE))
				append_quote_var(&new_word, &str);
			else if (is_variable(str))
				append_variable(&new_word, &str);
			else
				append_char(&new_word, *str++);
		}
		free(token->word);
		token->word = new_word;
	}
	expand_variable_token(token->next, force);
}

void	expand_variable(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind != ND_REDIR_HEREDOC)
		expand_variable_token(node->args, 0);
	expand_variable(node->redirects);
	expand_variable(node->next);
}
