/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:33:07 by jisokang          #+#    #+#             */
/*   Updated: 2021/02/20 19:55:41 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dst;
	unsigned char	value;
	size_t			i;

	dst = b;
	value = c;
	i = 0;
	while (i < len)
	{
		dst[i] = value;
		i++;
	}
	return (b);
}
