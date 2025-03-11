// expand_variable.c

#include "minishell.h"

int	is_namehead(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_namebody(char c)
{
	return (is_namehead(c) || ft_isdigit(c));
}

int	is_name(const char *s)
{
	if (!is_namehead(*s++))
		return (0);
	while (*s)
		if (!is_namebody(*s++))
			return (0);
	return (1);
}

int	is_variable(const char *s)
{
	return (s[0] == '$' && is_namehead(s[1]));
}

void	expand_variable_str(char **dst, char **rest, char *str)
{
	char	*name;
	char	*value;

	name = NULL;
	str++;
	append_char(&name, *str++);
	while (is_namebody(*str))
		append_char(&name, *str++);
	value = getenv(name);
	free(name);
	if (value)
		while (*value)
			append_char(dst, *value++);
	*rest = str;
}

void	append_quote(char **dst, char **rest, char *str)
{
	char	c;

	if (*str == SQUOTE || *str == DQUOTE)
	{
		c = *str;
		append_char(dst, *str++);
		while (*str != c)
		{
			if (*str == '\0')
				assert_error("unclosed quote");
			else if (c == DQUOTE && is_variable(str))
				expand_variable_str(dst, &str, str);
			else
				append_char(dst, *str++);
		}
		append_char(dst, *str++);
		*rest = str;
	}
	else
		assert_error("expected quote");
}

void	expand_variable_token(t_token *token)
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
			fatal_error("malloc");
		while (*str && !is_metacharacter(*str))
		{
			if (*str == SQUOTE || *str == DQUOTE)
				append_quote(&new_word, &str, str);
			else if (is_variable(str))
				expand_variable_str(&new_word, &str, str);
			else
				append_char(&new_word, *str++);
		}
		free(token->word);
		token->word = new_word;
	}
	expand_variable_token(token->next);
}

void	expand_variable(t_node *node)
{
	if (node == NULL)
		return ;
	expand_variable_token(node->args);
	expand_variable_token(node->filename);
	expand_variable(node->redirects);
	expand_variable(node->command);
	expand_variable(node->next);
}
