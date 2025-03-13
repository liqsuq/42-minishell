// ft_realloc.c

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	if (ptr == NULL)
		return (malloc(size));
	new = malloc(size);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, ptr, size);
	free(ptr);
	return (new);
}
