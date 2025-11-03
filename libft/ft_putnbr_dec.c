/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_dec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:37:18 by alejandj          #+#    #+#             */
/*   Updated: 2025/02/18 11:53:44 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_dec(int nbr)
{
	int				size;

	size = 0;
	if (nbr == INT_MIN)
		return (size += ft_putstr("-2147483648"));
	if (nbr < 0)
	{
		size += ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr >= 10)
		size += ft_putnbr_dec(nbr / 10);
	size += ft_putchar((nbr % 10) + '0');
	return (size);
}
