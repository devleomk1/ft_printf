/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:43:44 by jisokang          #+#    #+#             */
/*   Updated: 2021/03/30 17:17:40 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 테스트용 main 함수 */
int	main(void)
{
	int a = 0;
	//printf("%-7d", 33);
	//printf("hello, %.s", "gavin");
	printf("%.*s", -1, 0);
	printf("\n-----\n");
	ft_printf("%.*s", -1, 0);
	//a = ft_printf("%%%%");
	//printf("\n\na = %d", a);
}
