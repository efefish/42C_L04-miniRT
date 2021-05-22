#include "../includes/minirt.h"

t_vec	vec_init(double x, double y, double z)
{
	t_vec	rtn;

	rtn.x = x;
	rtn.y = y;
	rtn.z = z;
	return (rtn);
}
// ベクトルの足し算 a + b

t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	rtn;

	rtn.x = a.x + b.x;
	rtn.y = a.y + b.y;
	rtn.z = a.z + b.z;
	return (rtn);
}
// ベクトルの引き算 a - b

t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	rtn;

	rtn.x = a.x - b.x;
	rtn.y = a.y - b.y;
	rtn.z = a.z - b.z;
	return (rtn);
}
// ベクトルの定数倍 a * b

t_vec	vec_scalar(t_vec a, double b)
{
	t_vec	rtn;

	rtn.x = a.x * b;
	rtn.y = a.y * b;
	rtn.z = a.z * b;
	return (rtn);
}

int	ch_normal_range(t_vec *n)
{
	if (n->x < -1.0 || 1.0 < n->x
		|| n->y < -1.0 || 1.0 < n->y
		|| n->z < -1.0 || 1.0 < n->z)
		return (-1);
	return (0);
}
