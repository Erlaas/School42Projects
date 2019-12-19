/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:29:30 by mdonchen          #+#    #+#             */
/*   Updated: 2019/07/26 13:59:17 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

int				main(void)
{
	t_lem		lem;
	t_lst_paths	*path;

	lem = read_validate();
	path = lem_paths(&lem);
	if (!path)
		lem_err("ERROR: can't find solutions\n");
	send_ants(path, &lem);
	return (0);
}
