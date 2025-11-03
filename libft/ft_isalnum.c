/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:17:31 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/21 11:31:27 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a character is alphanumeric.
 * 
 * This function determines whether the given character is either a letter
 * (a-z, A-Z) or a digit (0-9).
 * 
 * @param c The character to ckeck passed as an `int`.
 * @return Returns a nonzero value (true) if the character is alphanumeric;
 *         otherwise, returns 0 (false).
 */
int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}
