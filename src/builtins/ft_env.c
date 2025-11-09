/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:07:26 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/07 15:18:58 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	ft_env(char **env)
{
	char	**arr;
	int		i;

	if (!env || !env[0])
		return ;
	i = 0;
	while (env[i] != NULL)
	{
		arr = ft_split(env[i], '=');
		if (!arr)
			return ;
		if (arr[1] != NULL)
			printf("%s\n", env[i]);
		ft_free_wa(arr);
		i++;
	}
}
