/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:19:45 by jisokang          #+#    #+#             */
/*   Updated: 2021/03/26 14:35:18 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_char(char *format, va_list ap, t_info *info, char *str)
{
	if (info->minus != TRUE)
		while(--(info->width) > 0)
			*str++ = ' ';
	*str++ = (unsigned char)va_arg(ap, int);
	while (--(info->width) > 0)
		*str++ = ' ';
	format++;
	return (1);
}
