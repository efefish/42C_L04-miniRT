#include "../includes/minirt.h"

// red, green, blue の値を0.0~1.0に丸める
t_rgb	rgb_normalize(t_rgb rgb)
{
	if (rgb.r < 0)
		rgb.r = 0.0;
	if (rgb.g < 0)
		rgb.g = 0.0;
	if (rgb.b < 0)
		rgb.b = 0.0;
	if (rgb.r > 1.0)
		rgb.r = 1.0;
	if (rgb.g > 1.0)
		rgb.g = 1.0;
	if (rgb.b > 1.0)
		rgb.b = 1.0;
	return (rgb);
}
// 各成分から構造体の値を返す

t_rgb	rgb_init(double r, double g, double b)
{
	t_rgb	rtn;

	rtn.r = r;
	rtn.g = g;
	rtn.b = b;
	return (rgb_normalize(rtn));
}
// t_rgb同士の足し算

t_rgb	rgb_add(t_rgb a, t_rgb b)
{
	a.r += b.r;
	a.g += b.g;
	a.b += b.b;
	return (rgb_normalize(a));
}

// t_rgb同士の各要素同士の掛け算
t_rgb	rgb_mult(t_rgb a, t_rgb b)
{
	a.r *= b.r;
	a.g *= b.g;
	a.b *= b.b;
	return (rgb_normalize(a));
}

t_mtrl	init_mtrl(t_rgb diffuse, t_rgb specular, double shininess)
{
	t_mtrl	mtrl;

	mtrl.dif = diffuse;
	mtrl.spe = specular;
	mtrl.shininess = shininess;
	return (mtrl);
}
