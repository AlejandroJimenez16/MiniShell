/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:24:12 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/21 11:35:53 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares two blocks of memory.
 * 
 * This function compares the first `n` bytes 
 * (each interpreted as unsigned char) 
 * of two memory blocks, `s1` and `s2`. Its compares the memory blocks 
 * byte by byte.
 * 
 * @param s1 Pointer to the first block of memory.
 * @param s2 Pointer to the second block of memory.
 * @param n The number of bytes to compare.
 * @return int A negative value if `s1` is less than `s2`, a positive value 
 * 		   if `s1` is greater than `s2`, or 0 if the blocks are equal.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*p1;
	const unsigned char	*p2;

	i = 0;
	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}
