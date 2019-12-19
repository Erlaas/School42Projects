/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstarts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:05:38 by mdonchen          #+#    #+#             */
/*   Updated: 2018/10/31 13:47:37 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstarts(const char *str, const char *start)
{
	size_t	i;

	if (!str && !start)
		return (1);
	if (!str || !start)
		return (0);
	if (!str[0] && !start[0])
		return (1);
	if (!str[0] || !start[0])
		return (0);
	i = 0;
	while (str[i] == start[i] && str[i] && start[i])
		i++;
	if (start[i] == '\0')
		return (1);
	return (0);
}
