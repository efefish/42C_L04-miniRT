#include "../../includes/minirt.h"

int	ft_str2vec(t_vec *vec, char *str)
{
	char	**vec_poipoi;

	vec_poipoi = ft_split(str, ',');
	if (vec_poipoi == NULL || ft_strchr_counter(str, ',') != 2
		|| ft_poipoi_strlen((void **)vec_poipoi) != 3)
	{
		printf("input str: %s\n", str);
		free_array((void **)vec_poipoi);
		return (ret_err("failed str2vec"));
	}
	vec->x = ft_atof(vec_poipoi[0]);
	vec->y = ft_atof(vec_poipoi[1]);
	vec->z = ft_atof(vec_poipoi[2]);
	free_array((void **)vec_poipoi);
	return (0);
}
