/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:42:37 by mdonchen          #+#    #+#             */
/*   Updated: 2018/10/31 13:29:55 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*ret_str;
	int		len;

	len = 0;
	while (str[len] != '\0')
		len++;
	if (!(ret_str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	len = 0;
	while (str[len])
	{
		ret_str[len] = str[len];
		len++;
	}
	ret_str[len] = '\0';
	return (ret_str);
}
