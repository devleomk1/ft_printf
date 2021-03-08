/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 04:10:22 by jisokang          #+#    #+#             */
/*   Updated: 2021/02/20 19:56:45 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	find;
	int		i;

	find = (unsigned char)c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == find)
			return ((char *)s + i);
		i--;
	}
	if (s[0] == find)
		return ((char *)s);
	return (0);
}
