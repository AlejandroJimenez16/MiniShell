/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:18:56 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/23 12:50:24 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*node;
	t_list	*new_node;
	void	*mapped_content;

	new_lst = NULL;
	node = lst;
	if (!lst || !f || !del)
		return (NULL);
	while (node != NULL)
	{
		mapped_content = f(node->content);
		new_node = ft_lstnew(mapped_content);
		if (!new_node)
		{
			del(mapped_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		node = node->next;
	}
	return (new_lst);
}
