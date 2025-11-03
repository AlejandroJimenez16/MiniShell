/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:18:23 by alejandj          #+#    #+#             */
/*   Updated: 2025/01/23 13:42:24 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	origin_size_dst;
	size_t	origin_size_src;

	origin_size_dst = ft_strlen(dst);
	origin_size_src = ft_strlen(src);
	if (size <= origin_size_dst)
		return (size + origin_size_src);
	i = 0;
	while (src[i] != '\0' && i < size - origin_size_dst - 1)
	{
		dst[origin_size_dst + i] = src[i];
		i++;
	}
	dst[origin_size_dst + i] = '\0';
	return (origin_size_dst + origin_size_src);
}
