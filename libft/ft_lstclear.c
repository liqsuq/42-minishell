/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:27:34 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/09 19:39:17 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
	*lst = NULL;
}

// #include <stdio.h>
// #include <stdlib.h>
// int main(void)
// {
// 	t_list *list = ft_lstnew(ft_strdup("42"));
// 	t_list *new = ft_lstnew(ft_strdup("tokyo"));
// 	ft_lstadd_back(&list, new);
// 	for (t_list *lst = list; lst != NULL; lst = lst->next)
// 		printf("%s\n", (char *)lst->content);
// 	printf("\n");
// 	ft_lstclear(&list, &free);
// 	printf("%p\n", list);
// 	return (0);
// }
