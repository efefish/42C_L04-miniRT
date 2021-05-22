#include "../includes/minirt.h"

int	calc_sq(t_vec point, t_sq *sq)
{
	t_vec		x_basis;
	t_vec		y_basis;
	t_vec		o_p;
	double		x_dist;
	double		y_dist;

	if (sq->normal.y == 1 || sq->normal.y == -1)
		init_normy(&sq->normal.x, &sq->normal.z);
	x_basis.x = sq->normal.z / sqrt(sq->normal.z * \
	sq->normal.z + sq->normal.x * sq->normal.x);
	x_basis.y = 0;
	x_basis.z = -sq->normal.x / sqrt(sq->normal.z \
	* sq->normal.z + sq->normal.x * sq->normal.x);
	x_basis = normalize(x_basis);
	y_basis = normalize(vec_cross(x_basis, vec_scalar(sq->normal, -1)));
	o_p = vec_sub(point, sq->center);
	x_dist = vec_dot(o_p, x_basis);
	y_dist = vec_dot(o_p, y_basis);
	if (x_dist >= -sq->side_size / 2 && x_dist <= sq->side_size / 2
		&& y_dist >= -sq->side_size / 2 && y_dist <= sq->side_size / 2)
		return (1);
	return (0);
}

t_itrsec	sq_itrsec(t_ray ray, t_sq *sq)
{
	double		d_n_dot;
	t_vec		c_cam;
	double		t;
	t_itrsec	itrsec;

	c_cam = vec_sub(ray.start, sq->center);
	d_n_dot = vec_dot(vec_scalar(ray.dir, -1), sq->normal);
	if (d_n_dot == 0)
	{
		itrsec.has_itrsec = 0;
		return (itrsec);
	}
	t = vec_dot(c_cam, sq->normal) / d_n_dot;
	itrsec.dist = t;
	if (d_n_dot > 0)
		itrsec.normal = sq->normal;
	else
		itrsec.normal = vec_scalar(sq->normal, -1);
	itrsec.pos = vec_add(ray.start, vec_scalar(ray.dir, t));
	itrsec.has_itrsec = calc_sq(itrsec.pos, sq);
	return (itrsec);
}

t_object	*init_sq(t_vec center, t_vec normal, double side_size,
					t_mtrl mtrl)
{
	t_object	*sq;

	sq = malloc(sizeof(t_object));
	if (sq == NULL)
		return (NULL);
	sq->type = SQ;
	sq->data.sq.center = center;
	sq->data.sq.normal = normal;
	sq->data.sq.side_size = side_size;
	sq->mtrl = mtrl;
	return (sq);
}

int	ch_sq(t_info *info, char **array)
{
	t_object	*object;
	t_vec		point;
	double		side_size;
	t_vec		normal;
	t_rgb		rgb;

	if (ft_poipoi_strlen((void **)array) != 4
		|| ft_str2vec(&point, array[0]) == ERROR
		|| ft_str2vec(&normal, array[1]) == ERROR
		|| rgb2bin(&rgb, array[3]) == ERROR)
		return (ret_err("invalid sq params"));
	if (ch_normal_range(&normal) == ERROR)
		return (ret_err("invalid normal params"));
	side_size = ft_atof(array[2]);
	object = init_sq(point, normalize(normal), side_size, \
		init_mtrl(rgb, rgb_init(0.3, 0.3, 0.3), 42));
	if (!object || !(ft_lstadd_back_new(&info->objects, object)))
		return (ret_err("failed malloc"));
	return (0);
}
