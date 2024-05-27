/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyim <gyim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:35:18 by gyim              #+#    #+#             */
/*   Updated: 2022/07/15 20:15:47 by gyim             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dtmp;
	unsigned char	*stmp;

	if (dst == NULL && src == NULL)
		return (NULL);
	dtmp = (unsigned char *)dst;
	stmp = (unsigned char *)src;
	if (dst < src)
		while (len--)
			*(dtmp++) = *(stmp++);
	else
		while (len--)
			*(dtmp + len) = *(stmp + len);
	return (dst);
}
