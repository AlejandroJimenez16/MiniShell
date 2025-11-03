/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:04:06 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/15 15:25:28 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Sets a block of memory to zero.
 * 
 * This function fills the first `n` bytes of the memory area
 * pointed to by `s` with zeros (bytes set to 0).
 * 
 * @param s A pointer to the memory area to be filled with zeros.
 * @param n The number of bytes to set to zero.
 * @return None.
 */
void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}
