/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:36:46 by mdonchen          #+#    #+#             */
/*   Updated: 2018/10/25 11:07:56 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char		*s2;
	const unsigned char chr = (unsigned char)c;

	s2 = (unsigned char*)s;
	while (n--)
		*s2++ = chr;
	return (s);
}
