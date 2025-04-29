// tokenize_word.c

#include "minishell.h"

int	is_word(const char *s)
{
	return (*s != '\0' && !is_metacharacter(*s));
}

t_token	*tokenize_word(t_data *data, char **line)
{
	char	*cur;
	char	*word;
	char	c;

	cur = *line;
	while (is_word(cur))
	{
		if (*cur == '\'' || *cur == '\"')
		{
			c = *cur;
			while (*++cur != c)
				if (*cur == '\0')
					break ;
			if (*cur == '\0')
				return (tokenize_error(data, "unmatched quote", line), NULL);
		}
		cur++;
	}
	word = ft_substr(*line, 0, cur - *line);
	if (word == NULL)
		fatal_error("ft_substr", strerror(errno));
	*line = cur;
	return (new_token(word, TK_WORD));
}
