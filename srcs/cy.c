#include "../includes/minirt.h"

void	cy_calc(t_itrsec *itrsec, t_cy *cy, t_ray *ray, double *t)
{
	t_vec	c2p[2];
	double	h[2];

	c2p[0] = vec_sub(vec_add(ray->start, vec_scalar(ray->dir, t[0])), cy->pos);
	c2p[1] = vec_sub(vec_add(ray->start, vec_scalar(ray->dir, t[1])), cy->pos);
	h[0] = vec_dot(c2p[0], cy->normal);
	h[1] = vec_dot(c2p[1], cy->normal);
	if (h[0] >= 0 && h[0] <= cy->height)
	{
		itrsec->has_itrsec = 1;
		itrsec->normal = normalize(vec_sub(c2p[0], \
		vec_scalar(cy->normal, h[0])));
		itrsec->dist = t[0];
		itrsec->pos = vec_add(ray->start, vec_scalar(ray->dir, t[0]));
	}
	else if (h[1] >= 0 && h[1] <= cy->height)
	{
		itrsec->has_itrsec = 1;
		itrsec->normal = normalize(vec_sub(vec_scalar(cy->normal, \
		h[1]), c2p[1]));
		itrsec->dist = t[1];
		itrsec->pos = vec_add(ray->start, vec_scalar(ray->dir, t[1]));
	}
	else
		itrsec->has_itrsec = 0;
}

t_itrsec	cy_itrsec(t_ray ray, t_cy *cy)
{
	t_itrsec	itrsec;
	double		n[4];
	double		t[2];

	n[0] = norm(vec_cross(ray.dir, cy->normal)) \
	* norm(vec_cross(ray.dir, cy->normal));
	n[1] = 2 * vec_dot(vec_cross(ray.dir, cy->normal), \
	vec_cross(vec_sub(ray.start, cy->pos), cy->normal));
	n[2] = norm(vec_cross(vec_sub(ray.start, cy->pos), cy->normal));
	n[2] = n[2] * n[2] - cy->radius * cy->radius;
	n[3] = n[1] * n[1] - 4 * n[0] * n[2];
	if (n[3] < 0)
	{
		itrsec.has_itrsec = 0;
		return (itrsec);
	}
	t[0] = (-n[1] - sqrt(n[3])) / (2 * n[0]);
	t[1] = (-n[1] + sqrt(n[3])) / (2 * n[0]);
	cy_calc(&itrsec, cy, &ray, t);
	return (itrsec);
}

t_object	*init_cy(t_vec pos, t_vec normal, double *f, t_mtrl mtrl)
{
	t_object	*cy;

	cy = malloc(sizeof(t_object));
	if (cy == NULL)
		return (NULL);
	cy->type = CY;
	cy->data.cy.pos = pos;
	cy->data.cy.normal = normal;
	cy->data.cy.radius = f[0];
	cy->data.cy.height = f[1];
	cy->mtrl = mtrl;
	return (cy);
}

int	ch_cy(t_info *info, char **array)
{
	t_object	*object;
	t_vec		point;
	t_vec		normal;
	double		f[2];
	t_rgb		rgb;

	if (ft_poipoi_strlen((void **)array) != 5
		|| ft_str2vec(&point, array[0]) == ERROR
		|| ft_str2vec(&normal, array[1]) == ERROR
		|| rgb2bin(&rgb, array[4]) == ERROR)
		return (ret_err("invalid cy params"));
	f[0] = ft_atof(array[2]) / 2;
	f[1] = ft_atof(array[3]);
	if (ch_normal_range(&normal) == ERROR)
		return (ret_err("invalid normal params"));
	object = init_cy(point, normalize(normal), f, \
		init_mtrl(rgb, rgb_init(0.3, 0.3, 0.3), 42));
	if (!object || !(ft_lstadd_back_new(&info->objects, object)))
		return (ret_err("failed malloc"));
	return (0);
}
