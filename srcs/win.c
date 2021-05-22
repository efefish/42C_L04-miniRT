#include "../includes/minirt.h"

int	win_set(t_info *info)
{
	int	max_width;
	int	max_height;

	mlx_get_screen_size(info->mlx, &max_width, &max_height);
	info->screen_width = int_comp(info->screen_width, max_width, 'l');
	info->screen_height = int_comp(info->screen_height, max_height, 'l');
	info->win = mlx_new_window(info->mlx, info->screen_width, \
	info->screen_height, "miniRT");
	if (!info->win)
		return (ret_err("invalid Window params"));
	return (0);
}

int	int_comp(int a, int b, char c)
{
	int	ret;

	if (c == 'l')
	{
		if (a < b)
			ret = a;
		else
			ret = b;
	}
	if (c == 'h')
	{
		if (a > b)
			ret = a;
		else
			ret = b;
	}
	return (ret);
}

void	init_normy(double *a, double *b)
{
	*a += EPSILON;
	*b += EPSILON;
}
