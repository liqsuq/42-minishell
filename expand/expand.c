// expand.c

#include "minishell.h"

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += strlen(*s);
	new = malloc(size);
	if (new == NULL)
		fatal_error("malloc");
	if (*s)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

void	remove_quotes(t_token *tokens)
{
	char	*new_word;
	char	*str;

	if (tokens == NULL)
		return ;
	if (tokens->kind == TK_WORD && tokens->word != NULL)
	{
		str = tokens->word;
		new_word = NULL;
		while (*str != '\0' && !is_metacharacter(*str))
		{
			if (*str == SQUOTE)
			{
				str++;
				while (*str != SQUOTE)
				{
					if (*str == '\0')
						assert_error("unmatched single quote");
					append_char(&new_word, *str++);
				}
				str++;
			}
			else if (*str == DQUOTE)
			{
				str++;
				while (*str != DQUOTE)
				{
					if (*str == '\0')
						assert_error("unmatched double quote");
					append_char(&new_word, *str++);
				}
				str++;
			}
			else
				append_char(&new_word, *str++);
		}
		free(tokens->word);
		tokens->word = new_word;
	}
	remove_quotes(tokens->next);
}

void	expand_quotes_removal(t_node *node)
{
	if (node == NULL)
		return ;
	remove_quotes(node->args);
	expand_quotes_removal(node->next);
}

void	expand(t_node *node)
{
	expand_quotes_removal(node);
}
