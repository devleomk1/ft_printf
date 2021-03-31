/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:42:42 by jisokang          #+#    #+#             */
/*   Updated: 2021/03/30 20:18:49 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(t_info *info, va_list ap)
{
	char	array[21];
	char	*str;
	char	*temp;

	ft_bzero(array, 21);
	str = array;
	temp = str;
	if (info->minus == DISABLE)
	{
		while (--(info->width) > 0)
			*str++ = ' ';
	}
	*str++ = (unsigned char)va_arg(ap, int);
	while (--(info->width) > 0)
		*str++ = ' ';
	return (write(1, temp, str - temp));
}
