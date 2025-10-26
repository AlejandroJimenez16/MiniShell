/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:27:28 by alejandj          #+#    #+#             */
/*   Updated: 2025/10/24 20:42:31 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	//char	*prompt;
	
	if (argc == 1)
	{
		// Ignorar argv
		(void)argv;

		// Bucle que muestra prompt
		while (1)
		{
			get_prompt(envp);
			line = readline("hola >");
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