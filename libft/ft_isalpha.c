/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:20:10 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/21 11:31:49 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a character is alphabetic.
 * 
 * This function determines whether the given character is a letter
 * (either uppercase (A-Z) or lowercase (a-z).
 * 
 * @param c The character to ckeck passed as an `int`.
 * @return Returns a nonzero value (true) if the character is alphabetic;
 *         otherwise, returns 0 (false).
 */
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
