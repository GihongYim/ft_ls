/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyim <gyim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:40:12 by gyim              #+#    #+#             */
/*   Updated: 2022/07/15 13:41:22 by gyim             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char const	*get_next_start(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

static int	get_num_of_words(char const *s, char c)
{
	int	ret;

	ret = 0;
	while (*s)
	{
		s = get_next_start(s, c);
		if (*s == '\0')
			break ;
		ret++;
		while (*s && *s != c)
			s++;
	}
	return (ret);
}

void	free_all(char **dst, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(dst[i]);
		dst[i++] = NULL;
	}
	free(dst);
	dst = NULL;
}

char	**alloc_words(char **dst, char const *s, char c)
{
	char const	*start;
	int			i;

	i = 0;
	while (*s)
	{
		s = get_next_start(s, c);
		if (*s == '\0')
			break ;
		start = s;
		while (*s && *s != c)
			s++;
		dst[i] = ft_substr(start, 0, (size_t)(s - start));
		if (!dst[i])
		{
			free_all(dst, i);
			break ;
		}
		i++;
	}
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char		**ret;
	int			num_of_words;

	if (s == NULL)
		return (NULL);
	num_of_words = get_num_of_words(s, c);
	ret = (char **)ft_calloc(sizeof(char *), (num_of_words + 1));
	if (!ret)
		return (NULL);
	return (alloc_words(ret, s, c));
}
