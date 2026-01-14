/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:48:15 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/22 13:48:15 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/*
** Global variable that stores exit code when recieving a signal
*/
int	g_sig_status = 0;

/*
** Handler for SIGINT (Ctrl+C) in prompt.
** 1. Prints a new line.
** 2. Tells readline we are in a new line.
** 3. Replace the actual buffer with an empty one.
** 4. Prints the prompt again.
*/
void	handle_sigint(int sig)
{
	(void)sig;
	g_sig_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

/*
** Initialice signals for interaction mode (prompt)
** Ignores Ctrl+\
*/
void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/*
** Configure signals for child processes.
** Establish default behavior, so comands like cat can be closed with Ctrl+C.
*/
void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
