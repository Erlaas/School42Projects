/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:38:11 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/15 12:41:57 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		count_new_lines(t_asm *asb, const char *gnl)
{
	unsigned	i;

	i = ++(asb->c);
	while (gnl[i] && gnl[i] != '\"')
	{
		if (gnl[i] == '\n')
		{
			asb->c = 0;
			++asb->line;
		}
		else
			++asb->c;
		++i;
	}
}

char		*asm_strjoin(char **s1, char **s2)
{
	char	*ret;

	ret = ft_strjoin(*s1, *s2);
	if (!ret)
		asm_err(ERR_OOM);
	ft_strdel(s1);
	ft_strdel(s2);
	return (ret);
}

void		update_gnl(char **gnl, char *p)
{
	char	*new;

	new = ft_strdup(p);
	if (!new)
		asm_err(ERR_OOM);
	ft_strdel(gnl);
	*gnl = new;
}

void		num_to_bytecode(char *str, int pc, int val, size_t siz)
{
	char	i;

	i = 0;
	while (siz)
	{
		str[pc + siz - 1] = (unsigned char)((val >> i) & 0xFF);
		i += 8;
		--siz;
	}
}

void		write_bytes_to_file(int fd, t_asm *asb)
{
	const int		siz = PROG_NAME_LENGTH + COMMENT_LENGTH + asb->i + 16;
	int				i;
	char			*buf;

	i = 0;
	if (!(buf = ft_strnew((size_t)siz)))
		asm_err(ERR_OOM);
	num_to_bytecode(buf, i, COREWAR_EXEC_MAGIC, 4);
	i += 4;
	ft_memcpy(&buf[i], asb->name, ft_strlen(asb->name));
	i += PROG_NAME_LENGTH + 4;
	num_to_bytecode(buf, i, asb->i, 4);
	i += 4;
	ft_memcpy(&buf[i], asb->comment, ft_strlen(asb->comment));
	i += COMMENT_LENGTH + 4;
	ft_memcpy(&buf[i], asb->code, (size_t)asb->i);
	write(fd, buf, (size_t)siz);
	free(buf);
}
