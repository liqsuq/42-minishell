/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:34:39 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/11 10:48:07 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL && f != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// #include <stdio.h>
// static void putstr_fd(void *content)
// {
// 	ft_putstr_fd(content, 1);
// }
// int main(void)
// {
// 	t_list *list = ft_lstnew("42");
// 	t_list *new = ft_lstnew("tokyo");
// 	ft_lstadd_back(&list, new);
// 	ft_lstiter(list, &putstr_fd);
// 	printf("\n");
// 	ft_lstclear(&list, NULL);
// 	return (0);
// }
