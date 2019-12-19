/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:30:02 by mdonchen          #+#    #+#             */
/*   Updated: 2019/07/26 20:14:55 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

void	check_overflow(const char *str)
{
	long long	num;
	long long	neg;

	num = 0;
	neg = 1;
	while (*str != ' ')
		str++;
	str++;
	if (*str == '+' || (*str == '-' && (neg = -1)))
		str++;
	while (*str >= '0' && *str <= '9' && num <= 2147483647)
		num = (num * 10) + (*str++ - '0');
	if (((neg == 1) && (num > 2147483647)) || (num * neg < -2147483648))
		lem_err("ERROR: Coordinates x overflow\n");
	str++;
	num = 0;
	neg = 1;
	if (*str == '+' || (*str == '-' && (neg = -1)))
		str++;
	while (*str >= '0' && *str <= '9' && (num <= 2147483647))
		num = (num * 10) + (*str++ - '0');
	if (((neg == 1) && (num > 2147483647)) || (num * neg < -2147483648))
		lem_err("ERROR: Coordinates y overflow\n");
}

int		da_da_kostil(char *str)
{
	if (room_command(str))
		lem_err("ERROR: Can't handle two commands at the same time\n");
	return (1);
}

int		len_path(t_lst_nodes *node)
{
	int i;

	i = -1;
	while (node)
	{
		node = node->next;
		++i;
	}
	return (i);
}

void	double_start_protec(char *str, t_node *s, t_node *e)
{
	if (s)
		if (ft_strequ(str, "##start"))
			lem_err("ERROR: Map has two starts\n");
	if (e)
		if (ft_strequ(str, "##end"))
			lem_err("ERROR: Map has two ends\n");
}

void	ft_putstrdel(char **as)
{
	if (as != NULL && *as != NULL)
	{
		if (!write(1, *as, ft_strlen(*as)) || !write(1, "\n", 1))
			lem_err("ERROR: Lines can't be empty\n");
		free(*as);
		*as = NULL;
	}
}
