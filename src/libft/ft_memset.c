/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyim <gyim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:25:42 by gyim              #+#    #+#             */
/*   Updated: 2022/07/12 18:11:49 by gyim             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*target;

	target = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		*target = (unsigned char)c;
		target++;
		i++;
	}
	return (b);
}
