/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:29:46 by mdonchen          #+#    #+#             */
/*   Updated: 2019/07/26 20:36:58 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

static unsigned int	get_ants(char **str)
{
	unsigned long	ants;
	char			*s;

	s = *str;
	ants = 0;
	while (*s >= '0' && *s <= '9' && ((ants * 10) + (*s - '0') <= 0xffffffff))
		ants = (ants * 10) + (*s++ - '0');
	if (*s)
	{
		if (*s >= '0' && *s <= '9' && ((ants * 10) + (*s - '0') > 0xffffffff))
			lem_err("ERROR: Ants number overflow\n");
		else
			lem_err("ERROR: Ants can be only 0-9 digits\n");
	}
	else if (!ants)
		lem_err("ERROR: Ants can't be 0\n");
	ft_putstrdel(str);
	return ((unsigned int)ants);
}

int					room_command(char *str)
{
	if (*(str + 1) == '#')
		return (ft_strequ(str, "##end") || ft_strequ(str, "##start"));
	return (0);
}

t_lem				read_validate(void)
{
	char			*str;
	t_lem			lem;
	unsigned int	links;

	links = 0;
	ft_memset(&lem, 0, sizeof(t_lem));
	while (gnl_stdin(&str) > 0)
	{
		if (*str == '#' && !room_command(str))
			ft_putstrdel(&str);
		else if (!lem.ants)
			lem.ants = get_ants(&str);
		else if (!links)
			links = read_rooms(&str, &lem);
		else
			read_link(&str, &lem);
	}
	if (str)
		lem_err("ERROR: Map dont have new line at the end\n");
	if (!links)
		lem_err("ERROR: Map has no links\n");
	return (lem);
}
