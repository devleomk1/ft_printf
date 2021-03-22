/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:43:30 by jisokang          #+#    #+#             */
/*   Updated: 2021/03/22 14:48:36 by jisokang         ###   ########.fr       */
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

# define PLUS 1
# define MINUS -1

# define DIGITS "0123456789ABCDEF"

/*
소문자 바꾸기는 ascii 값 차이 +40을 해주면 된다. 아님 ft_tolower쓰던가
*/

typedef struct	s_info
{
	int			minus;
	int			zero;
	int			width;
	int			precison;
	int			num_base;
	int			num_sign;
	char		type;
}				t_info;

int	ft_printf(const char *format, ...);
int	parse_symbols(const char *format, va_list ap);

#endif
