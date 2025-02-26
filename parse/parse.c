// parse.c

#include "minishell.h"

static int ft_strcmp(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

static void parse_redirection(t_node *cmdnode, t_token **rest, t_token *token)
{
  t_node *redir_node = NULL;

  if (ft_strcmp(token->word, ">") == 0)
      redir_node = new_node(ND_REDIR_OUT);
  else if (ft_strcmp(token->word, "<") == 0)
      redir_node = new_node(ND_REDIR_IN);
  else
      parse_error("unexpected redirection operator", rest, token);

  token = token->next;
  if (!token || token->kind != TK_WORD)
      parse_error("expected filename after redirection", rest, token);

  redir_node->filename = tokdup(token);
  add_node(&cmdnode->redirects, redir_node);

  token = token->next;
  *rest = token;
}


t_node *parse(t_token *token)
{
  t_node *node = new_node(ND_SIMPLE_CMD);

  while (token)
  {
    if (token->kind == TK_WORD)
    {
        append_token(&node->args, tokdup(token));
        token = token->next;
    }
    else if (token->kind == TK_OP && (!ft_strcmp(token->word, ">") || !ft_strcmp(token->word, "<")))
    {
      parse_redirection(node, &token, token);
    }
    else
    {
      parse_error("unexpected token", &token, token);
    }
  }
  return node;
}