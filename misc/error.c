// error.c

#include "minishell.h"

void	fatal_error(const char *msg)
{
	char	*str;

	if (msg != NULL)
		str = ft_strjoin(HEADER, msg);
	else
		str = ft_strdup(HEADER);
	if (str != NULL)
		perror(str);
	else
		perror(HEADER);
	free(str);
	exit(EXIT_FAILURE);
}

void	tokenize_error(t_data *data, const char *msg, char **line)
{
	char	*cur;

	cur = *line;
	data->is_abort = 1;
	data->exit_status = ERROR_SYNTAX;
	if (msg != NULL)
		ft_dprintf(STDERR, HEADER "syntax error: %s\n", msg);
	while (*cur != '\0')
		cur++;
	*line = cur;
}

void	parse_error(t_data *data, const char *msg, t_token **token)
{
	t_token	*cur;

	cur = *token;
	data->is_abort = 1;
	data->exit_status = ERROR_SYNTAX;
	if (msg != NULL)
		ft_dprintf(STDERR, HEADER "syntax error: %s\n", msg);
	while (cur != NULL)
		cur = cur->next;
	*token = cur;
}

void	expand_error(t_data *data, const char *msg)
{
	data->is_abort = 1;
	if (msg != NULL)
		ft_dprintf(STDERR, HEADER "%s\n", msg);
}

void	builtin_error(t_data *data, const char *msg, const char *errstr)
{
	char	buf[1024];

	ft_strlcpy(buf, HEADER, sizeof(buf));
	if (msg != NULL)
		ft_strlcat(buf, msg, sizeof(buf));
	if (errstr != NULL)
	{
		ft_strlcat(buf, ": ", sizeof(buf));
		ft_strlcat(buf, errstr, sizeof(buf));
	}
	ft_dprintf(STDERR, "%s\n", buf);
	data->exit_status = EXIT_FAILURE;
}
