#include "../includes/minirt.h"

void	bmp_img_data(t_img *img, int fd)
{
	unsigned int	tmp;
	int				x;
	int				y;

	y = img->height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < img->width)
		{
			tmp = get_color_from_img(*img, x, y);
			write(fd, &tmp, 4);
			x++;
		}
		y--;
	}
}

void	bmp_info_header(t_img *img, int fd)
{
	unsigned int	tmp;

	tmp = 12;
	write(fd, &tmp, 4);
	write(fd, &img->width, 2);
	write(fd, &img->height, 2);
	tmp = 1;
	write(fd, &tmp, 2);
	tmp = 32;
	write(fd, &tmp, 2);
}

void	bmp_file_header(t_img *img, int fd)
{
	unsigned int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 10 + img->width * img->height * 4;
	write(fd, &tmp, 4);
	write(fd, "\0\0", 2);
	write(fd, "\0\0", 2);
	tmp = 14 + 10;
	write(fd, &tmp, 4);
}

int	cam2bmp(t_cam *cam, char *filepath)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd == -1)
		return (-1);
	bmp_file_header(&cam->img, fd);
	bmp_info_header(&cam->img, fd);
	bmp_img_data(&cam->img, fd);
	close(fd);
	return (0);
}

int	save_bmp(t_info *info)
{
	t_dlist		*first_cam;
	t_cam		*cam;
	char		*filepath;
	int			idx;

	make_object(info);
	first_cam = info->cameras;
	idx = 0;
	while (1)
	{
		cam = (t_cam *)info->cameras->data;
		filepath = ft_strjoin(ft_itoa(idx), "cam.bmp");
		cam2bmp(cam, filepath);
		printf("fin made bmpfile %s\n", filepath);
		free(filepath);
		info->cameras = info->cameras->next;
		idx++;
		if (info->cameras == first_cam)
			break ;
	}
	printf("fin made all bmpfile\n");
	exit(0);
}
