/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:08:06 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/24 02:08:01 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	print_cmd_error(char *cmd, char *target, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (target)
	{
		ft_putstr_fd("'", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd("': ", 2);
	}
	ft_putendl_fd(error, 2);
}

void	print_unexpected_error(t_mini *mini, char *invalid)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(invalid, 2);
	ft_putendl_fd("'", 2);
	mini->exit_code = 2;
}
