#include "../includes/minirt.h"

void	sp_calc(t_itrsec *itrsec, double t, t_sp *sp, t_ray *ray)
{
	t_vec	p_i;
	t_vec	normal;

	p_i = vec_add(ray->start, vec_scalar(ray->dir, t));
	normal = normalize(vec_sub(p_i, sp->center));
	itrsec->has_itrsec = 1;
	itrsec->dist = t;
	itrsec->normal = normal;
	itrsec->pos = p_i;
}

t_itrsec	sp_itrsec(t_ray ray, t_sp *sp)
{
	t_itrsec	itrsec;
	t_vec		sp_cam;
	double		n[4];
	double		t;

	sp_cam = vec_sub(ray.start, sp->center);
	n[0] = norm(ray.dir) * norm(ray.dir);
	n[1] = 2 * vec_dot(sp_cam, ray.dir);
	n[2] = vec_dot(sp_cam, sp_cam) - sp->rad * sp->rad;
	n[3] = n[1] * n[1] - 4 * n[0] * n[2];
	if (n[3] < 0)
	{
		itrsec.has_itrsec = 0;
		return (itrsec);
	}
	t = (-n[1] - sqrt(n[3])) / (2 * n[0]);
	sp_calc(&itrsec, t, sp, &ray);
	return (itrsec);
}

t_object	*init_sp(t_vec center, double rad, t_mtrl mtrl)
{
	t_object	*sp;

	sp = malloc(sizeof(t_object));
	if (sp == NULL)
		return (NULL);
	sp->type = SP;
	sp->data.sp.center = center;
	sp->data.sp.rad = rad;
	sp->mtrl = mtrl;
	return (sp);
}

int	ch_sp(t_info *info, char **array)
{
	t_object	*object;
	t_vec		pos;
	double		diameter;
	t_rgb		rgb;

	if (ft_poipoi_strlen((void **)array) != 3
		|| ft_str2vec(&pos, array[0]) == ERROR
		|| rgb2bin(&rgb, array[2]) == ERROR)
		return (ret_err("invalid sp params"));
	diameter = ft_atof(array[1]);
	object = init_sp(pos, diameter / 2, init_mtrl(rgb, \
		rgb_init(0.9, 0.9, 0.9), 42));
	if (!object || !(ft_lstadd_back_new(&info->objects, object)))
		return (ret_err("failed newlist malloc"));
	return (0);
}
