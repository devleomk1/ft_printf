/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:43:44 by jisokang          #+#    #+#             */
/*   Updated: 2021/03/20 16:29:05 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(void)
{
	//ft_printf("ft_printf : Hello %d World %d\n", 1, 2);
	//printf("   printf : Hello %d World %d\n", 1, 2);
	printf("----------------------------------\n");
	printf("|%5c|\n", 'A');
	printf("|%-5c|\n", 'A');
	printf("|%-c|", 'A');
	printf("|%c|", 'A');
}
