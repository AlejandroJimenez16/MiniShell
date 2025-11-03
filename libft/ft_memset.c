/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:12:21 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/16 14:56:44 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fills a block of memory with a specific value.
 * 
 * This function fills the first `n` bytes of `s` to the specific
 * value `c`.
 * 
 * @param s Pointer to the memory block to be filled.
 * @param c The value to set, (unsigned char)
 * @param n The number of bytes to fill.
 * @return (void*) A pointer to the memory block (`s`)
 */
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
