/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:25:02 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/21 11:32:48 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a character is printable.
 * 
 * This function determines whether the given character is a printable
 * character, including visible characters and the space character.
 * 
 * @param c The character to ckeck passed as an `int`.
 * @return Returns a nonzero value (true) if the character is printable;
 *         otherwise, returns 0 (false).
 */
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
