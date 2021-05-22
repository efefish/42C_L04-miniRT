#include "../includes/minirt.h"

t_rgb	amb_init(double r, double g, double b)
{
	t_rgb	rtn;

	rtn.r = r;
	rtn.g = g;
	rtn.b = b;
	return (rtn);
}

unsigned int	rgb_to_hex(int r, int g, int b)
{
	unsigned int	rgb;

	rgb = 0;
	rgb |= b;
	rgb |= g << 8;
	rgb |= r << 16;
	return (rgb);
}

unsigned int	col_to_hex(t_rgb rgb)
{
	return (rgb_to_hex(rgb.r * 255, rgb.g * 255, rgb.b * 255));
}

int	ch_amb(t_info *info, char **array)
{
	t_rgb	rgb;
	double	illuminate;
	size_t	i;

	if (info->ambient.r != -1 || info->ambient.g != -1 \
		|| info->ambient.b != -1)
		return (ret_err("Ambient params already exist"));
	i = 0;
	while (array[i])
		i++;
	if (i != 2)
		return (ret_err("invalid Ambient params"));
	illuminate = ft_atof(array[0]);
	if (rgb2bin(&rgb, array[1]) == ERROR)
		return (ret_err("invalid Ambient params"));
	info->ambient = rgb_scalar(rgb, illuminate);
	return (0);
}
