/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyim <gyim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:25:25 by gyim              #+#    #+#             */
/*   Updated: 2022/07/14 19:40:27 by gyim             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dest;

	if (!dst && !src)
		return (NULL);
	dest = (char *)dst;
	while (n--)
	{
		*(dest++) = *((char *)src++);
	}
	return (dst);
}
