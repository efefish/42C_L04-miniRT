#include "../../includes/minirt.h"

size_t	ft_poipoi_strlen(void **poipoistr)
{
	size_t	i;

	i = 0;
	while (poipoistr[i])
		i++;
	return (i);
}
