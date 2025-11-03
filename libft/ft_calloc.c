/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:11:27 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/21 13:05:09 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates and initializes memory for an array.
 * 
 * This function allocates memory for an array of `nmemb`elements, each of
 * size `size` bytes, and initializes all allocated bytes to zero.
 * 
 * @param nmemb The number of elements to allocate.
 * @param size The size (in bytes) of each element.
 * @return void* A pointer to the allocated memory. If the allocation fails,
 *         the function returns `NULL`.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = malloc(nmemb * size);
	if (!p)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
}
