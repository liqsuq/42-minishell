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

static void	remove_quote(t_token *tokens)
{
	char	*new_word;
	char	*cur;
	char	c;

	if (tokens == NULL)
		return ;
	if (tokens->kind == TK_WORD && tokens->word != NULL)
	{
		cur = tokens->word;
		new_word = NULL;
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
		free(tokens->word);
		tokens->word = new_word;
	}
	remove_quote(tokens->next);
}

static void	expand_quote(t_node *node)
{
	if (node == NULL)
		return ;
	remove_quote(node->args);
	expand_quote(node->next);
}

void	expand(t_node *node)
{
	expand_variable(node);
	expand_quote(node);
}
