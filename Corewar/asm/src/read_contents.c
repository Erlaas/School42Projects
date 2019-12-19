/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_contents.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:38:00 by mdonchen          #+#    #+#             */
/*   Updated: 2019/11/15 12:42:56 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int						ft_isdelim(int c)
{
	return (c == '\0' || c == '\n' || c == '.' || c == '\"' || c == DIRECT_CHAR
	|| c == SEPARATOR_CHAR || c == COMMENT_CHAR || ft_isspace(c));
}

static int				ft_isreg(const char *str)
{
	const size_t	slen = ft_strlen(str);
	const int		flag = (slen == 2 || slen == 3);
	int				i;
	int				j;

	if (flag && str[0] == 'r')
	{
		i = 1;
		while (ft_isdigit(str[i]))
			++i;
		if (str[i] == '\0' && i > 1)
			return (1);
	}
	return (0);
}

int						ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\f' || c == '\v' || c == '\r');
}

void					read_str(t_asm *asb, char **gnl, unsigned i, \
t_content *content)
{
	ssize_t	siz;
	char	*str;
	char	*end;

	content->c = i;
	siz = 1;
	while (!(end = ft_strchr(&((*gnl)[i + 1]), '\"')) &&
		(siz = gnl_asm(asb->fd, &str)) > 0)
		*gnl = asm_strjoin(gnl, &str);
	if (siz == -1)
		asm_err(ERR_FILE);
	count_new_lines(asb, *gnl);
	if (!siz)
		asm_lexical_err(asb);
	if (!(content->content = ft_strsub(*gnl, i, end + 1 - &((*gnl)[i]))))
		asm_err(ERR_OOM);
	if (end - asb->c != *gnl)
	{
		update_gnl(gnl, end - asb->c);
	}
	++asb->c;
	add_content(&asb->contents, content);
}

void					read_symbols(t_asm *asb, char *gnl, unsigned i, \
t_content *content)
{
	unsigned	c;

	content->c = i;
	c = asb->c;
	while (gnl[asb->c] && ft_strchr(LABEL_CHARS, gnl[asb->c]))
		asb->c++;
	if ((asb->c - c) && gnl[asb->c] == LABEL_CHAR)
	{
		asb->c++;
		if (!(content->content = ft_strsub(gnl, i, asb->c - i)))
			asm_err(ERR_OOM);
		content->type = LBL;
	}
	else if ((asb->c - c) && ft_isdelim(gnl[asb->c]))
	{
		if (!(content->content = ft_strsub(gnl, i, asb->c - i)))
			asm_err(ERR_OOM);
		if (content->type == INDIR)
			content->type = (ft_isreg(content->content)) ? REG : OP;
	}
	else
		asm_lexical_err(asb);
	add_content(&asb->contents, content);
}
