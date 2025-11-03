/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:25:30 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/26 13:03:23 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;
	t_list	*next_node;

	if (!lst)
		return ;
	node = *lst;
	while (node != NULL)
	{
		next_node = node->next;
		if (del)
			del(node->content);
		free(node);
		node = next_node;
	}
	*lst = NULL;
}
