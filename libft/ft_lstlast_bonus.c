/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:54:22 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/22 13:45:25 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns the last node of a linked list.
 * 
 * This function iterates the list starting from the given node
 * and returns a pointer to the last node. If the list is empty
 * it returns `NULL`.
 * 
 * @param lst The first node of the list.
 * @return (t_list*) A pointer to the last node of the list, or
 * NULL if the list is empty.
 */
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	if (!lst)
		return (NULL);
	while (current != NULL)
	{
		if (current->next == NULL)
			return (current);
		current = current->next;
	}
	return (NULL);
}
