/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:42:46 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/30 15:03:54 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	update_shlvl(t_mini *mini)
{
	char	*value;
	int		n;
	char	*new_val;

	value = get_env("SHLVL", mini->env);
	if (!value)
		n = 0;
	else
		n = ft_atoi(value);
	if (n < 0)
		n = 0;
	n++;
	new_val = ft_itoa(n);
	if (!new_val)
		return ;
	set_env(mini, "SHLVL", new_val);
	free(new_val);
}
