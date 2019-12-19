/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:29:55 by mdonchen          #+#    #+#             */
/*   Updated: 2019/07/26 20:20:44 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

void			validate_room(const char *str)
{
	if (!*str)
		lem_err("ERROR: Lines can't be empty\n");
	if (*str == 'L')
		lem_err("ERROR: Rooms name can't start with character 'L'\n");
	while (*str != ' ' && *str)
		if (*str++ == '-')
			lem_err("ERROR: Rooms name can't contain '-'\n");
	if (*str++ != ' ')
		lem_err("ERROR: No rooms coordinates\n");
	if (*str == '+' || *str == '-')
		str++;
	if (!(*str >= '0' && *str <= '9'))
		lem_err("ERROR: No rooms coordinates");
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str++ != ' ')
		lem_err("ERROR: No y coordinates for room\n");
	if (*str == '+' || *str == '-')
		str++;
	if (!(*str >= '0' && *str <= '9'))
		lem_err("ERROR: No y coordinates for room\n");
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str)
		lem_err("ERROR: Wrong rooms coordinates");
}

char			*get_room_name(const char *str)
{
	char	*r_str;
	size_t	i;

	i = 0;
	while (str[i] != ' ' && str[i])
		++i;
	if (!(r_str = ft_memalloc(sizeof(char) * (i + 1))))
		lem_err("ERROR: Malloc returned NULL\n");
	i = 0;
	while (str[i] != ' ' && str[i])
	{
		r_str[i] = str[i];
		++i;
	}
	if (!r_str[0])
		lem_err("ERROR: Missing Room name\n");
	return (r_str);
}

void			get_coordinates(const char *str, int *x, int *y)
{
	int	neg;

	neg = 1;
	check_overflow(str);
	while (*str != ' ')
		str++;
	str++;
	if (*str == '+' || (*str == '-' && (neg = -1)))
		str++;
	while (*str >= '0' && *str <= '9')
		*x = (*x * 10) + (*str++ - '0');
	str++;
	*x = *x * neg;
	neg = 1;
	if (*str == '+' || (*str == '-' && (neg = -1)))
		str++;
	while (*str >= '0' && *str <= '9')
		*y = (*y * 10) + (*str++ - '0');
	*y = *y * neg;
}

t_node			*get_room(char **str, t_lem *lem)
{
	t_node	*node;

	validate_room(*str);
	node = ft_memalloc(sizeof(t_node));
	node->name = get_room_name(*str);
	get_coordinates(*str, &node->xy[0], &node->xy[1]);
	add_end_node(&lem->nodes, node);
	return (node);
}

unsigned int	read_rooms(char **str, t_lem *lem)
{
	double_start_protec(*str, lem->start, lem->end);
	if (ft_strchr(*str, '-') && !ft_strchr(*str, ' '))
	{
		read_link(str, lem);
		ft_putstrdel(str);
		return (1);
	}
	else if (ft_strequ(*str, "##start"))
	{
		ft_putstrdel(str);
		while (gnl_stdin(str) > 0 && **str == '#' && da_da_kostil(*str))
			ft_putstrdel(str);
		lem->start = get_room(str, lem);
	}
	else if (ft_strequ(*str, "##end"))
	{
		ft_putstrdel(str);
		while (gnl_stdin(str) > 0 && **str == '#' && da_da_kostil(*str))
			ft_putstrdel(str);
		lem->end = get_room(str, lem);
	}
	else
		get_room(str, lem);
	ft_putstrdel(str);
	return (0);
}
