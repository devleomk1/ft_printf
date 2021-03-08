/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:51:01 by jisokang          #+#    #+#             */
/*   Updated: 2021/02/20 19:55:02 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*next_lst;

	curr = *lst;
	while (curr != NULL)
	{
		next_lst = curr->next;
		ft_lstdelone(curr, del);
		curr = next_lst;
	}
	*lst = NULL;
}
