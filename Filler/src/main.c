/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 16:29:36 by mdonchen          #+#    #+#             */
/*   Updated: 2019/04/30 12:43:09 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <unistd.h>
#include <stdlib.h>

unsigned int	fig_map(t_fil fil, unsigned int i, unsigned int j)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	sp;
	const char		u = 'O' + (fil.p * 9);
	const char		o = 'X' - (fil.p * 9);

	x = 0;
	sp = 0;
	while (x < fil.py)
	{
		y = 0;
		while (y < fil.px)
		{
			if (fil.pic[x][y] == '*' && (fil.map[i + x][j + y] == u
						|| fil.map[i + x][j + y] == u + 32))
				sp++;
			else if (fil.pic[x][y] == '*' && (fil.map[i + x][j + y] == o
						|| fil.map[i + x][j + y] == o + 32))
				return (0);
			++y;
		}
		++x;
	}
	return (sp);
}

t_fil			ft_multi_fil(t_fil fil, unsigned int i, unsigned int j)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	sum;

	x = 0;
	sum = 0;
	while (x < fil.py)
	{
		y = 0;
		while (y < fil.px)
		{
			if (fil.pic[x][y] == '*')
				sum += fil.mtx[i + x][j + y];
			++y;
		}
		++x;
	}
	if (fil.sum == 0 || fil.sum > sum)
	{
		fil.sum = sum;
		fil.posx = i;
		fil.posy = j;
	}
	return (fil);
}

t_fil			algo_fil2(t_fil fil)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	fil.posx = 0;
	fil.posy = 0;
	fil.sum = 0;
	while (i < fil.y)
	{
		j = 0;
		while (j < fil.x)
		{
			if (!(i + fil.py > fil.y || j + fil.px > fil.x)
					&& fig_map(fil, i, j) == 1)
				fil = ft_multi_fil(fil, i, j);
			++j;
		}
		i++;
	}
	return (fil);
}

int				main(void)
{
	t_fil fil;

	fil = ft_nplayer();
	if (fil.err == 1)
		write(1, "Bad player info\n", 16);
	while (!fil.err)
		fil = read_until_err(fil);
	return (0);
}
