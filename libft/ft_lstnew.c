/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:02:22 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/09 20:04:14 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (ptr == NULL)
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}

// #include <stdio.h>
// int main(void)
// {
// 	t_list *list = ft_lstnew(ft_strdup("Hello World!"));
// 	printf("%s\n", (char *)list->content);
// 	ft_lstclear(&list, &free);
// 	return (0);
// }
