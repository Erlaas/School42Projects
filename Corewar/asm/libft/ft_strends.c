/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strends.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdonchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:08:08 by mdonchen          #+#    #+#             */
/*   Updated: 2018/10/31 13:48:07 by mdonchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strends(const char *str, const char *end)
{
	return (!ft_strcmp(str + ft_strlen(str) - ft_strlen(end), end));
}
