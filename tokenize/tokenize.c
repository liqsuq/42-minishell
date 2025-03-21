// tokenize.c

#include "minishell.h"

static int	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
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

static int	is_operator(const char *s)
{
	char *const	ops[] = {">>", "<<", "||", "&&", ";;", ">", "<", "|", "&", ";", "(", ")"};
	size_t		i;

	i = -1;
	while (++i < sizeof(ops) / sizeof(*ops))
		if (ft_strncmp(s, ops[i], ft_strlen(ops[i])) == 0)
			return (1);
	return (0);
}

int	is_metacharacter(char c)
{
	return (c != '\0' && ft_strchr("|&;()<> \t\n", c));
}

static int	is_word(const char *s)
{
	return (*s != '\0' && !is_metacharacter(*s));
}

static t_token	*tokenize_operator(t_data *data, char **line)
{
	char *const	ops[] = {">>", "<<", "||", "&&", ";;", ">", "<", "|", "&", ";", "(", ")"};
	char		*cur;
	size_t		i;
	char		*op;	

	cur = *line;
	i = -1;
	while (++i < sizeof(ops) / sizeof(*ops))
	{
		if (ft_strncmp(cur, ops[i], ft_strlen(ops[i])) == 0)
		{
			op = ft_strdup(ops[i]);
			if (op == NULL)
				fatal_error("strdup");
			*line = cur + ft_strlen(op);
			return (new_token(op, TK_OP));
		}
	}
	return (tokenize_error("unexpected operator", data, line), NULL);
}

static t_token	*tokenize_word(t_data *data, char **line)
{
	char	*cur;
	char	*word;
	char	c;

	cur = *line;
	while (*cur != '\0' && !is_metacharacter(*cur))
	{
		if (*cur == SQUOTE || *cur == DQUOTE)
		{
			c = *cur;
			while (*++cur != c)
				if (*cur == '\0')
					break ;
			if (*cur == '\0')
				return (tokenize_error("unmatched quote", data, line), NULL);
		}
		cur++;
	}
	word = ft_substr(*line, 0, cur - *line);
	if (word == NULL)
		fatal_error("ft_substr");
	*line = cur;
	return (new_token(word, TK_WORD));
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
			tokenize_error("unknown tokenize error", data, &line);
	}
	return (head);
}
