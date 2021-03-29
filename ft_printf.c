/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:37:49 by jisokang          #+#    #+#             */
/*   Updated: 2021/03/29 15:33:53 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 구조체 초기화 함수 */
void	init_struct(t_info info)
{
	info.minus = FALSE;
	info.zero = FALSE;
	info.width = 0;
	info.precision = 0; //-1?
	info.num_base = 10;
	info.num_sign = 0;
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
/* 분석하는 함수 */
int	parse_symbols(const char *format, va_list ap)
{
	t_info			*info;
	int				printed;
	long long		num;
	char			*str;		//출력 할 문자열
	char			*temp;
	size_t			i;

	printed = 0;
	/*---------- info ------------*/
	info = malloc(sizeof(t_info) * 1);
	if(!info)
		return (ERROR);
	/*----------------------------*/

	//str = (char [21]){};	//출력할 문자열의 MAX 길이는 20 + '\0'
	//temp = str;
	while(*format != 0)
	{
		init_struct(*info);
		str = (char [21]){};	//출력할 문자열의 MAX 길이는 20 + '\0'
		temp = str;
		if (*format != '%')
		{
			//*str++ = *format;
			printed += write(1, format, 1);
			format++;
		}
		if (*format == '%')
		{
			format++;
			if (*format == '-')
			{
				info->minus = TRUE;
				format++;
			}
			if (*format == '0')
			{
				info->zero = TRUE;
				format++;
			}
			/* atoi get width */
			if (ft_isdigit(*format) == TRUE)
				info->width = skip_atoi(&format);	//동작확인
			else if (*format == '*')
			{
				format++;
				info->width = va_arg(ap, int);
				if (info->width < 0)
				{
					info->width = -(info->width);	// *로 width값이 음수값으로 들어오면
					info->minus = TRUE;				//'-' flag TRUE
				}
			}

			/* atoi get precision here */
				//* va_arg
				//if (precision < 0) -> precision = 0;
			if (*format == '.')
			{
				format++;
				if (ft_isdigit(*format))
					info->precision = skip_atoi(&format);
				else if (*format == '*')
				{
					format++;
					info->precision = va_arg(ap, int);
				}
				if (info->precision < 0)
					info->precision = 0;
			}
			if (*format == 'c')
			{
				//printf("%c\n", *format);
				if (info->minus != TRUE)
					while(--(info->width) > 0)
						*str++ = ' ';
				*str++ = (unsigned char)va_arg(ap, int);
				while (--(info->width) > 0)
					*str++ = ' ';
				format++;
				//printf("%c\n", *format);
				*str = '\0';
				printed += write(1, temp, ft_strlen(temp));
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
				format++;
				/*---------- prototype cal ------------*/
				i = 0;
				char tmp_num[21];
				if (num == 0)
					tmp_num[i++] = '0';
				else
				{
					while (num != 0)
					{
						tmp_num[i++] = DIGITS[num % info->num_base];
						num = num / info->num_base;
					}
				}
				if (i > info->precision)
					info->precision = i;
				info->width -= info->precision;
				if (info->minus == FALSE)	//이거 조건 어떻게 줘야하지? 이게 minus falg on 이면 동작하지 말아야지
					while ((info->width)-- > 0)
						*str++ = ' ';
				if (info->num_sign == -1)
					*str++ = '-';
				while (i < (info->precision)--)
					*str++ = '0';
				while (i-- > 0)
					*str++ = tmp_num[i];
				while (info->width > 0)
					*str++ = ' ';
				*str = '\0';
				printed += write(1, temp, ft_strlen(temp));
			}

			/*---------- ------------- ------------*/
/*
			int j = 0;
			while (j < 21)
			{
				printf("|%d|", temp[j]);
				j++;
			}
*/
		}

	}
	//*str = '\0';
	//printed += write(1, temp, ft_strlen(temp));

	free(info);
	return (printed);
}

int	ft_printf(const char *format, ...)
{
	va_list ap;
	int printed;

	va_start(ap, format);
	printed = parse_symbols(format, ap);
	va_end(ap);
	return (printed);
}
