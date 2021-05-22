#include "../../includes/minirt.h"

size_t	ft_strchr_counter(char *str, char c)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	return (count);
}
