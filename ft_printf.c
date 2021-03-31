/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:37:49 by jisokang          #+#    #+#             */
/*   Updated: 2021/03/31 20:48:04 by jisokang         ###   ########.fr       */
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

// 이거 c파일로 Libft에 빼야됨
int	ft_putstr_len(char *format, int len)
{
	write(1, format, len);
	return (len);
}
void	ft_parse_flag(const char **format, t_info *info)
{
	if (**format == '-')
	{
		info->minus = ENABLE;
		(*format)++;
	}
	if (**format == '0')
	{
		info->zero = ENABLE;
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
				int	len;
				len = 0;
				char tmp_num[21];
				//char c;
				if (num == 0)
					tmp_num[len++] = '0';
				else
				{
					while (num != 0)
					{
						tmp_num[len++] = DIGITS[num % info->num_base];
						num = num / info->num_base;
					}
				}

				if (info->precision < len)
					info->precision = len;
				info->width -= info->precision;

				if (info->minus == DISABLE && info->zero == DISABLE)
					while ((info->width)-- > 0)
						*str++ = ' ';
				/* -- number sign -- */
				if (info->num_sign == -1)
					*str++ = '-';
				/*-------- 수정 HERE! --------- */
				/*
				if (info->zero == DISABLE)
						while ((info->width)-- > 0)
							*str++ = '0';
							*/
				//width = 3
				//preci = 5
				//len   = 2

				if (info->minus == DISABLE && info->zero == ENABLE)
				{
					if ((info->width) > (info->precision))
						while ((info->width)-- > 0)
							*str++ = ' ';
					else if ((info->width) < (info->precision))
						while ((info->width)-- > 0)
							*str++ = '0';
				}
				while (len < (info->precision)--)
					*str++ = '0';
				/*-------- NUM 출력 --------*/
				while (len-- > 0)
					*str++ = tmp_num[len];
				while ((info->width)-- > 0)		//minus 일때 뒤쪽 width 남은거 출력
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
