/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:14:53 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/16 15:04:09 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Output a character to a specified file descriptor.
 * 
 * This function writes the character `c` with the file descriptor `fd`.
 * 
 * @param c The character to output.
 * @param fd The file descriptor where the character will be written.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
