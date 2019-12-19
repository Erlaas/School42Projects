/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:34:30 by mdonchen          #+#    #+#             */
/*   Updated: 2018/10/29 15:18:15 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa(int n)
{
	char	*itoa;
	int		nsiz;
	char	*i_min;

	nsiz = ft_sizeofint(n);
	i_min = "-2147483648";
	if (!(itoa = (char *)malloc(sizeof(char) * nsiz + 1)))
		return (NULL);
	if (n == -2147483648)
		return (ft_strcpy(itoa, i_min));
	if (n < 0)
	{
		itoa[0] = '-';
		n = -n;
	}
	itoa[nsiz--] = '\0';
	while (n >= 10)
	{
		itoa[nsiz--] = n % 10 + '0';
		n = n / 10;
	}
	itoa[nsiz] = n % 10 + '0';
	return (itoa);
}
