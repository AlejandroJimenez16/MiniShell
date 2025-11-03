/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:30:25 by alejandj          #+#    #+#             */
/*   Updated: 2025/02/18 13:02:31 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_hex(unsigned int nbr, char *base)
{
	int	size;

	size = 0;
	if (nbr >= 16)
		size += ft_putnbr_hex(nbr / 16, base);
	size += ft_putchar(base[nbr % 16]);
	return (size);
}
