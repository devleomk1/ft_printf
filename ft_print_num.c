/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:24:19 by jisokang          #+#    #+#             */
/*   Updated: 2021/04/02 14:59:58 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_di(t_info *info, va_list ap)
{
	int			printed;
	long long	num;

	info->num_base = 10;
	num = va_arg(ap, int);
	if (num < 0)
	{
		info->num_sign = -1;
		num = -num;
		(info->width)--;
	}
	printed = print_num(info, num);
	return (printed);
}

int	print_u(void)
{
	return (0);
}

int	print_xX(t_info *info, va_list ap, char type)
{
	int			printed;
	long long	num;

	if (type == 'x')
		info->locass = SMALL;
	info->num_base = 16;
	num = va_arg(ap, unsigned int);
	printed = print_num(info, num);
	return (printed);
}

int	print_num(t_info *info, long long num)
{
	char		*str;
	char		*temp;
	char		tmp_num[21];
	int			len;
	int			tmp_pre;

	str = (char [21]){};
	temp = str;
	len = 0;
	tmp_pre = info->precision;

	if (num == 0)
		tmp_num[len++] = '0';
	else
		while (num != 0)
		{
			tmp_num[len++] = (DIGITS[num % info->num_base]) | info->locass;	//bit OR 연산
			num = num / info->num_base;
		}
	if (tmp_num[0] == '0' && (info->precision == 0 || info->dot_only == ENABLE))
		len = 0;
	if (len > info->precision)
		info->precision = len;
	info->gap = info->width - info->precision;
	if (info->minus == DISABLE && info->width > get_max(tmp_pre, len))
	{
		if(info->zero == ENABLE && tmp_pre < 0){}
		else
			while (info->gap-- > 0)
				*str++ = ' ';
	}
	/* -- number sign -- */
	if (info->num_sign == -1)
		*str++ = '-';
	if (info->zero == ENABLE)
		while (info->gap-- > 0)
			*str++ = '0';
	info->precision -= len;
	while ((info->precision)--)
			*str++ = '0';
	/*-------- NUM 출력 --------*/
	while (len-- > 0)
		*str++ = tmp_num[len];
	while ((info->gap)-- > 0)		//minus 일때 뒤쪽 width 남은거 출력
		*str++ = ' ';
	return (write(1, temp, str - temp));
}

int	ft_print_num(t_info *info, va_list ap, char type)
{
	int			printed;

	printed = 0;
	if (type == 'd' || type == 'i')
		printed = print_di(info, ap);
	else if (type == 'u')
		printed = print_u();
	else if (type == 'x' || type == 'X')
		printed = print_xX(info, ap, type);
	else
		printed = 0;
	return (printed);
}
