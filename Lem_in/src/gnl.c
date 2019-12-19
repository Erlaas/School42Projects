/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:21:29 by mdonchen          #+#    #+#             */
/*   Updated: 2019/07/26 20:22:03 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		gnl_stdin(char **str)
{
	int		ret;
	char	c;
	char	*lks;

	if (!str || !(*str = (char*)malloc(sizeof(char))))
		return (-1);
	*str[0] = '\0';
	while ((ret = read(0, &c, 1)) && c != '\n')
	{
		lks = *str;
		if (!(*str = charjoin(*str, c)))
			return (-1);
		free(lks);
	}
	if ((*str)[0] == '\0')
	{
		if (ret == 0)
			*str = NULL;
		free(*str);
	}
	return (ret);
}
