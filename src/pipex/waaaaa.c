/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waaaaa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:34:48 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/28 13:39:34 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	*ft_free_wa(char **word_arr)
{
	int	i;

	i = 0;
	while (word_arr[i])
		free(word_arr[i++]);
	free(word_arr);
	return ((void *)0);
}
