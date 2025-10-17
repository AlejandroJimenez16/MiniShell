/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:27:28 by alejandj          #+#    #+#             */
/*   Updated: 2025/10/17 13:58:30 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	main(int argc, char **argv, char **envp)
{
	char *line;
	
	if (argc == 1)
	{
		// Ignorar argv y envp
		(void)argv;
		(void)envp;

		// Bucle que muestra prompt
		while (1)
		{
			line = readline("alejandj@aleconst$ ");
			if (!line)
				break ;
			
			add_history(line);
		}
	}
	else
	{
		ft_putendl_fd("minishell: no args supported", 2);
		return (1);
	}
}