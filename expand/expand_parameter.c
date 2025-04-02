// expand_parameter.c

#include "minishell.h"

static void	append_status(char **dst, char **str, t_data *data)
{
	char	*stat;
	char	*cur;

	stat = ft_itoa(data->exit_status);
	if (stat == NULL)
		fatal_error("ft_itoa");
	cur = stat;
	while (*cur != '\0')
		append_char(dst, *cur++);
	free(stat);
	*str += 2;
}

void	expand_parameter_token(t_data *data, t_token *token)
{
	char	*new_word;
	char	*str;

	if (token == NULL)
		return ;
	if (token->kind == TK_WORD && token->word != NULL)
	{
		str = token->word;
		new_word = ft_calloc(1, sizeof(char));
		if (new_word == NULL)
			fatal_error("ft_calloc");
		while (*str != '\0')
		{
			if (str[0] == '$' && str[1] == '?')
				append_status(&new_word, &str, data);
			else
				append_char(&new_word, *str++);
		}
		free(token->word);
		token->word = new_word;
	}
	expand_parameter_token(data, token->next);
}

void	expand_parameter(t_data *data, t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind != ND_REDIR_HEREDOC)
		expand_parameter_token(data, node->args);
	expand_parameter(data, node->redirects);
	expand_parameter(data, node->next);
}
