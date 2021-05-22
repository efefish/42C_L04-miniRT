#include "../includes/minirt.h"

t_itrsec	calc_itrsec(t_ray ray, t_object object)
{
	t_itrsec	rtn;

	if (object.type == SP)
		rtn = sp_itrsec(ray, &object.data.sp);
	else if (object.type == PL)
		rtn = pl_itrsec(ray, &object.data.pl);
	else if (object.type == CY)
		rtn = cy_itrsec(ray, &object.data.cy);
	else if (object.type == SQ)
		rtn = sq_itrsec(ray, &object.data.sq);
	else if (object.type == TR)
		rtn = tr_itrsec(ray, &object.data.tr);
	else
		rtn.has_itrsec = 0;
	return (rtn);
}

t_object	*get_front_obj(t_info *info, t_ray ray)
{
	t_object		*nearest;
	t_object		*current;
	double			n_dist;
	t_list			*current_lst;
	t_itrsec		itrsec;

	n_dist = INFINITY;
	nearest = NULL;
	current_lst = info->objects;
	while (current_lst)
	{
		current = (t_object *)current_lst->content;
		itrsec = calc_itrsec(ray, *current);
		if (itrsec.has_itrsec)
		{
			if (itrsec.dist >= 0 && itrsec.dist <= n_dist)
			{
				nearest = current;
				n_dist = itrsec.dist;
			}
		}
		current_lst = current_lst->next;
	}
	return (nearest);
}

void	raytrace(t_info *info, t_cam *cam, int x, int y)
{
	t_ray		ray;
	t_object	*front_obj;
	t_rgb		rgb_pxl;

	ray.dir = normalize(vec_add(cam->d_center, vec_add(vec_scalar(cam->x_basis, \
	(x - (info->screen_width - 1) / 2)), vec_scalar(cam->y_basis, \
	((info->screen_height - 1) / 2 - y)))));
	ray.start = cam->pos;
	front_obj = get_front_obj(info, ray);
	if (front_obj)
	{
		calc_ray(info, &ray, front_obj, &rgb_pxl);
		my_mlx_pixel_put(&cam->img, x, y, col_to_hex(rgb_pxl));
	}
	else
		my_mlx_pixel_put(&cam->img, x, y, rgb_to_col(0, 0, 0));
}

void	make_object(t_info *info)
{
	t_dlist		*first_cam;
	t_cam		*cam;
	int			x;
	int			y;

	first_cam = info->cameras;
	while (1)
	{
		cam = (t_cam *)info->cameras->data;
		printf("%lf %lf %lf\n", cam->pos.x, cam->pos.y, cam->pos.z);
		y = 0;
		while (y < info->screen_height)
		{
			x = -1;
			while (++x < info->screen_width)
				raytrace(info, cam, x, y);
			y++;
		}
		info->cameras = info->cameras->next;
		if (info->cameras == first_cam)
			break ;
	}
}
