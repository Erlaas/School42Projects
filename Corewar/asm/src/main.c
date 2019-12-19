/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:37:46 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/17 15:04:08 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_s(const char *file)
{
	const int slen = ft_strlen(file);

	if (file && slen >= 3)
		return (!ft_strcmp(file + (slen - 2), ".s"));
	return (0);
}

char	*change_filename_to_cor(char *str)
{
	char	*new;

	new = ft_strsub(str, 0, ft_strlen(str) - 2);
	if (!new)
		asm_err(ERR_OOM);
	if (!(str = ft_strjoin(new, ".cor")))
		asm_err(ERR_OOM);
	ft_strdel(&new);
	return (str);
}

int		main(int argc, char **argv)
{
	t_asm	*asb;
	int		fd;
	char	*new;

	if (argc != 2 || !is_s(*(argv + 1)))
		usage(*argv);
	errno = 0;
	if ((fd = open(*(argv + 1), O_RDONLY)) < 0)
		asm_err(ERR_OPEN);
	if (!(asb = (t_asm*)ft_memalloc(sizeof(t_asm))))
		asm_err(ERR_OOM);
	read_file(asb, fd);
	close(fd);
	new = change_filename_to_cor(*(argv + 1));
	if ((fd = open(new, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		asm_err(ERR_CREATE);
	write_bytes_to_file(fd, asb);
	ft_putstr("Writing output program to ");
	ft_putendl(new);
	return (0);
}
