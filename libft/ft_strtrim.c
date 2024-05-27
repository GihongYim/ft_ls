/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyim <gyim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:04:42 by gyim              #+#    #+#             */
/*   Updated: 2022/07/11 20:34:46 by gyim             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_set(char c, char const *set)
{
	if (*set == '\0')
		return (0);
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_findbound(char const *curr, char const *set, int dir)
{
	while (*curr && ft_find_set(*curr, set))
	{
		curr += dir;
	}
	return ((char *)curr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*ret;
	char const	*end;
	size_t		len;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	end = s1 + (len - 1);
	s1 = ft_findbound(s1, set, 1);
	if (*s1 == '\0')
	{
		ret = malloc(1);
		if (!ret)
			return (0);
		*ret = '\0';
		return (ret);
	}
	end = ft_findbound(end, set, -1);
	len = end - s1 + 1;
	ret = malloc(len + 1);
	if (!ret)
		return (0);
	ft_strlcpy((char *)ret, (char *)s1, len + 1);
	return (ret);
}
