/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:21:24 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/21 11:35:37 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Searches for a character in a block of memory.
 * 
 * This function locates the first occurrence of the character `c` in the
 * block of memory pointed to by `s`. The search is performed over the first
 * `n` bytes of the memory block.
 * 
 * @param s Pointer to the block of memory where the search will be performed.
 * @param c The character to search for, passed as an `int`. The value is
 *          interpreted as an unsigned char.
 * @param n The number of bytes to search within the memory block.
 * @return void* A pointer to the first occurrence of the chaacter `c` in
 *         the memory block. If `c` is not found, the function returns `NULL`. 
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*b;

	i = 0;
	b = (unsigned char *)s;
	while (i < n)
	{
		if (b[i] == (unsigned char)c)
			return (&b[i]);
		i++;
	}
	return (NULL);
}
