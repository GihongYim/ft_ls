/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyim <gyim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 10:30:31 by gyim              #+#    #+#             */
/*   Updated: 2022/07/15 10:09:40 by gyim             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_num_len(long long n)
{
	int	ret;

	ret = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		ret++;
		n /= 10;
	}
	return (ret);
}

void	get_num(char *dst, long long n, int len)
{
	dst[len--] = '\0';
	if (n == 0)
		dst[len] = '0';
	while (n > 0)
	{
		dst[len--] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	int			negative;
	char		*ret;
	int			len;
	long long	num;

	len = 0;
	negative = 0;
	num = n;
	if (num < 0)
	{
		negative = 1;
		num *= -1;
		len++;
	}
	len += get_num_len(num);
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	if (negative)
		ret[0] = '-';
	get_num(ret + negative, num, len - negative);
	return (ret);
}
