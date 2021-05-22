#include "../../includes/minirt.h"

t_dlist	*ft_add_data4dlst(t_dlist **list, t_dlist *new)
{
	if (!list || !new)
		return (NULL);
	if (!*list)
	{
		*list = new;
		(*list)->next = *list;
		(*list)->prev = *list;
	}
	else
	{
		new->next = *list;
		new->prev = (*list)->prev;
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	*list = new;
	return (*list);
}
