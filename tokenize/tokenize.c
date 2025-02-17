// tokenizer.c

#include "minishell.h"

void	assert_error(const char *msg)
{
	ft_dprintf(STDERR_FILENO, "Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

int	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	consume_blank(char **rest, char *line)
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

int	is_operator(const char *s)
{
	char *const	ops[] = {"||", "&", "&&", ";", ";;", "(", ")", "|"};
	size_t		i;

	i = 0;
	while (i < sizeof(ops) / sizeof(*ops))
	{
		if (ft_strncmp(s, ops[i], ft_strlen(ops[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_metacharacter(char c)
{
	return (c != '\0' && ft_strchr("|&;()<> \t\n", c));
}

int	is_word(const char *s)
{
	return (*s && !is_metacharacter(*s));
}

t_token	*operator(char **rest, char *line)
{
	char *const	ops[] = {"||", "&", "&&", ";", ";;", "(", ")", "|"};
	size_t		i = 0;
	char		*op;

	while (i < sizeof(ops) / sizeof(*ops))
	{
		if (ft_strncmp(line, ops[i], ft_strlen(ops[i])) == 0)
		{
			op = ft_strdup(ops[i]);
			if (op == NULL)
				fatal_error("strdup");
			*rest = line + ft_strlen(op);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	assert_error("unexpected operator");
	return (NULL);
}

t_token	*word(char **rest, char *line)
{
	const char	*start = line;
	char		*word;

	while (*line && !is_metacharacter(*line))
		line++;
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
		if (consume_blank(&line, line))
			continue ;
		else if (is_operator(line))
			add_token(&head, operator(&line, line));
		else if (is_word(line))
			add_token(&head, word(&line, line));
		else
			assert_error("tokernize error");
	}
	return (head);
}
