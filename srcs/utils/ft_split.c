/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujisaw <tfujisaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 00:08:39 by tfujisaw          #+#    #+#             */
/*   Updated: 2021/05/06 06:29:04 by tfujisaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static	size_t	ar_count(char const *s, char c)
{
	size_t	i;
	size_t	checker;

	if (s == NULL)
		return ('\0');
	i = 1;
	checker = 0;
	while (s[i - 1])
	{
		if ((s[i] == c || s[i] == '\0') && s[i - 1] != c)
			checker++;
		i++;
	}
	return (checker);
}

static size_t	wordslen(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static	char	**set_free(char **array, int i)
{
	while (i > 0)
		free(array[--i]);
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	j;
	size_t	ar_counter;

	ar_counter = ar_count(s, c);
	array = (char **)malloc(sizeof(char *) * (ar_counter + 1));
	if (array == NULL || s == NULL)
		return (NULL);
	i = 0;
	while (i < ar_counter)
	{
		array[i] = (char *)malloc(sizeof(char) * wordslen(s, c) + 1);
		if (array[i] == NULL)
			return (set_free(array, i));
		j = 0;
		while (*s == c)
			s++;
		while (*s != c && *s != '\0')
			array[i][j++] = *s++;
		array[i][j] = '\0';
		i++;
	}
	array[i] = NULL;
	return (array);
}
