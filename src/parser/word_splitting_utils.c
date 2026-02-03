/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:57:29 by alejandj          #+#    #+#             */
/*   Updated: 2026/02/03 14:01:41 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	has_separators(char *tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i] == ' ' || tokens[i] == '\t' || tokens[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	normalize_split(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t' || str[i] == '\n')
			str[i] = ' ';
		i++;
	}
}
