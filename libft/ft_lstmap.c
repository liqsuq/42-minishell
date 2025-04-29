/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:37:50 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/16 17:40:04 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*tmp;
	void	*content;

	if (lst == NULL)
		return (NULL);
	ret = NULL;
	while (lst != NULL)
	{
		if (f != NULL)
			content = f(lst->content);
		else
			content = lst->content;
		tmp = ft_lstnew(content);
		if (tmp == NULL)
		{
			if (f != NULL || del != NULL)
				del(content);
			ft_lstclear(&ret, del);
			return (NULL);
		}
		ft_lstadd_back(&ret, tmp);
		lst = lst->next;
	}
	return (ret);
}

// #include <stdio.h>
// #include <stdlib.h>
// static void *capitalize(void *content)
// {
// 	char *str = content;
// 	for (int i = 0; str[i] != '\0'; i++)
// 		str[i] = ft_toupper(str[i]);
// 	return (content);
// }
// static void putendl_fd(void *content)
// {
// 	ft_putendl_fd(content, 1);
// }
// int main(void)
// {
// 	t_list *list = ft_lstnew(strdup("Hello "));
// 	t_list *new = ft_lstnew(strdup("World!"));
// 	ft_lstadd_back(&list, new);
// 	t_list *ret = ft_lstmap(list, &capitalize, &free);
// 	ft_lstiter(list, &putendl_fd);
// 	ft_lstiter(ret, &putendl_fd);
// 	ft_lstclear(&list, &free);
// 	ft_lstclear(&ret, NULL);
// 	return (0);
// }
