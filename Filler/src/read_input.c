/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:27:01 by mdonchen          #+#    #+#             */
/*   Updated: 2019/04/24 10:54:19 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <unistd.h>
#include <stdlib.h>

char	*charjoin(char *str, char c)
{
	unsigned int	slen;
	char			*newstr;

	slen = 0;
	while (str[slen])
		slen++;
	if (!(newstr = (char*)malloc(sizeof(char) * (slen + 2))))
		return (NULL);
	slen = 0;
	while (str[slen])
	{
		newstr[slen] = str[slen];
		++slen;
	}
	newstr[slen] = c;
	newstr[slen + 1] = '\0';
	return (newstr);
}

char	*gnl_filler(void)
{
	char	*str;
	char	c;
	char	*lks;

	if (!(str = (char*)malloc(sizeof(char))))
		return (NULL);
	str[0] = '\0';
	while ((read(0, &c, 1) && c != '\n'))
	{
		lks = str;
		if (!(str = charjoin(str, c)))
			return (NULL);
		free(lks);
	}
	return (str);
}

t_fil	ft_nplayer(void)
{
	const char	exec[11] = "$$$ exec p";
	char		*str;
	t_fil		fil;
	int			i;

	i = 0;
	fil.err = 0;
	str = gnl_filler();
	while (str[i] == exec[i])
		++i;
	if (exec[i] != '\0')
		fil.err = 1;
	else if (str[i] == '1')
		fil.p = 0;
	else if (str[i] == '2')
		fil.p = 1;
	else
		fil.err = 1;
	free(str);
	return (fil);
}

t_fil	ft_size_of_piece(t_fil fil)
{
	const char	exec[7] = "Piece ";
	char		*str;
	int			i;

	i = 0;
	fil.px = 0;
	fil.py = 0;
	str = gnl_filler();
	while (str[i] == exec[i])
		++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		fil.py *= 10;
		fil.py += str[i] - 48;
		++i;
	}
	++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		fil.px *= 10;
		fil.px += str[i] - 48;
		++i;
	}
	free(str);
	return (fil);
}

t_fil	ft_size_of_grid(t_fil fil)
{
	const char	exec[10] = "Plateau ";
	char		*str;
	int			i;

	i = 0;
	fil.x = 0;
	fil.y = 0;
	str = gnl_filler();
	while (str[i] == exec[i])
		++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		fil.y *= 10;
		fil.y += str[i] - 48;
		++i;
	}
	++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		fil.x *= 10;
		fil.x += str[i] - 48;
		++i;
	}
	free(str);
	return (fil);
}
