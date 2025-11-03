/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:17:41 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/21 11:30:23 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The atoi function (ASCII to Integer) converts a string
 * representing a number into its corresponding integer value.
 * 
 * This function takes a null-terminated string that represents a number
 * and converts it to its corresponding integer value. The string can
 * include optional leading whitespace and an optional '+' or '-' sign.
 * If the string is not a valid representation of a number, the result is 0.
 * 
 * @param nptr A string containing the number to be converted in base 10.
 * @return The converted value or 0 on error.
 */
int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}
