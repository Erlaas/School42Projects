/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:11:57 by mdonchen          #+#    #+#             */
/*   Updated: 2019/07/26 18:56:57 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANTS_H
# define ANTS_H
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct		s_node{
	char				*name;
	int					xy[2];
	unsigned int		fl:1;
	unsigned int		q:1;
	struct s_node		*prev;
	struct s_lst_nodes	*links;
}					t_node;

typedef struct		s_lst_nodes{
	t_node				*node;
	struct s_lst_nodes	*next;
}					t_lst_nodes;

typedef struct		s_lst_paths{
	t_lst_nodes			*path;
	struct s_lst_paths	*next;
}					t_lst_paths;

typedef struct		s_lem{
	unsigned int	ants;
	t_lst_nodes		*nodes;
	t_node			*start;
	t_node			*end;
}					t_lem;

typedef struct		s_lst_ants{
	t_lst_nodes			*pos;
	unsigned int		id;
	struct s_lst_ants	*next;
}					t_lst_ants;

/*
** ants.c
*/
void				print_ants(t_lst_ants *ants, t_lem *lem);
unsigned int		ants_add_end(t_lst_ants **a,
		t_lst_nodes *p, unsigned int d);
/*
** send_ants.c
*/
void				send_ants(t_lst_paths *paths, t_lem *lem);
/*
** b_f_s.c
*/
t_lst_nodes			*b_f_s(t_lem *lem);
/*
** link.c
*/
int					link_unique(t_lst_nodes *links, t_node *node);
void				read_link(char **str, t_lem *lem);
/*
** paths.c
*/
void				add_end_path(t_lst_paths **lst, t_lst_nodes *path);
t_lst_paths			*lem_paths(t_lem *lem);
/*
** utils.c
*/
void				check_overflow(const char *str);
int					da_da_kostil(char *str);
int					len_path(t_lst_nodes *node);
void				double_start_protec(char *str, t_node *s, t_node *e);
void				ft_putstrdel(char **str);
/*
** node.c
*/
void				add_end_node(t_lst_nodes **lst, t_node *node);
void				del_node(t_lst_nodes **lst, t_node *node);
unsigned int		read_rooms(char **str, t_lem *lem);
/*
** error.c
*/

void				lem_err(const char *str);
/*
** read_validate.c
*/
int					room_command(char *str);
t_lem				read_validate(void);

/*
** gnl.c
*/
int					gnl_stdin(char **str);
#endif
