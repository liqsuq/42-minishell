// parse.c

#include "minishell.h"

static void parse_redirection(t_node *cmdnode, t_token **rest, t_token *token)
{
  t_node *redir_node = NULL;

  if (!ft_strcmp(token->word, ">"))
    redir_node = new_node(ND_REDIR_OUT);
  else if (!ft_strcmp(token->word, ">>"))
    redir_node = new_node(ND_REDIR_APPEND);
  else if (!ft_strcmp(token->word, "<"))
    redir_node = new_node(ND_REDIR_IN);
  else if (!ft_strcmp(token->word, "<<"))
    redir_node = new_node(ND_REDIR_HEREDOC);
  else
    parse_error("unexpected redirection operator", rest, token);

  token = token->next;
  if (!token || token->kind != TK_WORD)
    parse_error("expected filename (or 'EOF') after redirection", rest, token);

  if (redir_node->kind == ND_REDIR_HEREDOC)
  {
    if (ft_strcmp(token->word, "EOF") != 0)
      parse_error("this minishell only supports '<<EOF' heredoc", rest, token);
  }
  else
  {
    redir_node->filename = tokdup(token);
  }

  add_node(&cmdnode->redirects, redir_node);

  token = token->next;
  *rest = token;
}

int ft_strcmp(const char *s1, const char *s2)
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

static t_node *parse_simple_command(t_token **rest, t_token *token)
{
  t_node *cmdnode = new_node(ND_SIMPLE_CMD);

  while (token)
  {
    if (token->kind == TK_WORD)
    {
      append_token(&cmdnode->args, tokdup(token));
      token = token->next;
    }
    else if (token->kind == TK_OP &&
             (!ft_strcmp(token->word, ">")  || !ft_strcmp(token->word, ">>") ||
              !ft_strcmp(token->word, "<")  || !ft_strcmp(token->word, "<<")))
    {
      parse_redirection(cmdnode, &token, token);
    }
    else if (token->kind == TK_OP && !ft_strcmp(token->word, "|"))
      break;
    else
    {
      parse_error("unexpected token", &token, token);
      break;
    }
  }
  *rest = token;
  return cmdnode;
}

static t_node *parse_pipeline(t_token **rest, t_token *token)
{
  t_node *left_cmd = parse_simple_command(&token, token);
  if (!left_cmd)
  {
    *rest = token;
    return NULL;
  }

  if (token && token->kind == TK_OP && !ft_strcmp(token->word, "|"))
  {
    token = token->next;
    t_node *pipe_node = new_node(ND_PIPELINE);
    pipe_node->left = left_cmd;
    pipe_node->right = parse_pipeline(&token, token);
    *rest = token;
    return pipe_node;
  }

  *rest = token;
  return left_cmd;
}

t_node *parse(t_token *token)
{
  t_node *root = parse_pipeline(&token, token);
  return root;
}
