/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:35:25 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/27 18:27:34 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	set_champs(t_vm *vm, t_champion *ch)
{
	unsigned int	id;

	update_ch_id(ch);
	id = 1;
	while (id <= vm->players)
	{
		if (!(vm->champs[id - 1] = is_champion(ch, id)))
			print_usage();
		++id;
	}
	vm->winner = vm->champs[vm->players - 1];
}

static void	read_dump(int *argc, char ***argv, t_vm *vm)
{
	if ((vm->dump > 0) || *argc < 2 || !ft_isnum(*(*argv + 1)))
		print_usage();
	vm->dump = ft_atoi(*(*argv + 1));
	if (vm->dump < 0)
		vm->dump = -1;
	(*argv) += 2;
	(*argc) -= 2;
}

static void	read_verbal(int *argc, char ***argv, t_vm *vm)
{
	if (*argc < 2 || !ft_isnum(*(*argv + 1)))
		print_usage();
	vm->v = ft_atoi(*(*argv + 1));
	(*argv) += 2;
	(*argc) -= 2;
}

static void	read_champion(int *argc, char ***argv, t_vm *vm, t_champion **ch)
{
	int n;

	if (*argc >= 3 && !ft_strcmp(**argv, "-n") && ft_isnum(*(*argv + 1)))
	{
		n = ft_atoi(*(*argv + 1));
		if (is_champion(*ch, n) || !is_cor(*(*argv + 2)))
			print_usage();
		add_champion(ch, read_champion_file(*(*argv + 2), n));
		(*argv) += 3;
		(*argc) -= 3;
	}
	else if (is_cor(**argv))
	{
		add_champion(ch, read_champion_file(**argv, 0));
		(*argv)++;
		(*argc)--;
	}
	else
		print_usage();
	vm->players++;
}

t_vm		*read_args(int argc, char **argv)
{
	t_vm		*vm;
	t_champion	*ch;

	if (!(vm = (t_vm*)ft_memalloc(sizeof(t_vm))))
		cor_err(ERR_OOM);
	ch = NULL;
	errno = 0;
	argv++;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->dump = -1;
	while (argc > 0)
	{
		if (!ft_strcmp(*argv, "-dump"))
			read_dump(&argc, &argv, vm);
		else if (!ft_strcmp(*argv, "-v"))
			read_verbal(&argc, &argv, vm);
		else if (!ft_strcmp(*argv, "-aff"))
			read_aff(&argc, &argv, vm);
		else if (!ft_strcmp(*argv, "-n") || is_cor(*argv))
			read_champion(&argc, &argv, vm, &ch);
		else
			print_usage();
	}
	set_champs(vm, ch);
	return (vm);
}
