/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:37:49 by jisokang          #+#    #+#             */
/*   Updated: 2021/04/02 15:03:12 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 구조체 초기화 함수 */
void	init_struct(t_info *info)
{
	info->minus = DISABLE;
	info->zero = DISABLE;
	info->dot_only = DISABLE;
	info->width = -1;
	info->precision = -1;
	info->num_base = 10;
	info->num_sign = 0;
	info->gap = 0;
	info->locass = DISABLE;

}
int	get_max(int a, int b)
{
	if(a > b)
		return (a);
	else
		return (b);
}
int	get_min(int a, int b)
{
	if(a > b)
		return (b);
	else
		return (a);
}

/* atoi */
static int skip_atoi(const char **s)
{
	int	i;

	i = 0;
	while (ft_isdigit(**s))
		i = i * 10 + *((*s)++) - '0';
	return i;
}

/* get flag */
void	ft_parse_flag(const char **format, t_info *info)
{
	while (**format == '-' || **format == '0')
	{
		if (**format == '0')
			info->zero = ENABLE;
		else
		{
			if (info->zero == ENABLE)	//MINUS와 ZERO를 같이 쓰면
				info->zero = DISABLE;	//ZERO가 무시된다.
			info->minus = ENABLE;
		}
		(*format)++;
	}
}
/* atoi get width */
void	ft_parse_width(const char **format, t_info *info, va_list ap)
{
	if (ft_isdigit(**format) == TRUE)
		info->width = skip_atoi(format);
	else if (**format == '*')
	{
		(*format)++;
		info->width = va_arg(ap, int);
		if (info->width < 0)
		{
			info->width = -(info->width);	// *로 width값이 음수값으로 들어오면
			info->minus = ENABLE;			//'-' flag TRUE
			if(info->zero == ENABLE)
				info->zero = DISABLE;
		}
	}
}
/* atoi get precision here */
void	ft_parse_precision(const char **format, t_info *info, va_list ap)
{
	if (**format == '.')
	{
		(*format)++;
		if (ft_isdigit(**format))
			info->precision = skip_atoi(format);
		else if (**format == '*')
		{
			(*format)++;
			info->precision = va_arg(ap, int);
		}
		else
			info->dot_only = ENABLE;
		if (info->precision < 0)
			info->precision = -1;
	}
}

/* 분석하는 함수 */
int	ft_parse_symbols(const char *format, va_list ap)
{
	t_info			*info;
	int				printed;

	printed = 0;
	info = malloc(sizeof(t_info) * 1);
	if(!info)
		return (ERROR);
	while(*format != 0)
	{
		init_struct(info);
		if (*format != '%')
		{
			printed += write(1, format, 1);
			format++;
		}
		if (*format == '%')
		{
			format++;
			/* get FLAG */
			ft_parse_flag(&format, info);
			/* get width & precision */
			ft_parse_width(&format, info, ap);
			ft_parse_precision(&format, info, ap);

			if (*format == 'c')
				printed += ft_print_char(info, ap);
			else if (*format == '%')
				printed += write(1, "%", 1);
			else if (*format == 's')
				printed += ft_print_string(info, ap);
			else if (ft_strchr("diuxX", *format))
				printed += ft_print_num(info, ap, *format);

			format++;
		}
	}
	free(info);
	return (printed);
}

int	ft_printf(const char *format, ...)
{
	va_list ap;
	int printed;

	va_start(ap, format);
	printed = ft_parse_symbols(format, ap);
	va_end(ap);
	return (printed);
}
