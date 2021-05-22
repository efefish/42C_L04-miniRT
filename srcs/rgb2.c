#include "../includes/minirt.h"

t_rgb	rgb_scalar(t_rgb rgb, double n)
{
	t_rgb	rtn;

	rtn.r = rgb.r * n;
	rtn.g = rgb.g * n;
	rtn.b = rgb.b * n;
	return (rgb_normalize(rtn));
}

int	rgb_to_col(int r, int g, int b)
{
	r = int_comp(0, int_comp(r, 255, 'l'), 'h');
	g = int_comp(0, int_comp(g, 255, 'l'), 'h');
	b = int_comp(0, int_comp(b, 255, 'l'), 'h');
	return (r << 16 | g << 8 | b);
}

int	rgb_range(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}

int	get_rgbhex_from_rgbstr(unsigned int *rgb, char *rgbstr)
{
	char	**rgb_ar;

	if (ft_strchr_counter(rgbstr, ',') != 2 \
	|| ft_split_counter(rgbstr, ',') != 3)
		return (ret_err("invalid rgb params"));
	rgb_ar = ft_split(rgbstr, ',');
	if (!rgb_ar)
		return (ERROR);
	if (!ft_digit_check(rgb_ar[0]) || !ft_digit_check(rgb_ar[1]) \
	|| !ft_digit_check(rgb_ar[2]) || !rgb_range(ft_atoi(rgb_ar[0]), \
		ft_atoi(rgb_ar[1]), ft_atoi(rgb_ar[2]))
		|| (rgb_ar[0][0] == '0' && rgb_ar[0][1])
		|| (rgb_ar[1][0] == '0' && rgb_ar[1][1])
		|| (rgb_ar[2][0] == '0' && rgb_ar[2][1]))
	{
		free_array((void **)rgb_ar);
		return (ERROR);
	}
	*rgb = 0;
	*rgb = ft_atoi(rgb_ar[0]) << 16 \
	| ft_atoi(rgb_ar[1]) << 8 | ft_atoi(rgb_ar[2]);
	free_array((void **)rgb_ar);
	return (0);
}

int	rgb2bin(t_rgb *rgb, char *rgbstr)
{
	unsigned int	rgbhex;
	double			r;
	double			g;
	double			b;

	if (get_rgbhex_from_rgbstr(&rgbhex, rgbstr) == ERROR)
		return (ret_err("coloring error"));
	r = (double)(rgbhex >> 16 & 0xff) / 255;
	g = (double)(rgbhex >> 8 & 0xff) / 255;
	b = (double)(rgbhex & 0xff) / 255;
	*rgb = rgb_init(r, g, b);
	return (0);
}
