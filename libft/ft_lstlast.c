/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:22:43 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/16 17:35:36 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// #include <stdio.h>
// int main(void)
// {
// 	t_list *list = ft_lstnew("Hello");
// 	t_list *new = ft_lstnew("42tokyo");
// 	ft_lstadd_back(&list, new);
// 	printf("%s\n", (char *)ft_lstlast(list)->content);
// 	ft_lstclear(&list, NULL);
// 	return (0);
// }
