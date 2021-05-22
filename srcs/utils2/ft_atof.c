#include "../../includes/minirt.h"

double	ft_atof(char *s)
{
	long double	val;
	long double	power;
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	val = 0.0;
	power = 1.0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
		val = 10.0 * val + (s[i++] - '0');
	if (s[i] == '.')
		i++;
	while (ft_isdigit(s[i]))
	{
		val = 10.0 * val + (s[i++] - '0');
		power *= 10.0;
	}
	return ((double)sign * val / power);
}
