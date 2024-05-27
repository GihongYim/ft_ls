/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyim <gyim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:24:51 by gyim              #+#    #+#             */
/*   Updated: 2022/07/15 12:38:04 by gyim             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*t1;
	char	*t2;

	t1 = (char *)s1;
	t2 = (char *)s2;
	i = 0;
	while (i < n && *t1 == *t2)
	{
		i++;
		t1++;
		t2++;
	}
	if (i == n)
		return (0);
	else
		return ((int)((unsigned char)*t1 - (unsigned char)*t2));
}
