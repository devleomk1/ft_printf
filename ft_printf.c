/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:37:49 by jisokang          #+#    #+#             */
/*   Updated: 2021/03/22 16:52:24 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 구조체 초기화 함수 */
void	init_struct(t_info info)
{
	info.minus = FALSE;
	info.zero = FALSE;
	info.width = 0;
	info.precison = 0;
	info.num_base = 10;
	info.num_sign = 0;
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
	char		*word;		//출력 할 단위
	size_t		i;
	size_t		len;

	if(!(info = malloc(sizeof(t_info) * 1)))
		return (ERROR);
	init_struct(*info);
	i = 0;
	printed = 0;
	while(format[i] != 0)
	{
		if (format[i] == '%')
		{
			i++;
			if(format[i] == '-')
			{
				info->minus = TRUE;
				i++;
			}
			if(format[i] == '0')
			{
				info->zero = TRUE;
				i++;
			}
			//atoi get width
			//atoi get precision here

			if(format[i] == 'd' || format[i] == 'i')
			{
				temp_num = va_arg(ap, int);
				info->num_base = 10;
				num = temp_num;
				i++;
			}
			//check status here

			word = (char [21]){};
			len = 20;
			while (num != 0)
			{
				word[len--] = DIGITS[num % info->num_base];
				num = num / info->num_base;
			}
			word = &word[len + 1];
			len = 20 - len;
			printed = printed + ft_putstr_len(word, len);
		}
		ft_putchar_fd(format[i], 1);
		i++;
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
