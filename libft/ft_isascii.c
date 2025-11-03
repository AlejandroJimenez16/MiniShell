/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:22:17 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/21 11:32:06 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a character is an ASCII character.
 * 
 * This function determines whether the given character is part of the
 * standard ASCII character set, wich includes values from 0 to 127.
 * 
 * @param c The character to ckeck passed as an `int`.
 * @return Returns a nonzero value (true) if the character is an ASCII character;
 *         otherwise, returns 0 (false).
 */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
