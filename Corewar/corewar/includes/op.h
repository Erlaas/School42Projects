/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 12:10:05 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/30 19:14:24 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include <errno.h>
# include <stdio.h>

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define FT_UINTMAX				0xffffffff
# define FT_INT_MAX				((int)(FT_UINTMAX >> 1))

# define ERR_OOM "ERROR: Malloc returned NULL"
# define ERR_COR_FILE "ERROR(champion): Unable to open .cor file"
# define ERR_MAGIC "ERROR(champion): Wrong magic number"
# define ERR_READ "ERROR(champion): Unable to read file"
# define ERR_INVALID_COR "ERROR(champion): Invalid .cor file"
# define ERR_NO_NULL "ERROR(champion): Missing NULL bytes"
# define ERR_INVALID_SIZE "ERROR(champion): Invalid champion size"

# define FT_ABS(X) (((X) < 0) ? (-(X)) : (X))
# define MEM_MOD(x) ((x) % MEM_SIZE)
# define FIRST_TYPE(x) ((x) >> 6)
# define SECOND_TYPE(x) (((x) >> 4) & 3)
# define THIRD_TYPE(x) (((x) >> 2) & 3)

typedef	struct		s_champion{
	int					fd;
	int					id;
	int					size;
	int					pc;
	int					pc_count;
	unsigned			was_alive;
	unsigned			lives;
	unsigned			prev_lives;
	char				*name;
	char				*comment;
	char				*code;
	struct s_champion	*next;
}					t_champion;

typedef struct		s_pc{
	unsigned		pc;
	unsigned		jump;
	unsigned		lives;
	unsigned char	types[3];
	unsigned char	op;
	unsigned		carry:1;
	int				cycle_alive;
	int				cycles_exec;
	int				id;
	int				r[REG_NUMBER];
	t_champion		*ch;
	struct s_pc		*next;
}					t_pc;

typedef struct		s_vm{
	unsigned char	map[MEM_SIZE];
	t_champion		*champs[MAX_PLAYERS];
	t_pc			*pc_lst;
	unsigned		players;
	unsigned		pcs;
	int				cycles;
	int				cycles_dup;
	unsigned		lives_n;
	unsigned		checks;
	int				dump;
	int				v;
	int				aff;
	t_champion		*winner;
	int				cycle_to_die;
}					t_vm;

typedef struct		s_op{
	char			*op_name;
	unsigned char	op;
	unsigned char	argc;
	unsigned		read_argv:1;
	unsigned		carry:1;
	unsigned char	argv[3];
	unsigned		dir_size;
	unsigned		cycles;
	void			(*function)(t_vm *vm, t_pc *pc);
}					t_op;

void				time_to_exec(t_vm *vm, t_pc *pc);
void				read_aff(int *argc, char ***argv, t_vm *vm);
void				insert_int_map(unsigned char *map, int kms, int val,\
		int size);
int					read_int(const unsigned char *map, int kms, int size);
t_pc				*cp_pc(t_pc *pc, int kms);
int					read_value(t_vm *vm, t_pc *pc, char i, int flag);
void				cycle_to_die_exec(t_vm *vm);
void				move_pc(t_pc *pc);
int					calc_jump(t_pc *pc, t_op *op);
void				exec_check(t_vm *vm);
void				printhex(int num, int size);
int					args_valid(t_pc *pc, t_vm *vm, t_op *op);
t_pc				*new_pc(t_champion *owner, unsigned int pc);
void				add_pc(t_pc **pc_lst, t_pc *pc);
void				create_pc(t_vm *vm);
void				cor_err(char *str);
void				print_map(unsigned char *map);
void				print_usage(void);
int					is_cor(const char *file);
int					ft_isnum(const char *str);
t_champion			*read_champion_file(char *file, int id);
t_vm				*read_args(int argc, char **argv);
t_champion			*is_champion(t_champion *ch, int n);
void				add_champion(t_champion **champs, t_champion *new);
void				update_ch_id(t_champion *ch);
int					mem_mod(int pc);
char				read_byte(t_vm *vm, int pc, int step);
void				verbal_pc_move(unsigned char *map, t_pc *pc);
void				op_live(t_vm *vm, t_pc *pc);
void				op_ld(t_vm *vm, t_pc *pc);
void				op_st(t_vm *vm, t_pc *pc);
void				op_add(t_vm *vm, t_pc *pc);
void				op_sub(t_vm *vm, t_pc *pc);
void				op_and(t_vm *vm, t_pc *pc);
void				op_or(t_vm *vm, t_pc *pc);
void				op_xor(t_vm *vm, t_pc *pc);
void				op_zjmp(t_vm *vm, t_pc *pc);
void				op_ldi(t_vm *vm, t_pc *pc);
void				op_sti(t_vm *vm, t_pc *pc);
void				op_fork(t_vm *vm, t_pc *pc);
void				op_lld(t_vm *vm, t_pc *pc);
void				op_lldi(t_vm *vm, t_pc *pc);
void				op_lfork(t_vm *vm, t_pc *pc);
void				op_aff(t_vm *vm, t_pc *pc);

static t_op		g_op_tab[16] = {
	{
		.op_name = "live",
		.op = 1,
		.argc = 1,
		.read_argv = 0,
		.carry = 0,
		.argv = {T_DIR, 0, 0},
		.dir_size = 4,
		.cycles = 10,
		.function = &op_live
	},
	{
		.op_name = "ld",
		.op = 2,
		.argc = 2,
		.read_argv = 1,
		.carry = 1,
		.argv = {T_DIR | T_IND, T_REG, 0},
		.dir_size = 4,
		.cycles = 5,
		.function = &op_ld
	},
	{
		.op_name = "st",
		.op = 3,
		.argc = 2,
		.read_argv = 1,
		.carry = 0,
		.argv = {T_REG, T_REG | T_IND, 0},
		.dir_size = 4,
		.cycles = 5,
		.function = &op_st
	},
	{
		.op_name = "add",
		.op = 4,
		.argc = 3,
		.read_argv = 1,
		.carry = 1,
		.argv = {T_REG, T_REG, T_REG},
		.dir_size = 4,
		.cycles = 10,
		.function = &op_add
	},
	{
		.op_name = "sub",
		.op = 5,
		.argc = 3,
		.read_argv = 1,
		.carry = 1,
		.argv = {T_REG, T_REG, T_REG},
		.dir_size = 4,
		.cycles = 10,
		.function = &op_sub
	},
	{
		.op_name = "and",
		.op = 6,
		.argc = 3,
		.read_argv = 1,
		.carry = 1,
		.argv = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
		.cycles = 6,
		.function = &op_and
	},
	{
		.op_name = "or",
		.op = 7,
		.argc = 3,
		.read_argv = 1,
		.carry = 1,
		.argv = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
		.cycles = 6,
		.function = &op_or
	},
	{
		.op_name = "xor",
		.op = 8,
		.argc = 3,
		.read_argv = 1,
		.carry = 1,
		.argv = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
		.cycles = 6,
		.function = &op_xor
	},
	{
		.op_name = "zjmp",
		.op = 9,
		.argc = 1,
		.read_argv = 0,
		.carry = 0,
		.argv = {T_DIR, 0, 0},
		.dir_size = 2,
		.cycles = 20,
		.function = &op_zjmp
	},
	{
		.op_name = "ldi",
		.op = 10,
		.argc = 3,
		.read_argv = 1,
		.carry = 0,
		.argv = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.dir_size = 2,
		.cycles = 25,
		.function = &op_ldi
	},
	{
		.op_name = "sti",
		.op = 11,
		.argc = 3,
		.read_argv = 1,
		.carry = 0,
		.argv = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.dir_size = 2,
		.cycles = 25,
		.function = &op_sti
	},
	{
		.op_name = "fork",
		.op = 12,
		.argc = 1,
		.read_argv = 0,
		.carry = 0,
		.argv = {T_DIR, 0, 0},
		.dir_size = 2,
		.cycles = 800,
		.function = &op_fork
	},
	{
		.op_name = "lld",
		.op = 13,
		.argc = 2,
		.read_argv = 1,
		.carry = 1,
		.argv = {T_DIR | T_IND, T_REG, 0},
		.dir_size = 4,
		.cycles = 10,
		.function = &op_lld
	},
	{
		.op_name = "lldi",
		.op = 14,
		.argc = 3,
		.read_argv = 1,
		.carry = 1,
		.argv = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.dir_size = 2,
		.cycles = 50,
		.function = &op_lldi
	},
	{
		.op_name = "lfork",
		.op = 15,
		.argc = 1,
		.read_argv = 0,
		.carry = 0,
		.argv = {T_DIR, 0, 0},
		.dir_size = 2,
		.cycles = 1000,
		.function = &op_lfork
	},
	{
		.op_name = "aff",
		.op = 16,
		.argc = 1,
		.read_argv = 1,
		.carry = 0,
		.argv = {T_REG, 0, 0},
		.dir_size = 4,
		.cycles = 2,
		.function = &op_aff
	}
};

#endif
