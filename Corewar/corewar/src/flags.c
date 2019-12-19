/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:35:46 by mdonchen          #+#    #+#             */
/*   Updated: 2019/10/30 18:46:11 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static int	read_int_from_hex(int fd)
{
	ssize_t			i;
	unsigned char	buf[4];
	int				res;
	int				mask;
	unsigned int	s;

	i = read(fd, &buf, 4);
	if (i == -1)
		cor_err(ERR_READ);
	else if (i < 4)
		cor_err(ERR_INVALID_COR);
	s = (buf[0] & 0x80);
	res = 0;
	mask = 0;
	while (i)
	{
		res += ((s ? (buf[i - 1] ^ 0xFF) : (buf[i - 1])) << (mask++ * 8));
		--i;
	}
	if (s)
		res = ~(res);
	return (res);
}

static char	*read_str(int fd, size_t len)
{
	ssize_t	i;
	char	*buf;

	if (!(buf = ft_strnew(len)))
		cor_err(ERR_OOM);
	i = read(fd, buf, len);
	if (i == -1)
		cor_err(ERR_READ);
	else if (i < (ssize_t)len)
		cor_err(ERR_INVALID_COR);
	return (buf);
}

static char	*read_code(int fd, ssize_t len)
{
	char	*buf;
	char	c;
	ssize_t size;

	if (!(buf = malloc(len)))
		cor_err(ERR_OOM);
	size = read(fd, buf, len);
	if (size == -1)
		cor_err(ERR_READ);
	else if (read(fd, &c, 1) != 0 || size < len)
		cor_err(ERR_INVALID_COR);
	return (buf);
}

t_champion	*read_champion_file(char *file, int id)
{
	t_champion	*ch;
	int			fd;

	if (!(ch = (t_champion*)ft_memalloc(sizeof(t_champion))))
		cor_err(ERR_OOM);
	ch->id = id;
	if ((fd = open(file, O_RDONLY)) < 0)
		cor_err(ERR_COR_FILE);
	if (read_int_from_hex(fd) != COREWAR_EXEC_MAGIC)
		cor_err(ERR_MAGIC);
	ch->name = read_str(fd, PROG_NAME_LENGTH);
	if (read_int_from_hex(fd) != 0)
		cor_err(ERR_NO_NULL);
	ch->size = read_int_from_hex(fd);
	if (ch->size < 0 || ch->size > CHAMP_MAX_SIZE)
		cor_err(ERR_INVALID_SIZE);
	ch->comment = read_str(fd, COMMENT_LENGTH);
	if (read_int_from_hex(fd) != 0)
		cor_err(ERR_NO_NULL);
	ch->code = read_code(fd, (ssize_t)ch->size);
	return (ch);
}

void		read_aff(int *argc, char ***argv, t_vm *vm)
{
	vm->aff = 1;
	(*argv)++;
	(*argc)--;
}
