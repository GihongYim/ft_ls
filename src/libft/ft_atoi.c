/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyim <gyim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:51:02 by gyim              #+#    #+#             */
/*   Updated: 2022/07/14 13:29:26 by gyim             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_sign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

int	ft_over(unsigned long long n, int sign)
{
	unsigned long long	llmax;

	llmax = 9223372036854775807;
	if (sign == 1 && n > llmax)
		return (-1);
	if (sign == -1 && n > llmax + 1)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	unsigned long long	ret;
	int					sign;

	ret = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		ret *= 10;
		ret += (*str - '0');
		str++;
		if (ft_over(ret, sign) != 1)
			return (ft_over(ret, sign));
	}
	ret *= sign;
	return ((int) ret);
}
