/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strends.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:08:08 by mdonchen          #+#    #+#             */
/*   Updated: 2018/10/31 13:48:07 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strends(const char *str, const char *end)
{
	size_t	i;

	if (!str && !end)
		return (1);
	if (!str || !end)
		return (0);
	if (!end[0])
		return (1);
	if (!str[0])
		return (0);
	i = (ft_strlen(str) - ft_strlen(end));
	while (str[i] == *end && str[i] && *end)
	{
		i++;
		end++;
	}
	if (str[i] == '\0' && *end == '\0')
		return (1);
	return (0);
}
