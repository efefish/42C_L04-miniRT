#include "../../includes/minirt.h"

t_list	*ft_lstadd_back_new(t_list **lst, void *content)
{
	t_list	*new_list;

	new_list = ft_lstnew(content);
	if (!new_list)
		return (NULL);
	ft_lstadd_back(lst, new_list);
	return (*lst);
}
