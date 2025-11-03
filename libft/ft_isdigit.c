/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:23:58 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/21 11:32:20 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a character is a decimal digit.
 * 
 * This function determines whether the given character is a digit
 * (0-9).
 * 
 * @param c The character to ckeck passed as an `int`.
 * @return Returns a nonzero value (true) if the character is an ASCII character;
 *         otherwise, returns 0 (false).
 */
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
