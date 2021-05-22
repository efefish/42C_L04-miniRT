#include "../includes/minirt.h"

void	free_array(void **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i++] = NULL;
	}
	free(array);
}

void	ch_array(t_info *info, char **array, int *ret, t_cam *tmp)
{
	if ((*ret >= 0 && array[0])
		&& (ft_strlen(array[0]) == 1 && array[0][0] == 'R'))
		*ret = ch_res(info, array + 1);
	else if ((*ret >= 0 && array[0])
		&& (ft_strlen(array[0]) == 1 && array[0][0] == 'A'))
		*ret = ch_amb(info, array + 1);
	else if ((*ret >= 0 && array[0])
		&& (ft_strlen(array[0]) == 1 && array[0][0] == 'c'))
		*ret = cam_tmp(array + 1, tmp);
	else if ((*ret >= 0 && array[0])
		&& (ft_strlen(array[0]) == 1 && array[0][0] == 'l'))
		*ret = ch_light(info, array + 1);
	else if ((*ret >= 0 && array[0]) && ft_strncmp(array[0], "pl", 3) == 0)
		*ret = ch_pl(info, array + 1);
	else if ((*ret >= 0 && array[0]) && ft_strncmp(array[0], "sp", 3) == 0)
		*ret = ch_sp(info, array + 1);
	else if ((*ret >= 0 && array[0]) && ft_strncmp(array[0], "tr", 3) == 0)
		*ret = ch_tr(info, array + 1);
	else if ((*ret >= 0 && array[0]) && ft_strncmp(array[0], "cy", 3) == 0)
		*ret = ch_cy(info, array + 1);
	else if ((*ret >= 0 && array[0]) && ft_strncmp(array[0], "sq", 3) == 0)
		*ret = ch_sq(info, array + 1);
	else
		*ret = no_params(array);
}

int	divide_file(int fd, t_info *info)
{
	char	*line;
	int		ret;
	char	**array;
	int		gnl_ret;
	t_cam	tmp[100];

	ret = 0;
	while (ret >= 0)
	{
		gnl_ret = get_next_line(fd, &line);
		array = ft_split(line, ' ');
		if (!array || gnl_ret == -1)
			ret = -1;
		ch_array(info, array, &ret, tmp);
		free(line);
		line = NULL;
		free_array((void **)array);
		if (gnl_ret != 1)
			break ;
	}
	free(line);
	ch_cam(info, tmp);
	return (ret);
}

int	ch_rtfile_name(char *str)
{
	size_t	name_len;

	name_len = ft_strlen(str);
	return (!(name_len < 4 || str[name_len - 4] == '/'
			|| ft_strncmp(str + name_len - 3, ".rt", 3)));
}

int	read_rtfile(t_info *info, char *str)
{
	int		fd;

	if (!ch_rtfile_name(str))
		return (ret_err("invalid file type"));
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ret_err("open error"));
	return (divide_file(fd, info));
}
