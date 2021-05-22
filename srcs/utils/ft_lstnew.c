#include "../../includes/minirt.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*data;

	data = malloc(sizeof(t_list));
	if (data == NULL)
		return (NULL);
	data->content = content;
	data->next = NULL;
	return (data);
}
