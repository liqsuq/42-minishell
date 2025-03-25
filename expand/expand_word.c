// expand_word.c

#include "minishell.h"

static t_token	*split_word(t_token *token, char *end, char *next)
{
	char	*str;
	t_token	*new;

	if (token == NULL || end == NULL || next == NULL)
		return (NULL);
	if (*next != '\0')
	{
		str = ft_strdup(next);
		if (str == NULL)
			return (NULL);
		new = new_token(str, TK_WORD);
		if (new == NULL)
		{
			free(str);
			return (NULL);
		}
		new->next = token->next;
		token->next = new;
	}
	str = ft_substr(token->word, 0, end - token->word);
	if (str == NULL)
		return (NULL);
	free(token->word);
	token->word = str;
	return (token);
}

static t_token	*split_word_tail(t_token *token)
{
	char	*end;
	char	*cur;
	char	c;

	cur = token->word;
	while (*cur != '\0')
	{
		if (is_blank(*cur))
		{
			end = cur;
			while (is_blank(*cur))
				cur++;
			return (split_word(token, end, cur));
		}
		if (*cur == SQUOTE || *cur == DQUOTE)
		{
			c = *cur++;
			while (*cur != c)
				cur++;
		}
		cur++;
	}
	return (token);
}

static t_token	*split_word_head(t_token *token)
{
	char	*cur;
	char	*new;

	cur = token->word;
	while (is_blank(*cur))
		cur++;
	if (cur != token->word)
	{
		new = ft_strdup(cur);
		if (new == NULL)
			return (NULL);
		free(token->word);
		token->word = new;
	}
	return (token);
}

static void	expand_word_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->kind == TK_WORD && token->word != NULL)
	{
		if (split_word_head(token) == NULL)
			fatal_error("split_word_head");
		if (split_word_tail(token) == NULL)
			fatal_error("split_word_tail");
	}
	expand_word_token(token->next);
}

void	expand_word(t_node *node)
{
	if (node == NULL)
		return ;
	expand_word_token(node->args);
	expand_word(node->next);
}
