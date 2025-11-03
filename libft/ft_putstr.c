/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:25:54 by alejandj          #+#    #+#             */
/*   Updated: 2025/02/18 13:03:07 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s)
{
	int	i;
	int	size;

	if (!s)
		return (ft_putstr("(null)"));
	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		size += ft_putchar(s[i]);
		i++;
	}
	return (size);
}
