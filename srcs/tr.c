#include "../includes/minirt.h"

int	calc_tr(t_vec point, t_tr *tr)
{
	t_vec	cross_1;
	t_vec	cross_2;
	t_vec	cross_3;
	int		check[3];

	cross_1 = normalize(vec_cross(vec_sub(tr->Betelgeuse, tr->Sirius), \
	vec_sub(point, tr->Sirius)));
	cross_2 = normalize(vec_cross(vec_sub(tr->Sirius, tr->Procyon), \
	vec_sub(point, tr->Procyon)));
	cross_3 = normalize(vec_cross(vec_sub(tr->Procyon, tr->Betelgeuse), \
	vec_sub(point, tr->Betelgeuse)));
	check[0] = vec_dot(cross_1, cross_2) < 0;
	check[1] = vec_dot(cross_2, cross_3) < 0;
	check[2] = vec_dot(cross_3, cross_1) < 0;
	if ((check[0] && check[1] && check[2])
		|| (!check[0] && !check[1] && !check[2]))
		return (1);
	return (0);
}

t_itrsec	tr_itrsec(t_ray ray, t_tr *tr)
{
	t_vec		tr_normal;
	double		d_n_dot;
	t_vec		c_cam;
	double		t;
	t_itrsec	itrsec;

	tr_normal = normalize(vec_cross(vec_sub(tr->Betelgeuse, tr->Sirius), \
	vec_sub(tr->Procyon, tr->Sirius)));
	c_cam = vec_sub(ray.start, tr->Sirius);
	d_n_dot = vec_dot(vec_scalar(ray.dir, -1), tr_normal);
	if (d_n_dot == 0)
	{
		itrsec.has_itrsec = 0;
		return (itrsec);
	}
	t = vec_dot(c_cam, tr_normal) / d_n_dot;
	itrsec.dist = t;
	if (d_n_dot > 0)
		itrsec.normal = tr_normal;
	else
		itrsec.normal = vec_scalar(tr_normal, -1);
	itrsec.pos = vec_add(ray.start, vec_scalar(ray.dir, t));
	itrsec.has_itrsec = calc_tr(itrsec.pos, tr);
	return (itrsec);
}

t_object	*init_tr(t_vec Sirius, t_vec Procyon, t_vec Betelgeuse, t_mtrl mtrl)
{
	t_object	*tr;

	tr = malloc(sizeof(t_object));
	if (tr == NULL)
		return (NULL);
	tr->type = TR;
	tr->data.tr.Sirius = Sirius;
	tr->data.tr.Procyon = Procyon;
	tr->data.tr.Betelgeuse = Betelgeuse;
	tr->mtrl = mtrl;
	return (tr);
}

int	ch_tr(t_info *info, char **array)
{
	t_object	*object;
	t_vec		Sirius;
	t_vec		Procyon;
	t_vec		Betelgeuse;
	t_rgb		rgb;

	if (ft_poipoi_strlen((void **)array) != 4
		|| ft_str2vec(&Sirius, array[0]) == ERROR
		|| ft_str2vec(&Procyon, array[1]) == ERROR
		|| ft_str2vec(&Betelgeuse, array[2]) == ERROR
		|| rgb2bin(&rgb, array[3]) == ERROR)
		return (ret_err("invalid tr params"));
	object = init_tr(Sirius, Procyon, Betelgeuse, \
	init_mtrl(rgb, rgb_init(0.3, 0.3, 0.3), 42));
	if (!object || !(ft_lstadd_back_new(&info->objects, object)))
		return (ret_err("failed malloc"));
	return (0);
}
