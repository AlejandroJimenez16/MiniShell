/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:43:51 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/05 13:48:26 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	print_cmd_error(char *cmd, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(error, 2);
}

int	get_cmd_arr_size(char **tokens, t_token_info *t_info, int start)
{
	int	i;
	int	count;

	i = start;
	count = 0;
	while (tokens[i] && t_info[i].type_token != PIPE)
	{
		if (t_info[i].type_token == WORD)
		{
			if (i == 0 || !is_redir(t_info[i - 1].type_token))
				count++;
		}
		i++;
	}
	return (count);
}

int	get_num_nodes(char *line, t_token_info *t_info)
{
	int	i;
	int	count;
	int	n_tokens;

	count = 0;
	n_tokens = count_tokens(line);
	i = 0;
	while (i < n_tokens)
	{
		if (t_info[i].type_token == PIPE)
			count++;
		i++;
	}
	return (count + 1);
}

int	is_redir(int type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == HEREDOC)
		return (1);
	return (0);
}

/* TODO Si es funcion de testeo marcamelo si no, arregla normi */
void    print_cmd_list(t_list *cmd_list)
{
	t_list	*tmp;

	tmp = cmd_list;

	while (tmp)
	{
		t_cmd *node = tmp->content;
		
		printf("Cmd: ");
		for (int i = 0; node->cmd[i]; i++)
			printf("%s ", node->cmd[i]);
		printf("\n");

		if (node->infile)
			printf("infile: %s\n", node->infile);
		if (node->heredoc)
			printf("delimeter: %s\n", node->delimeter);
		if (node->outfile)
			printf("outfile: %s\n", node->outfile);
		if (node->append)
			printf("append: %d\n", node->append);

		tmp = tmp->next;
		printf("\n");
	}
}
