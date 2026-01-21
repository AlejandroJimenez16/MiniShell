/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:58:34 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/21 17:59:33 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	create_path(char **s1, char *s2)
{
	char	*new_string;

	new_string = ft_strjoin(*s1, "/");
	free(*s1);
	*s1 = ft_strjoin(new_string, s2);
	free(new_string);
}

void	handle_cmd_error(char **cmd, t_mini *mini, int permission, char *path)
{
	if (!mini->arr_path || mini->arr_path[0] == NULL)
		print_cmd_error(cmd[0], NULL, ": No such file or directory");
	else if (permission)
		print_cmd_error(path, NULL, ": Permission denied");
	else
		print_cmd_error(cmd[0], NULL, ": command not found");
	if (permission)
		mini->exit_code = 126;
	else
		mini->exit_code = 127;
	free(path);
}

void	print_exec_error(t_mini *mini, char **cmd, char *path)
{
	char	*prefix;

	if (path)
		prefix = ft_strjoin(path, ": ");
	else
		prefix = ft_strjoin(cmd[0], ": ");
	print_cmd_error(prefix, NULL, strerror(errno));
	free(prefix);
	mini->exit_code = 126;
}
