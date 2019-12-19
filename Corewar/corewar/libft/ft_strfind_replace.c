/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 17:05:32 by mdonchen          #+#    #+#             */
/*   Updated: 2018/10/30 17:18:58 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfind_replace(char *s1, char f, char r)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s1 || !f || !r)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (NULL);
	while (s1[i])
	{
		if (s1[i] == f)
			str[i] = r;
		else
			str[i] = s1[i];
		i++;
	}
	return (str);
}
