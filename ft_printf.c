/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:37:49 by jisokang          #+#    #+#             */
/*   Updated: 2021/03/26 14:35:15 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 구조체 초기화 함수 */
void	init_struct(t_info info)
{
	info.minus = FALSE;
	info.zero = FALSE;
	info.width = 0;
	info.precison = 0; //-1?
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
	t_info		*info;
	int			printed;
	long long	temp_num;
	unsigned long long num;
	char		*str;		//출력 할 문자열
	char		*temp;
	size_t		len;



	printed = 0;
	/*---------- info ------------*/
	info = malloc(sizeof(t_info) * 1);
	if(!info)
		return (ERROR);
	init_struct(*info);
	/*----------------------------*/
	while(*format != 0)
	{
		str = (char [21]){};	//출력할 문자열의 MAX 길이는 20 + \0
		temp = str;
		if (*format == '%')
		{
			format++;
			if(*format == '-')
			{
				info->minus = TRUE;
				format++;
			}
			if(*format == '0')
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
					info->precison = skip_atoi(&format);
				else if (*format == '*')
				{
					format++;
					info->precison = va_arg(ap, int);
				}
				if (info->precison < 0)
					info->precison = 0;
			}


			if (*format == 'c')
			{
				if (info->minus != TRUE)
					while(--(info->width) > 0)
						*str++ = ' ';
				*str++ = (unsigned char)va_arg(ap, int);
				while (--(info->width) > 0)
					*str++ = ' ';
				format++;
			}
			if(*format == 'd' || *format == 'i')
			{
				temp_num = va_arg(ap, int);
				info->num_base = 10;
				num = temp_num;
				format++;
			}
			//check status here

			/*---------- prototype cal ------------*/

			len = 20;
			/*
			while (num != 0)
			{
				str[len--] = DIGITS[num % info->num_base];
				num = num / info->num_base;
			}
			str = &str[len + 1];
			len = 20 - len;
			*/
			*str = '\0';
			printed = printed + ft_putstr_len(temp, len);
			/*---------- prototype cal ------------*/

/*
			int j = 0;
			while (j < 20)
			{
				printf("|%d|", temp[j]);
				j++;
			}
*/
		}
		//ft_putchar_fd(*format, 1);
		write(1, format, 1);
		format++;
	}
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
