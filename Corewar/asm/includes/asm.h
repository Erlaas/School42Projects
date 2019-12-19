/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:43:13 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/15 12:47:20 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include "libft.h"
# include "op.h"

# define BUFF_SIZE 2048

# define ERR_OPEN "Error: can't open file"
# define ERR_FILE "Error: can't read file"
# define ERR_OOM "Error: Malloc returned NULL"
# define ERR_CREATE "Error: Can't create file"

typedef enum{
	COM,
	STR,
	LBL,
	OP,
	REG,
	DIRR,
	DIRR_LAB,
	INDIR,
	INDIR_LAB,
	SEP,
	NL,
	END
}	t_type;

typedef struct		s_mlabel{
	unsigned		line;
	unsigned		c;
	int				i;
	int				op_i;
	size_t			size;
	struct s_mlabel	*next;
}					t_mlabel;

typedef	struct		s_label{
	char			*name;
	int				op_i;
	t_mlabel		*mlabels;
	struct s_label	*next;
}					t_label;

typedef struct		s_content{
	char				*content;
	t_type				type;
	unsigned			line;
	unsigned			c;
	struct s_content	*next;
}					t_content;

typedef struct		s_asm{
	char		*name;
	char		*comment;
	char		*code;
	int			size;
	int			fd;
	int			i;
	int			op_i;
	unsigned	line;
	unsigned	c;
	t_content	*contents;
	t_label		*labels;
}					t_asm;

typedef struct		s_op{
	char			*op_name;
	unsigned char	op;
	unsigned char	argc;
	unsigned		read_argv:1;
	unsigned char	argv[3];
	unsigned		dir_size;
}					t_op;

void				op_err(t_content *content);
void				add_mlabel(t_mlabel **lst, t_mlabel *new);
t_label				*find_lab(t_label *lst, char *name);
void				usage(char *str);
void				asm_err(char *str);
int					gnl_asm(const int fd, char **gnl);
void				read_file(t_asm *asb, int fd);
t_content			*new_content(t_asm *asb, t_type type);
void				add_content(t_content **contents, t_content *new);
int					ft_isspace(int c);
void				read_symbols(t_asm *asb, char *gnl, unsigned i,\
		t_content *content);
void				read_str(t_asm *asb, char **gnl, unsigned i,\
		t_content *content);
void				asm_lexical_err(t_asm *asb);
int					ft_isdelim(int c);
char				*asm_strjoin(char **s1, char **s2);
void				count_new_lines(t_asm *asb, const char *gnl);
void				update_gnl(char **gnl, char *p);
void				content_err(t_content *content);
void				pc_info(t_asm *asb, t_content **content);
void				update_code_buff(t_asm *asb);
void				add_label(t_label **lst, t_label *new);
t_label				*new_label(char *name, int op_i);
t_op				*get_op(char *name);
char				read_arg(t_asm *asb, t_content **content, t_op *op, int i);
void				arg_type_err(t_op *op, int i, t_content *content);
t_mlabel			*new_mlabel(t_asm *asb, size_t siz);
void				num_to_bytecode(char *str, int pc, int val, size_t siz);
void				update_op_types(char *op_types, char type, int i);
void				read_code(t_asm *asb, t_content **content);
void				lab_err(t_label *lab);
void				mlabel_to_num(t_asm *asb);
void				write_bytes_to_file(int fd, t_asm *asb);

#endif
