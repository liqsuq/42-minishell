/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:13:48 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/09 20:05:59 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

// #include <stdio.h>
// int main(void)
// {
// 	t_list *list = ft_lstnew("42tokyo");
// 	t_list *new1 = ft_lstnew("hogehoge");
// 	t_list *new2 = ft_lstnew("fugafuga");
// 	ft_lstadd_front(&list, new1);
// 	ft_lstadd_front(&list, new2);
// 	printf("%d\n", ft_lstsize(list));
// 	ft_lstclear(&list, NULL);
// 	return (0);
// }
