/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 15:35:22 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/30 18:47:28 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_usage(void)
{
	ft_putstr("Usage : ./corewar [-dump n][-n n][-aff][-v n] champion_name.co");
	ft_putstr("r\n\t-dump [n] : Dump memory after [n] cycles\n");
	ft_putstr("\t-n [n] : Set [n] to the next player\n");
	ft_putstr("\t-aff : To enable print outputs from \"aff\"\n");
	ft_putstr("\t-v [n] : Verbal levels\n");
	ft_putstr("\t\t1 Print lives\n");
	ft_putstr("\t\t2 Print cycles\n");
	ft_putstr("\t\t4 Print operations\n");
	ft_putstr("\t\t8 Print deaths\n");
	ft_putstr("\t\t16 Print PC movements\n");
	exit(0);
}

int		ft_isnum(const char *str)
{
	unsigned int	num;
	unsigned int	lim;
	int				i;
	int				s;

	num = 0;
	i = 0;
	lim = (unsigned int)(FT_INT_MAX / 10);
	s = (str[i] == '-') ? 1 : 0;
	if (str[i] == '+' || str[i] == '-')
		++i;
	while (ft_isdigit(str[i]))
	{
		if (num > lim || (num == lim && (str[i] - '0') > (7 + s)))
			return (0);
		num = num * 10 + (str[i] - '0');
		++i;
	}
	return (!str[i] && (i > 0));
}

int		is_cor(const char *file)
{
	const int	slen = ft_strlen(file);

	if (file && slen >= 4)
		return (!ft_strcmp(file + (slen - 4), ".cor"));
	return (0);
}

void	printhex(int num, int size)
{
	const char	str[] = "0123456789abcdef";
	char		print[size];
	int			i;

	i = 0;
	while (i < size)
	{
		print[i] = '0';
		++i;
	}
	--i;
	while (num > 0)
	{
		print[i] = str[num % 16];
		num /= 16;
		--i;
	}
	write(1, print, size);
}

void	print_map(unsigned char *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_putstr("0x");
		printhex(i, 4);
		ft_putstr(" : ");
		j = 0;
		while (j < 64)
		{
			printhex(map[i + j], 2);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i += 64;
	}
	ft_putchar('\n');
}
