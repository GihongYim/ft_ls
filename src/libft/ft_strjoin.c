/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyim <gyim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:45:54 by gyim              #+#    #+#             */
/*   Updated: 2022/07/15 09:31:13 by gyim             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		s1_len;
	size_t		s2_len;
	char		*newstr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr = malloc(s1_len + s2_len + 1);
	if (!newstr)
		return (0);
	ft_strlcpy(newstr, (char *)s1, s1_len + 1);
	ft_strlcat(newstr, (char *)s2, s1_len + s2_len + 1);
	return (newstr);
}
