/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:24:19 by jisokang          #+#    #+#             */
/*   Updated: 2021/04/03 15:04:21 by jisokang         ###   ########.fr       */
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

int	print_u(t_info *info, va_list ap)
{
	int			printed;
	long long	num;

	info->num_base = 10;
	num = va_arg(ap, unsigned int);
	printed = print_num(info, num);
	return (printed);
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
int	print_p(t_info *info, va_list ap)
{
	int			printed;
	long long	num;
	info->special = ENABLE;
	info->locass = SMALL;
	info->width -= 2;
	info->num_base = 16;
	num = (unsigned long)va_arg(ap, void *);

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
	long long	ycha_num =0;

	str = (char[1024]){};
	temp = str;
	len = 0;
	tmp_pre = info->precision;
	ycha_num = num;
	/* get_number --------------------------------------------------------------------------*/
	if (num == 0)
		tmp_num[len++] = '0';
	else
		while (num != 0)
		{
			tmp_num[len++] = (DIGITS[num % info->num_base]) | info->locass;	//bit OR 연산
			num = num / info->num_base;
		}
	if (ycha_num == 0 && (info->precision == 0 || info->dot_only == ENABLE))
		len = 0;
	if (len > info->precision)
		info->precision = len;
	info->gap = info->width - info->precision;
	temp = str;
	if (info->minus == DISABLE && info->gap > 0)
		if(!(info->zero == ENABLE && tmp_pre < 0) || info->dot_only == ENABLE)
			while (info->gap-- > 0)
				*str++ = ' ';
	/* number sign -------------------------------------------------------------------------*/
	if (info->num_sign == -1)
		*str++ = '-';
	/*--------------------------------------------------------------------------------------*/
	if (info->special == ENABLE)
	{
		*str++ = '0';
		*str++ = 'x';
	}
	if (info->zero == ENABLE)
		while (info->gap-- > 0)
			*str++ = '0';
	info->precision -= len;
	while ((info->precision)--)
			*str++ = '0';
	/* NUM 출력 -----------------------------------------------------------------------------*/
	// len = 0이면, 무조건 출력하지 않는다.
	while (len-- > 0)
		*str++ = tmp_num[len];
	/*--------------------------------------------------------------------------------------*/
	while ((info->gap)-- > 0)		//minus 일때 뒤쪽 width 남은거 출력
		*str++ = ' ';
	return (write(1, temp, str - temp));
}

int	ft_print_num(t_info *info, va_list ap, const char type)
{
	int			printed;

	printed = 0;
	if (type == 'd' || type == 'i')
		printed = print_di(info, ap);
	else if (type == 'u')
		printed = print_u(info, ap);
	else if (type == 'x' || type == 'X')
		printed = print_xX(info, ap, type);
	else if (type == 'p')
		printed = print_p(info, ap);
	else
		printed = 0;
	return (printed);
}
