/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:26:11 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/17 18:56:20 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	obtain_num_digits(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

/**
 * @brief The itoa function (Integer to ASCII) converts an integer to a string.
 * 
 * This function converts the integer `n` into a string representation.
 * 
 * @param n The integer to convert.
 * @return char* A pointer to the resulting string representation of the integer.
 */
char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = obtain_num_digits(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (len > 0)
	{
		if (str[len - 1] == '-')
			break ;
		str[--len] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}
