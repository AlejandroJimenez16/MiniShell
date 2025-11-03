/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:23:27 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/20 16:24:14 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	int		i;
	long	result;
	int		sign;
	int		digit;

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
		digit = nptr[i] - '0';
		if (sign == 1 && (result > (LONG_MAX - digit) / 10))
			return (LONG_MAX);
		if (sign == -1 && (-result < (LONG_MIN + digit) / 10))
			return (LONG_MIN);
		result = result * 10 + digit;
		i++;
	}
	return (result * sign);
}
