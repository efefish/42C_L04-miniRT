#include "../includes/minirt.h"

int	main_loop(t_info *info)
{
	t_cam	*cam;

	cam = (t_cam *)info->cameras->data;
	mlx_put_image_to_window(info->mlx, info->win, cam->img.img, 0, 0);
	return (0);
}

int	info_init(t_info *info)
{
	info->screen_width = 0;
	info->screen_height = 0;
	info->cameras = NULL;
	info->objects = NULL;
	info->lights = NULL;
	info->ambient = amb_init(-1, -1, -1);
	info->mlx = mlx_init();
	return (0);
}

int	exit_window(t_info *info)
{
	if (info->mlx && info->win)
		mlx_destroy_window(info->mlx, info->win);
	if (info->mlx)
		mlx_destroy_display(info->mlx);
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_info	info;

	if (argc < 2 || argc > 3)
		exit_err("invalid arguments");
	info_init(&info);
	if ((read_rtfile(&info, argv[1])) == ERROR)
		exit_err("invalid files");
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", ft_strlen("--save") + 1))
			exit_err("invalid third argv");
		save_bmp(&info);
	}
	if (win_set(&info) == ERROR)
		return (ERROR);
	make_object(&info);
	mlx_hook(info.win, 2, 1, key_press, &info);
	mlx_hook(info.win, HOOK_NUM, 1L << 17, exit_window, &info);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_loop(info.mlx);
	return (0);
}
