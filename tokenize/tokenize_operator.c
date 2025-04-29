// tokenize_operetor.c

#include "minishell.h"

int	is_operator(const char *s)
{
	char *const	ops[] = {">>", "<<", ">", "<", "|"};
	size_t		i;

	i = -1;
	while (++i < sizeof(ops) / sizeof(*ops))
		if (ft_strncmp(s, ops[i], ft_strlen(ops[i])) == 0)
			return (1);
	return (0);
}

t_token	*tokenize_operator(t_data *data, char **line)
{
	char *const	ops[] = {">>", "<<", ">", "<", "|"};
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
	return (tokenize_error(data, "unexpected operator", line), NULL);
}
