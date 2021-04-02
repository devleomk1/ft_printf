/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:37:49 by jisokang          #+#    #+#             */
/*   Updated: 2021/04/01 21:37:55 by jisokang         ###   ########.fr       */
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
	long long		num;
	char			*str;		//출력 할 문자열
	char			*temp;

	printed = 0;
	info = malloc(sizeof(t_info) * 1);
	if(!info)
		return (ERROR);
	while(*format != 0)
	{
		/* 이 칭구들을 각각 type별로 넣어주면 더 줄일 수 있어. */
		init_struct(info);
		str = (char [21]){};	//출력할 문자열의 MAX 길이는 20 + '\0'
		temp = str;
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

			/* get %c */
			if (*format == 'c')
				printed += ft_print_char(info, ap);
			/* get %% */
			else if (*format == '%')
				printed += write(1, "%", 1);
			else if (*format == 's')
				printed += ft_print_string(info, ap);
			else if(*format == 'x' || *format == 'X')
			{
				info->num_base = 16;
				num = va_arg(ap, unsigned int);
					/*---------- prototype cal : num에서 전부 동일하게 연산------------*/
				int	len = 0;
				char tmp_num[21];
				int tmp_pre = info->precision;
				int locass = DISABLE;

				if (*format == 'x')
					locass = SMALL;
				if (num == 0)
					tmp_num[len++] = '0';
				else
					while (num != 0)
					{
						tmp_num[len++] = (DIGITS[num % info->num_base]) | locass;
						num = num / info->num_base;
					}
				if (tmp_num[0] == '0' && (info->precision == 0 || info->dot_only == ENABLE))
					len = 0;
				if (len > info->precision)
					info->precision = len;
				info->gap = info->width - info->precision;
				if (info->minus == DISABLE && info->width > max(tmp_pre, len))
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
				printed += write(1, temp, str - temp);
			}
			else if(*format == 'd' || *format == 'i')
			{
				info->num_base = 10;
				num = va_arg(ap, int);
				if (num < 0)
				{
					info->num_sign = -1;
					num = -num;
					(info->width)--;
				}
				/*---------- prototype cal : num에서 전부 동일하게 연산------------*/
				int	len = 0;
				char tmp_num[21];
				int tmp_pre = info->precision;

				if (num == 0)
					tmp_num[len++] = '0';
				else
					while (num != 0)
					{
						tmp_num[len++] = DIGITS[num % info->num_base];
						num = num / info->num_base;
					}
				if (tmp_num[0] == '0' && (info->precision == 0 || info->dot_only == ENABLE))
					len = 0;
				if (len > info->precision)
					info->precision = len;
				info->gap = info->width - info->precision;
				if (info->minus == DISABLE && info->width > max(tmp_pre, len))
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
				printed += write(1, temp, str - temp);
			}
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
