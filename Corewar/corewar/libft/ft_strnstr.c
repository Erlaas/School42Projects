/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:50:20 by mdonchen          #+#    #+#             */
/*   Updated: 2018/10/28 18:49:14 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	lenger;

	while ((*haystack && len--) || *haystack == needle[0])
	{
		i = 0;
		if (needle[0] == haystack[0] || !(*needle))
		{
			lenger = len + 1;
			while (needle[i] == haystack[i] && haystack[i]
					&& needle[i] != '\0' && lenger--)
				i++;
			if (needle[i] == '\0')
				return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
