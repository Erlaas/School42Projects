/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:36:06 by mdonchen          #+#    #+#             */
/*   Updated: 2019/04/24 14:58:59 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdlib.h>
#include <unistd.h>

t_fil	let_leaks_out(t_fil fil)
{
	unsigned int i;

	i = 0;
	while (i < fil.y)
	{
		free(fil.mtx[i]);
		free(fil.map[i]);
		++i;
	}
	free(fil.map);
	free(fil.mtx);
	i = 0;
	while (i < fil.py)
		free(fil.pic[i++]);
	free(fil.pic);
	return (fil);
}

t_fil	filerr(t_fil fil)
{
	fil.err = 1;
	return (fil);
}

void	ft_putunbr(unsigned int n)
{
	if (n > 9)
		ft_putunbr(n / 10);
	n = n % 10 + '0';
	write(1, &n, 1);
}

void	print_coordinates(unsigned int x, unsigned int y)
{
	ft_putunbr(x);
	write(1, " ", 1);
	ft_putunbr(y);
	write(1, "\n", 1);
}

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
