/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyim <gyim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:20:50 by gyim              #+#    #+#             */
/*   Updated: 2022/07/15 20:15:46 by gyim             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		needlelen;

	needlelen = ft_strlen(needle);
	if (needlelen == 0)
		return ((char *)haystack);
	i = 0;
	while (*haystack && i + needlelen <= len)
	{
		j = 0;
		while (*(haystack + j) && *(needle + j)
			&& *(haystack + j) == *(needle + j))
			j++;
		if (*(needle + j) == '\0')
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (NULL);
}
