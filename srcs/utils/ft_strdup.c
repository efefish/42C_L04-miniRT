/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujisaw <tfujisaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 00:07:54 by tfujisaw          #+#    #+#             */
/*   Updated: 2021/05/10 05:39:58 by tfujisaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

char	*ft_strdup(const char *s)
{
	char		*newarray;
	size_t		i;

	newarray = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (newarray == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		newarray[i] = s[i];
		i++;
	}
	newarray[i] = '\0';
	return (newarray);
}
