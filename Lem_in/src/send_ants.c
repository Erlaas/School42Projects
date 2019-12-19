/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:29:58 by mdonchen          #+#    #+#             */
/*   Updated: 2019/07/26 10:33:54 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ants.h"

unsigned int	paths_sum(t_lst_paths *head, t_lst_paths *paths)
{
	unsigned int	i;

	i = 0;
	while (head != paths)
	{
		i = i + (len_path(paths->path) - len_path(head->path));
		head = head->next;
	}
	return (i);
}

unsigned int	ants_ended(t_lst_ants **ants, t_lst_paths *paths,
		unsigned int ants_ended, t_lem *lem)
{
	t_lst_paths	*head;

	head = paths;
	while ((lem->ants - ants_ended) && paths)
	{
		if (head->path->node == lem->start &&
			head->path->next->node == lem->end)
			ants_ended = ants_add_end(ants, paths->path, ants_ended + 1);
		else
		{
			if ((lem->ants - ants_ended) > paths_sum(head, paths))
				ants_ended = ants_add_end(ants, paths->path, ants_ended + 1);
			paths = paths->next;
		}
	}
	paths = head;
	return (ants_ended);
}

void			del_ant(t_lst_ants **ants, t_lst_ants *ant)
{
	t_lst_ants *head;
	t_lst_ants *tmp;

	tmp = NULL;
	if (*ants != ant)
	{
		head = *ants;
		while (head->next)
		{
			if (head->next == ant)
			{
				tmp = head->next;
				head->next = head->next->next;
				free(tmp);
				break ;
			}
			head = head->next;
		}
	}
	else
	{
		tmp = *ants;
		*ants = (*ants)->next;
		free(tmp);
	}
}

void			del_enders(t_lst_ants **ants, t_lem *lem)
{
	t_lst_ants *head;

	head = *ants;
	while (head)
	{
		if (lem->end == head->pos->node)
			del_ant(ants, head);
		head = head->next;
	}
}

void			send_ants(t_lst_paths *paths, t_lem *lem)
{
	unsigned int	ants_end;
	t_lst_ants		*ants;

	write(1, "\n", 1);
	ants = NULL;
	ants_end = ants_ended(&ants, paths, 0, lem);
	while (ants)
	{
		print_ants(ants, lem);
		write(1, "\n", 1);
		del_enders(&ants, lem);
		ants_end = ants_ended(&ants, paths, ants_end, lem);
	}
}
