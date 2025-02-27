// reset_redirect.c

#include "minishell.h"

void perform_all_redirects(t_node *redirects)
{
  t_node *cur = redirects;
  while (cur)
  {
    perform_redirect(cur, NULL);
    cur = cur->next;
  }
}

void reset_all_redirects(t_node *redirects)
{
  int count;
  t_node *tmp;

  count = 0;
  tmp = redirects;
  while (tmp)
  {
    count++;
    tmp = tmp->next;
  }

   t_node **array = malloc(sizeof(t_node*) * count);
   if (!array)
       fatal_error("malloc");
   tmp = redirects;
   int i = 0;
   while (tmp)
   {
      array[i++] = tmp;
      tmp = tmp->next;
   }

  i = count - 1;
  while (i >= 0)
  {
    reset_redirect(array[i]);
    i--;
  }
  free(array);
}