#include "../includes/minirt.h"

int	ret_err(char *str)
{
	ft_putstr_fd("Error:", 2);
	ft_putendl_fd(str, 2);
	return (ERROR);
}

int	exit_err(char *str)
{
	ft_putstr_fd("Error:", 2);
	ft_putendl_fd(str, 2);
	exit(1);
}
