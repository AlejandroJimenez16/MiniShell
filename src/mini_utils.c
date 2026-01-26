/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:43:51 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/26 14:09:51 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	create_min_env(t_mini *mini)
{
	char	*pwd;

	mini->has_env = 0;
	if (!mini->env)
	{
		mini->env = malloc(sizeof(char *));
		if (!mini->env)
			return ;
		mini->env[0] = NULL;
	}
	pwd = getcwd(NULL, 0);
	set_env(mini, "PWD", pwd);
	set_env(mini, "SHLVL", "1");
	set_env(mini, "PATH",
		"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:"
		"/home/alejandj/.local/bin");
}

void	init_mini(char **argv, char **env, t_mini *mini)
{
	(void)argv;
	if (!env || !env[0])
		create_min_env(mini);
	else
	{
		mini->env = copy_env(env);
		mini->has_env = 1;
	}
	mini->exit_code = 0;
	mini->last_command = ft_strdup("./minishell");
	mini->arr_path = NULL;
	mini->prompt = NULL;
	mini->line = NULL;
	mini->save_stdin = -1;
	mini->save_stdout = -1;
	init_signals();
	ft_init_history(mini);
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
