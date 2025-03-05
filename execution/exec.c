// exec.c

#include "minishell.h"

int exec_nodes(t_node *node)
{
  int status = 0;

  if (!node)
    return 0;

  if (has_pipe(node))
  {
    return exec_pipeline(node);
  }
  else
  {
    expand(node);
    perform_all_redirects(node->redirects);
    char **argv = tokens2argv(node->args);
    if (!argv[0])
    {
      reset_all_redirects(node->redirects);
      free_argv(argv);
      return 0;
    }
    char *path = resolve_path(argv[0]);
    if (!path)
    {
      status = 127;
    }
    else
    {
      status = exec_command(path, argv);
      free(path);
    }
    free_argv(argv);
    reset_all_redirects(node->redirects);
    return status;
  }
}
