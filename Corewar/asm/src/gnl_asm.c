/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_asm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:37:39 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/18 17:01:57 by vkhomenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <unistd.h>

static char	*ft_strchrsafe(const char *txt, int num)
{
	return (!txt ? NULL : ft_strchr(txt, num));
}

static int	gnl_helper(char **txt, char **line)
{
	char	*buff;
	char	*item;

	item = (ft_strchrsafe(*txt, '\n')) + 1;
	if (!(*line = ft_strsub(*txt, 0, item - *txt)))
		return (-1);
	if (!ft_strlen(item))
	{
		free(*txt);
		*txt = NULL;
		return (1);
	}
	buff = ft_strdup(item);
	free(*txt);
	*txt = buff;
	return ((buff) ? 1 : -1);
}

int			gnl_asm(const int fd, char **line)
{
	static char		*txt = NULL;
	char			buff[BUFF_SIZE + 1];
	ssize_t			len;
	char			*tms;

	if (fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
	while (!ft_strchrsafe(txt, '\n'))
	{
		if (!(len = read(fd, buff, BUFF_SIZE)))
		{
			if (!(*line = txt))
				return (0);
			txt = NULL;
			return (1);
		}
		buff[len] = '\0';
		tms = txt;
		txt = ft_strjoin(txt, buff);
		free(tms);
		if (!txt)
			return (-1);
	}
	return (gnl_helper(&txt, line));
}
