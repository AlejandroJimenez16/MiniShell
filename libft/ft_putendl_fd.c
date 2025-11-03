/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:05:45 by alejanjiga        #+#    #+#             */
/*   Updated: 2025/01/16 15:07:40 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs a string followed by a newline to a specified file descriptor.
 * 
 * This function writes the string `s` to the file descriptor `fd`, followed
 * by a newline character (`\n`).
 * 
 * If `s` is NULL, the function does nothing.
 * 
 * @param c The character to output.
 * @param fd The file descriptor where the character will be written.
 */
void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
