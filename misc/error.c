/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nateshim <nateshim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:45:45 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/02 21:06:32 by nateshim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fatal_error(const char *msg, const char *errstr)
{
	char	buf[BUFFER_SIZE];

	ft_strlcpy(buf, HEADER, sizeof(buf));
	if (msg != NULL)
		ft_strlcat(buf, msg, sizeof(buf));
	if (errstr != NULL)
	{
		ft_strlcat(buf, ": ", sizeof(buf));
		ft_strlcat(buf, errstr, sizeof(buf));
	}
	ft_dprintf(STDERR, "%s\n", buf);
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
	const char	*tok;
	t_token		*cur;

	cur = *token;
	data->is_abort = 1;
	data->exit_status = ERROR_SYNTAX;
	if (msg != NULL && *msg != '\0')
		tok = msg;
	else if (token != NULL && *token != NULL && (*token)->word != NULL)
		tok = (*token)->word;
	else
		tok = "newline";
	ft_dprintf(STDERR, HEADER "syntax error near unexpected token `%s'\n", tok);
	if (token != NULL)
	{
		while (cur != NULL)
		{
			while (cur != NULL)
				cur = cur->next;
			*token = cur;
		}
		free(*token);
		*token = NULL;
	}
}

void	bltin_error(t_data *data, const char *msg, const char *errstr)
{
	char	buf[BUFFER_SIZE];

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
