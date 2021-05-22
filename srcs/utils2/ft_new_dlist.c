#include "../../includes/minirt.h"

t_dlist	*ft_new_dlist(t_dlist **list, void *data)
{
	t_dlist	*new;

	new = (t_dlist *)malloc(sizeof(t_dlist));
	if (new == NULL)
		return (NULL);
	new->data = data;
	new->next = NULL;
	new->prev = NULL;
	return (ft_add_data4dlst(list, new));
}
