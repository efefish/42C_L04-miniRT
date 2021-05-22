/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujisaw <tfujisaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 00:08:42 by tfujisaw          #+#    #+#             */
/*   Updated: 2021/05/10 03:45:44 by tfujisaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	char	*array;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	array = (char *)malloc(sizeof(char) * (len_s1 + ft_strlen(s2) + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		array[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		array[i + len_s1] = s2[i];
		i++;
	}
	array[i + len_s1] = '\0';
	return (array);
}
