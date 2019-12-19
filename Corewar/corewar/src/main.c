/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 12:08:36 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/27 16:33:36 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	create_map(t_vm *vm)
{
	const int		jump = MEM_SIZE / vm->players;
	unsigned int	pc;
	unsigned int	i;

	pc = 0;
	i = 1;
	while (i <= vm->players)
	{
		ft_memcpy(&(vm->map[pc]), vm->champs[i - 1]->code,
		(size_t)(vm->champs[i - 1]->size));
		pc += jump;
		++i;
	}
}

static void	print_players(t_champion **ch, int players)
{
	int i;

	i = 1;
	ft_putstr("Introducing champions...\n");
	while (i <= players)
	{
		ft_putstr("* Player ");
		ft_putnbr(i);
		ft_putstr(", size ");
		ft_putnbr(ch[i - 1]->size);
		ft_putstr(" bytes, \"");
		ft_putstr(ch[i - 1]->name);
		ft_putstr("\" (\"");
		ft_putstr(ch[i - 1]->comment);
		ft_putstr("\") \n");
		++i;
	}
}

static void	play(t_vm *vm)
{
	while (vm->pcs)
	{
		if (vm->dump == (int)vm->cycles)
		{
			print_map(vm->map);
			exit(0);
		}
		exec_check(vm);
		if (vm->cycle_to_die == (int)vm->cycles_dup || vm->cycle_to_die <= 0)
			cycle_to_die_exec(vm);
	}
}

static void	print_winner(t_vm *vm)
{
	ft_putstr("Champion ");
	ft_putnbr(vm->winner->id);
	ft_putstr(", \"");
	ft_putstr(vm->winner->name);
	ft_putstr("\", has won !\n");
}

int			main(int argc, char **argv)
{
	t_vm *vm;

	if (argc < 2)
		print_usage();
	vm = read_args((argc - 1), argv);
	create_map(vm);
	create_pc(vm);
	print_players(vm->champs, vm->players);
	play(vm);
	print_winner(vm);
	return (0);
}
