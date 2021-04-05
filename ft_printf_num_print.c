/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:11:49 by jisokang          #+#    #+#             */
/*   Updated: 2021/04/03 19:11:33 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_len(char c, int len)
{
	int	i;

	i = 0;
	while (len-- > 0)
	{
		i = i + write(1, &c, 1);
	}
	return (i);
}

int	num_itoa(t_info *info, char *num_box, long long num)
{
	int	len;

	len = 0;
	if (num == 0)
		num_box[len++] = '0';
	else
	{
		while (num != 0)
		{
			num_box[len++] = (DIGITS[num % info->num_base]) | info->locass;
			num = num / info->num_base;
		}
	}
	return (len);
}

int	print_sign(t_info *info)
{
	int	printed;

	printed = 0;
	if (info->num_sign == -1)
		printed += write(1, "-", 1);
	if (info->address == ENABLE)
		printed += write(1, "0x", 2);
	return (printed);
}

int	print_num(t_info *info, long long num)
{
	int			len;
	int			tmp_pre;
	int			printed;
	long long	tmp_num;
	char		num_box[21];

	printed = 0;
	tmp_pre = info->precision;
	tmp_num = num;
	len = num_itoa(info, num_box, num);
	if (tmp_num == 0 && (info->precision == 0 || info->dot_only == ENABLE))
		len = 0;
	if (len > info->precision)
		info->precision = len;
	info->gap = info->width - info->precision;
	if (info->minus == DISABLE && info->gap > 0)
		if (!(info->zero == ENABLE && tmp_pre < 0) || info->dot_only == ENABLE)
			while (info->gap-- > 0)
				printed += write(1, " ", 1);
			//printed += ft_putchar_len(' ', info->gap);
	printed = print_sign(info);
	if (info->zero == ENABLE)
		while (info->gap-- > 0)
			printed += write(1, "0", 1);
	info->precision -= len;
	while (info->precision-- > 0)
		printed += write(1, "0", 1);
		//printed += ft_putchar_len('0', info->precision);
	while (len-- > 0)
		printed += write(1, &num_box[len], 1);
	while (info->gap-- > 0)
		printed += write(1, " ", 1);
	//printed += ft_putchar_len(' ', info->gap);
	return (printed);
}
