/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:44:48 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/06 00:17:04 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_variable(const char *s)
{
	return (s[0] == '$' && (ft_isalpha(s[1]) || s[1] == '_'));
}

static void	append_variable(t_data *data, char **dst, char **str)
{
	char	*name;
	char	*value;
	char	*cur;

	name = NULL;
	cur = *str + 1;
	append_char(&name, *cur++);
	while (ft_isalpha(*cur) || ft_isdigit(*cur) || *cur == '_')
		append_char(&name, *cur++);
	value = get_env(data->env, name);
	free(name);
	if (value)
		while (*value)
			append_char(dst, *value++);
	*str = cur;
}

static void	append_quote_var(t_data *data, char **dst, char **str)
{
	char	c;
	char	*cur;

	c = **str;
	cur = *str;
	append_char(dst, *cur++);
	while (*cur != c)
	{
		if (c == '\"' && is_variable(cur))
			append_variable(data, dst, &cur);
		else
			append_char(dst, *cur++);
	}
	append_char(dst, *cur++);
	*str = cur;
}

void	expand_variable_token(t_data *data, t_token *token, int force)
{
	char	*new_word;
	char	*str;

	if (token == NULL)
		return ;
	if (token->kind == TK_WORD && token->word != NULL)
	{
		str = token->word;
		new_word = xcalloc(1, sizeof(char));
		while (*str != '\0')
		{
			if (!force && (*str == '\'' || *str == '\"'))
				append_quote_var(data, &new_word, &str);
			else if (is_variable(str))
				append_variable(data, &new_word, &str);
			else
				append_char(&new_word, *str++);
		}
		free(token->word);
		token->word = new_word;
	}
	expand_variable_token(data, token->next, force);
}

void	expand_variable(t_data *data, t_node *node)
{
	if (node == NULL || data->abort)
		return ;
	if (node->kind != ND_REDIR_HEREDOC)
		expand_variable_token(data, node->args, 0);
	if (node->kind != ND_SIMPLE_CMD && node->kind != ND_REDIR_HEREDOC)
		if (node->args == NULL || ft_strlen(node->args->word) == 0)
			expand_error(data, "ambiguous redirect", &node);
	if (node == NULL || data->abort)
		return ;
	expand_variable(data, node->redirects);
	expand_variable(data, node->next);
}
