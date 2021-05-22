#include "../includes/minirt.h"

void	cam_basis(t_cam *cam)
{
	t_vec	x_basis;
	t_vec	y_basis;

	x_basis.x = cam->d_center.z / sqrt(cam->d_center.z \
		* cam->d_center.z + cam->d_center.x * cam->d_center.x);
	x_basis.y = 0;
	x_basis.z = -cam->d_center.x / sqrt(cam->d_center.z \
		* cam->d_center.z + cam->d_center.x * cam->d_center.x);
	y_basis = normalize(vec_cross(x_basis, vec_scalar(cam->d_center, -1)));
	if (cam->dir.x == 0 && cam->dir.y != 0 && cam->dir.z == 0)
	{
		if (cam->dir.y > 0)
		{
			x_basis = vec_init(-1, 0, 0);
			y_basis = vec_init(0, 0, -1);
		}
		else
		{
			x_basis = vec_init(1, 0, 0);
			y_basis = vec_init(0, 0, 1);
		}
	}
	cam->x_basis = x_basis;
	cam->y_basis = y_basis;
}

t_cam	*cam_setup(t_info *info, t_vec pos, t_vec dir, double fov)
{
	t_cam	*cam;
	double	d;

	cam = malloc(sizeof(t_cam));
	if (cam == NULL)
		return (NULL);
	cam->pos = pos;
	cam->dir = dir;
	cam->fov = fov;
	cam->img.img = mlx_new_image(info->mlx,
			info->screen_width, info->screen_height);
	cam->img.addr = mlx_get_data_addr(cam->img.img, &cam->img.bits_per_pixel,
			&cam->img.line_length, &cam->img.endian);
	cam->img.width = info->screen_width;
	cam->img.height = info->screen_height;
	d = info->screen_width / 2 / tan(cam->fov / 2 / 180 * M_PI);
	cam->d_center = vec_scalar(cam->dir, d);
	return (cam);
}

t_cam	*cam_init(t_info *info, t_vec pos, t_vec dir, double fov)
{
	t_cam	*cam;

	cam = cam_setup(info, pos, dir, fov);
	cam_basis(cam);
	return (cam);
}

int	ch_cam(t_info *info, t_cam *tmp)
{
	int		i;
	t_cam	*cam;

	i = 0;
	while (i < tmp->n)
	{
		if (info->screen_width == 0 || info->screen_height == 0 )
			return (ret_err("invalid window params"));
		cam = cam_init(info, (tmp + i)->pos, normalize((tmp + i)->dir), \
		(tmp + i)->fov);
		if (!cam || !(ft_new_dlist(&info->cameras, (void *)cam)))
			return (ret_err("failed dlist malloc"));
		i++;
	}
	return (0);
}

int	cam_tmp(char **array, t_cam *tmp)
{
	static int	i;

	if (i > 100)
		return (ret_err("too many cameras"));
	if (ft_poipoi_strlen((void **)array) != 3
		|| ft_str2vec(&(tmp + i)->pos, array[0]) == ERROR
		|| ft_str2vec(&(tmp + i)->dir, array[1]) == ERROR)
		return (ret_err("invalid cam params"));
	if (ft_ch_dir_vec(&tmp->dir) == ERROR)
		return (ret_err("invalid directionVector params"));
	(tmp + i)->fov = ft_atof(array[2]);
	i++;
	tmp->n = i;
	return (0);
}
