/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:38:49 by alejandj          #+#    #+#             */
/*   Updated: 2025/02/18 11:36:40 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	p_format(va_list args)
{
	void	*ptr;
	int		size;

	size = 0;
	ptr = va_arg(args, void *);
	if (ptr == NULL)
		size += ft_putstr("(nil)");
	else
	{
		size += ft_putstr("0x");
		size += ft_print_pointer((unsigned long)ptr, "0123456789abcdef");
	}
	return (size);
}

int	apply_format(va_list args, char c)
{
	int	size;

	size = 0;
	if (c == 'c')
		size += ft_putchar(va_arg(args, int));
	if (c == 's')
		size += ft_putstr(va_arg(args, char *));
	if (c == 'p')
		size += p_format(args);
	if (c == 'd')
		size += ft_putnbr_dec(va_arg(args, int));
	if (c == 'i')
		size += ft_putnbr_dec(va_arg(args, int));
	if (c == 'u')
		size += ft_putnbr_unsigned(va_arg(args, unsigned int));
	if (c == 'x')
		size += ft_putnbr_hex(va_arg(args, int), "0123456789abcdef");
	if (c == 'X')
		size += ft_putnbr_hex(va_arg(args, int), "0123456789ABCDEF");
	if (c == '%')
		size += ft_putchar('%');
	return (size);
}

int	ft_printf(char const *str, ...)
{
	int		i;
	int		size;
	va_list	args;

	va_start(args, str);
	size = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			size += apply_format(args, str[i]);
		}
		else
		{
			size += ft_putchar(str[i]);
		}
		i++;
	}
	va_end(args);
	return (size);
}
