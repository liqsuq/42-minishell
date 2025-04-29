// tokenize.c

#include "minishell.h"

int	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_metacharacter(char c)
{
	return (c != '\0' && ft_strchr("><| \t\n", c));
}

static int	skip_blank(char **line)
{
	char	*cur;

	cur = *line;
	if (is_blank(*cur))
	{
		while (*cur && is_blank(*cur))
			cur++;
		*line = cur;
		return (1);
	}
	*line = cur;
	return (0);
}

t_token	*tokenize(t_data *data, char *line)
{
	t_token	*head;

	head = NULL;
	while (*line != '\0')
	{
		if (skip_blank(&line))
			continue ;
		else if (is_operator(line))
			add_token(&head, tokenize_operator(data, &line));
		else if (is_word(line))
			add_token(&head, tokenize_word(data, &line));
		else
			tokenize_error(data, "unknown tokenize error", &line);
	}
	return (head);
}
