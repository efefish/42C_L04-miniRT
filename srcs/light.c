#include "../includes/minirt.h"

t_light	*init_light(t_vec pos, t_rgb illumination)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (light == NULL)
		return (NULL);
	light->pos = pos;
	light->illum = illumination;
	return (light);
}

int	ch_light(t_info *info, char **array)
{
	t_light		*light;
	t_vec		pos;
	t_rgb		rgb;
	double		illumination;

	if (ft_poipoi_strlen((void **)array) != 3
		|| ft_str2vec(&pos, array[0]) == ERROR
		|| rgb2bin(&rgb, array[2]) == ERROR)
		return (ret_err("invalid light params"));
	illumination = ft_atof(array[1]);
	rgb = rgb_scalar(rgb, illumination);
	light = init_light(pos, rgb);
	if (!light || !(ft_lstadd_back_new(&info->lights, light)))
		return (ret_err("failed malloc"));
	return (0);
}
