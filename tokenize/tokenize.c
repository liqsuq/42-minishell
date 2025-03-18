// tokenize.c

#include "minishell.h"

static int	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	skip_blank(char **rest, char *line)
{
	if (is_blank(*line))
	{
		while (*line && is_blank(*line))
			line++;
		*rest = line;
		return (1);
	}
	*rest = line;
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

static t_token	*operator(char **rest, char *line)
{
	char *const	ops[] = {">>", "<<", "||", "&&", ";;", ">", "<", "|", "&", ";", "(", ")"};
	size_t		i;
	char		*op;

	i = -1;
	while (++i < sizeof(ops) / sizeof(*ops))
	{
		if (ft_strncmp(line, ops[i], ft_strlen(ops[i])) == 0)
		{
			op = ft_strdup(ops[i]);
			if (op == NULL)
				fatal_error("strdup");
			*rest = line + ft_strlen(op);
			return (new_token(op, TK_OP));
		}
	}
	assert_error("unexpected operator");
	return (NULL);
}

static t_token	*word(char **rest, char *line)
{
	const char	*start = line;
	char		*word;
	char		c;

	while (*line != '\0' && !is_metacharacter(*line))
	{
		if (*line == SQUOTE || *line == DQUOTE)
		{
			c = *line;
			while (*++line != c)
				if (*line == '\0')
					break;
			if (*line == '\0')
				tokenize_error("unmatched single quote", &line, line);
		}
		line++;
	}
	word = strndup(start, line - start);
	if (word == NULL)
		fatal_error("strndup");
	*rest = line;
	return (new_token(word, TK_WORD));
}

t_token	*tokenize(char *line)
{
	t_token	*head;

	head = NULL;
	while (*line != '\0')
	{
		if (skip_blank(&line, line))
			continue ;
		else if (is_operator(line))
			add_token(&head, operator(&line, line));
		else if (is_word(line))
			add_token(&head, word(&line, line));
		else
			tokenize_error("tokernize error", &line, line);
	}
	return (head);
}
