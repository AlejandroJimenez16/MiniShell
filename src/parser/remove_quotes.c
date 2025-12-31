/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 19:50:33 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/30 22:07:49 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char	*remove_quotes(char *value, int len_value)
{
	char	*value_clean;
	int		i;
	int		j;

	i = 1;
	j = 0;
	value_clean = malloc(len_value - 2 + 1);
	if (!value_clean)
		return (NULL);
	while (i < len_value - 1)
	{
		value_clean[j] = value[i];
		j++;
		i++;
	}
	value_clean[j] = '\0';
	return (value_clean);
}
