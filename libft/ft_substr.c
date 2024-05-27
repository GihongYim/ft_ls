/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyim <gyim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:25:45 by gyim              #+#    #+#             */
/*   Updated: 2022/07/12 16:13:27 by gyim             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_getlen(const char *s1, size_t len)
{
	size_t	size;

	size = ft_strlen(s1);
	if (size > len)
		size = len;
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	size;

	if (!s)
		return (0);
	if (start >= (unsigned int)ft_strlen(s))
	{
		ret = malloc(1);
		if (!ret)
			return (0);
		ret[0] = '\0';
		return (ret);
	}
	size = ft_getlen(s + start, len);
	ret = malloc(size + 1);
	if (!ret)
		return (0);
	ft_strlcpy(ret, (char *)s + start, size + 1);
	return (ret);
}
