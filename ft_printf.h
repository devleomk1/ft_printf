/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:43:30 by jisokang          #+#    #+#             */
/*   Updated: 2021/04/03 17:28:25 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include "./libft/libft.h"

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define ENABLE 1
# define DISABLE 0
# define SMALL 32

# define DIGITS "0123456789ABCDEF"

typedef struct s_info
{
	int			minus;
	int			zero;
	int			width;
	int			precision;
	int			dot_only;
	int			locass;
	int			num_base;
	int			num_sign;
	int			gap;
	int			address;
}				t_info;

/*
ft_printf.c
*/
void	init_struct(t_info *info);
int	ft_printf(const char *format, ...);
int	ft_parse_symbols(const char *format, va_list ap);

/*
for parse
*/
void	ft_parse_flag(const char **format, t_info *info);
void	ft_parse_width(const char **format, t_info *info, va_list ap);
void	ft_parse_precision(const char **format, t_info *info, va_list ap);
int	ft_parse_type(t_info *info, va_list ap, const char type);

/*
print_type
*/
int	ft_print_char(t_info *info, va_list ap);
int	ft_print_percent(t_info *info);
int	ft_print_string(t_info *info, va_list ap);
int	ft_print_num(t_info *info, va_list ap, const char type);

/*
for num function
*/

int	print_num(t_info *info, long long num);

#endif
