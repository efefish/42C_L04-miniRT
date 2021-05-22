#include "../includes/minirt.h"

t_itrsec	pl_itrsec(t_ray ray, t_pl *pl)
{
	double		d_n_dot;
	t_vec		c_cam;
	double		t;
	t_itrsec	itrsec;

	c_cam = vec_sub(ray.start, pl->pos);
	d_n_dot = vec_dot(vec_scalar(ray.dir, -1), pl->normal);
	if (d_n_dot == 0)
	{
		itrsec.has_itrsec = 0;
		return (itrsec);
	}
	t = vec_dot(c_cam, pl->normal) / d_n_dot;
	itrsec.has_itrsec = 1;
	itrsec.dist = t;
	if (d_n_dot > 0)
		itrsec.normal = pl->normal;
	else
		itrsec.normal = vec_scalar(pl->normal, -1);
	itrsec.pos = vec_add(ray.start, vec_scalar(ray.dir, t));
	return (itrsec);
}

t_object	*init_pl(t_vec pos, t_vec normal, t_mtrl mtrl)
{
	t_object	*pl;

	pl = malloc(sizeof(t_object));
	if (pl == NULL)
		return (NULL);
	pl->type = PL;
	pl->data.pl.pos = pos;
	pl->data.pl.normal = normal;
	pl->mtrl = mtrl;
	return (pl);
}

int	ch_pl(t_info *info, char **array)
{
	t_object	*object;
	t_vec		pos;
	t_vec		normal;
	t_rgb		rgb;

	if (ft_poipoi_strlen((void **)array) != 3
		|| ft_str2vec(&pos, array[0]) == ERROR
		|| ft_str2vec(&normal, array[1]) == ERROR
		|| rgb2bin(&rgb, array[2]) == ERROR)
		return (ret_err("invalid pl params"));
	if (ch_normal_range(&normal) == ERROR)
		return (ret_err("invalid normal params"));
	object = init_pl(pos, normalize(normal), \
		init_mtrl(rgb, rgb_init(0.3, 0.3, 0.3), 42));
	if (!object || !(ft_lstadd_back_new(&info->objects, object)))
		return (ret_err("failed malloc"));
	return (0);
}
