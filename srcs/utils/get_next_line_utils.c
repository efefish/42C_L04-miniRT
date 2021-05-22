/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujisaw <tfujisaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:01:21 by tfujisaw          #+#    #+#             */
/*   Updated: 2021/05/08 00:25:20 by tfujisaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strjoin(char const *s1, char const *s2, size_t len)
{
	size_t				len_s1;
	char				*array;
	unsigned long long	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = gnl_strlen(s1);
	array = (char *)malloc(sizeof(char) * (len_s1 + len + 1));
	if (array == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		array[i] = s1[i];
	i = 0;
	while (s2[i] && i < len)
	{
		array[i + len_s1] = s2[i];
		i++;
	}
	array[i + len_s1] = '\0';
	return (array);
}

char	*gnl_strdup(const char *s)
{
	char		*newarray;
	size_t		i;

	newarray = (char *)malloc(sizeof(char) * (gnl_strlen(s) + 1));
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

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	gnl_strchr(const char *s, char c)
{
	size_t	s_len;
	size_t	i;

	s_len = gnl_strlen(s);
	i = 0;
	while (i < s_len)
	{
		if (s[i] == (char)c)
			break ;
		i++;
	}
	return (i);
}
