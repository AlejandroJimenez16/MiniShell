/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:55:50 by alejandj          #+#    #+#             */
/*   Updated: 2025/02/18 11:15:25 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_unsigned(unsigned int nbr)
{
	int	size;

	size = 0;
	if (nbr == 0)
		return (size += ft_putchar('0'));
	if (nbr >= 10)
		size += ft_putnbr_unsigned(nbr / 10);
	size += ft_putchar(nbr % 10 + '0');
	return (size);
}
