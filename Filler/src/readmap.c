/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:57:25 by mdonchen          #+#    #+#             */
/*   Updated: 2019/04/30 12:39:15 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdlib.h>
#include <unistd.h>

int				**fil_mtx(unsigned int x, unsigned int y)
{
	int				**mtx;
	unsigned int	i;

	if (!(mtx = (int**)malloc(sizeof(int*) * (y + 1))))
		return (NULL);
	i = 0;
	while (i < y)
	{
		if (!(mtx[i] = (int*)malloc(sizeof(int) * (x + 1))))
			return (NULL);
		++i;
	}
	return (mtx);
}

char			**read_piece(unsigned int y)
{
	char				**pic;
	unsigned int		i;

	i = 0;
	if (!(pic = (char**)malloc(sizeof(char*) * y)))
		return (NULL);
	while (i < y)
	{
		if ((pic[i] = gnl_filler()) == NULL)
			return (NULL);
		i++;
	}
	return (pic);
}

unsigned int	find_num(t_fil fil, unsigned int i, unsigned int j)
{
	unsigned int	x;
	unsigned int	y;
	int				num;
	int				sum;

	x = 0;
	num = -1;
	while (x < fil.y)
	{
		y = 0;
		while (y < fil.x)
		{
			if (fil.map[x][y] == ('X' - (fil.p * 9))
					|| fil.map[x][y] == ('x' - (fil.p * 9)))
				sum = ft_abs(x - i) + ft_abs(y - j);
			if (num == -1 || num > sum)
				num = sum;
			++y;
		}
		++x;
	}
	return (num);
}

t_fil			algo_fil(t_fil fil)
{
	unsigned int	i;
	unsigned int	j;
	const char		u = 'O' + (fil.p * 9);
	const char		o = 'X' - (fil.p * 9);

	i = 0;
	while (i < fil.y)
	{
		j = 0;
		while (j < fil.x)
		{
			if ((fil.map[i][j] != o || fil.map[i][j] != o + 32)
					&& (fil.map[i][j] != u || fil.map[i][j] != u + 32))
				fil.mtx[i][j] = find_num(fil, i, j);
			j++;
		}
		i++;
	}
	fil = algo_fil2(fil);
	print_coordinates(fil.posx, fil.posy);
	let_leaks_out(fil);
	return (fil);
}

t_fil			read_until_err(t_fil fil)
{
	char				*gnl;
	unsigned int		i;

	fil = ft_size_of_grid(fil);
	if (!(fil.map = (char**)malloc(sizeof(char*) * (fil.y + 1))))
		return (fil = filerr(fil));
	free(gnl_filler());
	i = 0;
	while (i < fil.y)
	{
		if (!(gnl = (gnl_filler())))
			return (fil = filerr(fil));
		fil.map[i] = ft_strdup(gnl + 4);
		free(gnl);
		++i;
	}
	fil = ft_size_of_piece(fil);
	if (fil.px == 0 || fil.py == 0 || !(fil.pic = read_piece(fil.py))
			|| !(fil.mtx = fil_mtx(fil.x, fil.y)))
		return (fil = filerr(fil));
	fil = algo_fil(fil);
	return (fil);
}
