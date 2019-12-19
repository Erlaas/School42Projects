/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 16:30:30 by mdonchen          #+#    #+#             */
/*   Updated: 2019/04/24 15:04:13 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

typedef struct		s_fil{
	int				**mtx;
	char			**map;
	char			**pic;
	unsigned int	err: 1;
	unsigned int	p: 1;
	unsigned int	x;
	unsigned int	y;
	unsigned int	px;
	unsigned int	py;
	unsigned int	posx;
	unsigned int	posy;
	unsigned int	sum;
}					t_fil;

char				*gnl_filler(void);
t_fil				ft_nplayer(void);
t_fil				ft_size_of_grid(t_fil fil);
int					**ft_alloc_grid(unsigned int x, unsigned int y);
t_fil				read_until_err(t_fil fil);
t_fil				ft_size_of_piece(t_fil fil);
char				*ft_strdup(const char *str);
unsigned int		fig_map(t_fil fil, unsigned int i, unsigned int j);
t_fil				algo_fil2(t_fil fil);
void				print_coordinates(unsigned int x, unsigned int y);
t_fil				filerr(t_fil fil);
void				ft_putunbr(unsigned int n);
t_fil				let_leaks_out(t_fil fil);
int					ft_abs(int x);

#endif
