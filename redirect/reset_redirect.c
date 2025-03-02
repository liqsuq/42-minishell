// reset_redirect.c

#include "minishell.h"

void perform_all_redirects(t_node *redirects)
{
  t_node *cur;

  cur = redirects;
  while (cur)
  {
    perform_redirect(cur, NULL);
    cur = cur->next;
  }
}

void perform_all_redirects_recursive(t_node *node)
{
  if (!node)
    return;

  // まずこのノードの redirects リストを処理 (← 既存の関数を使う)
  perform_all_redirects(node->redirects);

  // パイプラインの場合、left と right を再帰
  if (node->kind == ND_PIPELINE)
  {
    perform_all_redirects_recursive(node->left);
    perform_all_redirects_recursive(node->right);
  }

  // 他にも ND_SIMPLE_CMD が続くなど別の構造があるなら処理
  // あるいは、フラットに node->next があるならそこも再帰
  if (node->next)
    perform_all_redirects_recursive(node->next);
}

void reset_all_redirects_recursive(t_node *node)
{
    if (!node)
        return;

    // まずこのノードの `redirects` をリセット
    reset_all_redirects(node->redirects);

    // パイプラインノードなら、left と right を再帰
    if (node->kind == ND_PIPELINE)
    {
        reset_all_redirects_recursive(node->left);
        reset_all_redirects_recursive(node->right);
    }

    // node->next が使われているなら、そこも再帰
    if (node->next)
        reset_all_redirects_recursive(node->next);
}

void reset_all_redirects(t_node *redirects)
{
  int count;
  int i;
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
   i = 0;
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