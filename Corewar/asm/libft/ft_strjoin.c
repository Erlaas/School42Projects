/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:44:42 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/15 12:47:55 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	const size_t	i = (s1 ? ft_strlen(s1) : 0) + (s2 ? ft_strlen(s2) : 0);
	char			*p;
	char			*ret;

	if (!s1 && !s2)
		return (NULL);
	if ((ret = ft_strnew(i)))
	{
		p = ret;
		if (s1)
			while (*s1)
				*p++ = *s1++;
		if (s2)
			while (*s2)
				*p++ = *s2++;
		*p = '\0';
	}
	return (ret);
}
