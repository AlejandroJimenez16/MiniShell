/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:08:49 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/22 13:45:34 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of nodes in a linked list.
 * 
 * This function iterates the list starting from the given node
 * and counts the total number of nodes until the end of the list is reached.
 * 
 * @param lst The first node of the list.
 * @return (int) The tota number of nodes in the list.
 */
int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		count;

	if (!lst)
		return (0);
	current = lst;
	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}
