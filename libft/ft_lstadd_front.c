/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:10:33 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/09 19:36:20 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>
// int main(void)
// {
// 	t_list *lst1 = ft_lstnew("42");
// 	t_list *new1 = ft_lstnew("tokyo");
// 	t_list *lst2 = NULL;
// 	t_list *new2 = ft_lstnew("hogehoge");
// 	ft_lstadd_front(&lst1, new1);
// 	for (t_list *lst = lst1; lst != NULL; lst = lst->next)
// 		printf("%s\n", (char *)lst->content);
// 	printf("\n");
// 	ft_lstadd_front(&lst2, new2);
// 	for (t_list *lst = lst2; lst != NULL; lst = lst->next)
// 		printf("%s\n", (char *)lst->content);
// 	ft_lstclear(&lst1, NULL);
// 	ft_lstclear(&lst2, NULL);
// 	return (0);
// }
