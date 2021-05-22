#include "../includes/minirt.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_color_from_img(t_img img, int x, int y)
{
	return (*(unsigned int *)(img.addr
		+ (y * img.line_length + x * (img.bits_per_pixel / 8))));
}

int	key_press(int key, t_info *info)
{
	if (key == KEYCODE_ESC)
	{
		mlx_destroy_window(info->mlx, info->win);
		exit(0);
	}
	if (key == KEYCODE_LEFT)
		if (info->cameras)
			info->cameras = info->cameras->next;
	if (key == KEYCODE_RIGHT)
		if (info->cameras)
			info->cameras = info->cameras->prev;
	return (0);
}
