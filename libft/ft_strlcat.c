/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyim <gyim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 09:45:52 by gyim              #+#    #+#             */
/*   Updated: 2022/07/13 09:57:52 by gyim             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	dstlen;
	size_t	i;

	srcsize = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstsize < ft_strlen(dst))
		return (dstsize + srcsize);
	i = 0;
	while (*dst)
	{
		dst++;
		i++;
	}
	while (*src && i + 1 < dstsize)
	{
		*dst++ = *src++;
		i++;
	}
	*dst = '\0';
	return (dstlen + srcsize);
}
