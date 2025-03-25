// expand.c

#include "minishell.h"

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s != NULL)
		size += strlen(*s);
	new = ft_realloc(*s, size);
	if (new == NULL)
	{
		free(*s);
		fatal_error("ft_realloc");
	}
	new[size - 2] = c;
	new[size - 1] = '\0';
	*s = new;
}

static void	remove_quote(t_token *token)
{
	char	*new_word;
	char	*cur;
	char	c;

	new_word = NULL;
	cur = token->word;
	while (*cur != '\0' && !is_metacharacter(*cur))
	{
		if (*cur == SQUOTE || *cur == DQUOTE)
		{
			c = *cur;
			while (*++cur != c)
				append_char(&new_word, *cur);
			cur++;
		}
		else
			append_char(&new_word, *cur++);
	}
	free(token->word);
	token->word = new_word;
}

static void	expand_quote(t_node *node)
{
	t_token	*tok;

	if (node == NULL)
		return ;
	tok = node->args;
	while (tok != NULL)
	{
		if (tok->kind == TK_WORD && tok->word != NULL)
			remove_quote(tok);
		tok = tok->next;
	}
	expand_quote(node->next);
}

void	expand(t_data *data, t_node *node)
{
	expand_variable(node);
	expand_parameter(data, node);
	expand_quote(node);
}
