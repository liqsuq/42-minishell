/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:29:53 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/09 19:41:03 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	if (del != NULL)
		del(lst->content);
	free(lst);
}

// #include <stdio.h>
// #include <stdlib.h>
// int main(void)
// {
// 	t_list *list = ft_lstnew(ft_strdup("42tokyo"));
// 	for (t_list *lst = list; lst != NULL; lst = lst->next)
// 		printf("%s\n", (char *)lst->content);
// 	printf("\n");
// 	ft_lstdelone(list, &free);
// 	printf("%p\n", list);
// 	return (0);
// }
