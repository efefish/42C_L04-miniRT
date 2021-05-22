#include "../../includes/minirt.h"

int	ft_ch_dir_vec(t_vec *chdir)
{
	if (chdir->x < -1.0 || 1.0 < chdir->x
		|| chdir->y < -1.0 || 1.0 < chdir->y
		|| chdir->z < -1.0 || 1.0 < chdir->z)
		return (-1);
	return (0);
}
