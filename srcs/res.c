#include "../includes/minirt.h"

int	ch_res(t_info *info, char **array)
{
	int	screen_width;
	int	screen_height;

	if (ft_poipoi_strlen((void **)array) != 2)
		return (exit_err("invalid Resolution Params"));
	if (info->screen_width || info->screen_height)
		return (exit_err("Resolution params are already exist"));
	if (!ft_digit_check(array[0]) || !ft_digit_check(array[1]))
		return (exit_err("invalid Resolution Params(not figure)"));
	screen_width = ft_atoi(array[0]);
	screen_height = ft_atoi(array[1]);
	if ((array[0][0] == '0' && screen_width)
		|| (array[1][0] == '0' && screen_height)
		|| screen_width <= 0 || screen_height <= 0)
		return (exit_err("invalid Resolution Params(cant make Window)"));
	info->screen_width = screen_width;
	info->screen_height = screen_height;
	return (0);
}
