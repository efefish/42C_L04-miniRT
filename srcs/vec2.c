#include "../includes/minirt.h"

// ベクトルの内積a·b
double	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
// ベクトルの外積 a × b

t_vec	vec_cross(t_vec a, t_vec b)
{
	t_vec	rtn;

	rtn.x = a.y * b.z - a.z * b.y;
	rtn.y = a.z * b.x - a.x * b.z;
	rtn.z = a.x * b.y - a.y * b.x;
	return (rtn);
}

double	squared_norm(t_vec v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	norm(t_vec v)
{
	return (sqrt(squared_norm(v)));
}

// ベクトルの大きさを1にしたものを返す

t_vec	normalize(t_vec v)
{
	t_vec	rtn;
	double	vnorm;

	vnorm = norm(v);
	rtn.x = v.x / vnorm;
	rtn.y = v.y / vnorm;
	rtn.z = v.z / vnorm;
	return (rtn);
}

// ベクトルの大きさ(長さ) |a|
//double	vec_mag(t_vec a)

//"x,y,z" の形式のテキストをパースしてvecポインタに格納して
//ステータスを返す(0は成功. -1以外ならエラー)
//int		get_vec_from_str(t_vec *vec, char *str)
