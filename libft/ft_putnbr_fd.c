/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:13:37 by alejanjiga        #+#    #+#             */
/*   Updated: 2025/01/14 11:26:56 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	special_cases(int n, int fd)
{
	if (n == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		return (1);
	}
	if (n == INT_MAX)
	{
		write(fd, "2147483647", 10);
		return (1);
	}
	if (n == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	return (0);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	temp[10];
	int		i;

	if (special_cases(n, fd))
		return ;
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	i = 0;
	while (n > 0)
	{
		temp[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	while (i > 0)
	{
		write(fd, &temp[i - 1], 1);
		i--;
	}
}
