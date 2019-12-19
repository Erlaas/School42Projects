/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:51:37 by mdonchen          #+#    #+#             */
/*   Updated: 2018/10/26 14:13:53 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;

	while (*haystack || needle[0] == *haystack)
	{
		i = 0;
		if (*needle == *haystack || !(*needle))
		{
			while (needle[i] == haystack[i] && haystack[i])
				i++;
			if (!(needle[i]))
				return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
