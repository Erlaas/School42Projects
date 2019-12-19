/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:45:07 by mdonchen          #+#    #+#             */
/*   Updated: 2018/10/28 16:29:41 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (siz == 0)
		return (srclen);
	i = ft_strlen(dst);
	if (i > siz - 1)
		return (siz + srclen);
	j = 0;
	while (i + j < siz - 1 && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + srclen);
}
