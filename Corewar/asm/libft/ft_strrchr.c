/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:50:33 by mdonchen          #+#    #+#             */
/*   Updated: 2018/10/26 11:35:47 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;

	if (*s == c)
		temp = (char *)s;
	else
		temp = NULL;
	while (*s)
	{
		s++;
		if (*s == c)
			temp = (char *)s;
	}
	return ((char *)temp);
}
