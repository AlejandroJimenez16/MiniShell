/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:27:11 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/20 02:58:20 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Lo que se hace con (unsigned char *) es castear los punteros a unsigned char

#include "libft.h"

/**
 * @brief Copies a block of memory from one location to another.
 * 
 * This function copies `n` bytes from the source memory block `src` to the 
 * destination memory block `dest`. The memory areas should not overlap.
 * If the memory areas do overlap, the behavior is undefined. Use `memmove`
 * for overlapping memory areas.
 * 
 * @param dest Pointer to the destination memory block where the content 
 * will be copied.
 * @param src Pointer to the source memory block to copy from.
 * @param n The number of bytes to copy.
 * @return void* A pointer to the destination memory block (`dest`).
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
