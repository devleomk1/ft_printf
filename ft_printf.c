/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:37:49 by jisokang          #+#    #+#             */
/*   Updated: 2021/03/16 15:59:14 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_len(char *format, int len)
{
	write(1, format, len);
	return (len);
}

int	parse_symbols(const char *format, va_list ap)
{
	/* parse = 분석 */
	t_info		*info;
	size_t		i;
	size_t		base;		//진법
	int			printed;
	long long	temp_num;
	unsigned long long num;
	char		*word;		//출력 할 단위
	size_t		len;

	if(!(info = malloc(sizeof(t_info) * 1)))
		return (ERROR);
	i = 0;
	printed = 0;
	while(format[i] != 0)
	{
		if (format[i] == '%')
		{
			i++;
			if(format[i] == 'd')
			{
				temp_num = va_arg(ap, int);
				base = 10;
				num = temp_num;
				i++;
			}

			word = (char [21]){};
			len = 20;
			while (num != 0)
			{
				word[len--] = digits[num % base];
				num = num / base;
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
