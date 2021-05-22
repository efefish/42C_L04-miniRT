#include "../includes/minirt.h"

int	no_params(char **array)
{
	if (!array[0])
		return (0);
	return (-1);
}

int	has_shadow(t_info *info, t_light light, t_itrsec itrsec)
{
	t_vec		l;
	t_ray		shadow_ray;
	double		light_dist;
	t_list		*current;
	t_itrsec	inter;

	l = normalize(vec_sub(light.pos, itrsec.pos));
	shadow_ray.start = vec_add(itrsec.pos, vec_scalar(l, EPSILON));
	shadow_ray.dir = l;
	light_dist = norm(vec_sub(light.pos, itrsec.pos)) - EPSILON;
	current = info->objects;
	while (current)
	{
		inter = calc_itrsec(shadow_ray, *(t_object *)current->content);
		if (inter.has_itrsec && inter.dist >= 0 && inter.dist <= light_dist)
			return (1);
		current = current->next;
	}
	return (0);
}

t_rgb	calc_ref_diff(t_object object, t_itrsec itrsec, t_light light)
{
	t_vec	l;
	double	ray_deg;
	t_rgb	ref_diff;

	l = normalize(vec_sub(light.pos, itrsec.pos));
	ray_deg = vec_dot(itrsec.normal, l);
	if (ray_deg < 0)
		ray_deg = 0;
	ref_diff = rgb_scalar(rgb_mult(object.mtrl.dif, light.illum), ray_deg);
	return (ref_diff);
}

t_rgb	calc_ref_spec(t_ray ray, t_object object, t_itrsec itrsec, \
		t_light light)
{
	t_vec	l;
	t_vec	v;
	t_vec	r;
	t_rgb	ref_spec;

	l = normalize(vec_sub(light.pos, itrsec.pos));
	v = vec_scalar(ray.dir, -1);
	r = vec_sub(vec_scalar(vec_scalar(itrsec.normal, \
	vec_dot(itrsec.normal, l)), 2), l);
	ref_spec = rgb_scalar(rgb_mult(object.mtrl.spe, light.illum), \
		pow(vec_dot(v, r), object.mtrl.shininess));
	if (vec_dot(v, r) < 0)
		ref_spec = rgb_init(0, 0, 0);
	return (ref_spec);
}

void	calc_ray(t_info *info, t_ray *ray, t_object *nearest, t_rgb *result)
{
	t_itrsec	itrsec;
	t_list		*current_light;
	t_rgb		ref_diff_spec;
	t_rgb		res;

	itrsec = calc_itrsec(*ray, *nearest);
	current_light = info->lights;
	ref_diff_spec = rgb_init(0, 0, 0);
	if (itrsec.dist < 0)
		return ;
	while (current_light)
	{
		res = rgb_add(calc_ref_diff(*nearest, \
			itrsec, *(t_light *)current_light->content), calc_ref_spec(*ray, \
			*nearest, itrsec, *(t_light *)current_light->content));
		if (has_shadow(info, *(t_light *)current_light->content, itrsec))
			res = rgb_init(0, 0, 0);
		ref_diff_spec = rgb_add(ref_diff_spec, res);
		current_light = current_light->next;
	}
	*result = rgb_add(rgb_mult(nearest->mtrl.dif, info->ambient), \
		ref_diff_spec);
}
