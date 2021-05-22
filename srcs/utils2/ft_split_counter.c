#include "../../includes/minirt.h"

int	ft_split_counter(char *str, char c)
{
	int		split_size;

	split_size = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (!*str)
			break ;
		while (*str && *str != c)
			str++;
		split_size++;
	}
	return (split_size);
}
