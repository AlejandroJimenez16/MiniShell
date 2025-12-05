/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:27:28 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/05 13:23:48 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/*
static void	handle_simple_commands(t_mini *mini)
{
	t_token_info	*t_info;
	int				status;
	
	t_info = malloc(count_tokens(mini->line) * sizeof(t_token_info));
	if (!t_info)
		return ;
	mini->cmd = split_tokens(mini->line, &t_info);
	if (!mini->cmd)
	{
		ft_free_wa(mini->arr_path);
		free(mini->line);
		clear_history();
		return ;
	}
	expand_vars(mini, t_info);
	if (!is_builtin(mini->cmd))
	{
		child_simple_cmd(mini);
		waitpid(mini->simple_cmd_process, &status, 0);
		mini->exit_code = WEXITSTATUS(status);
	}
	else
		exec_builtins(mini);
	if (mini->cmd && mini->cmd[0])
	{
    	if (mini->last_command)
        	free(mini->last_command);
    	mini->last_command = ft_strdup(mini->cmd[count_tokens(mini->line) - 1]);
	}
	ft_free_wa(mini->cmd);
}

static int	validate_line(char *line)
{
	int		i;
	int		single_open;
	int		double_open;

	single_open = 0;
	double_open = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !double_open)
			single_open = !single_open;
		else if (line[i] == '\"' && !single_open)
			double_open = !double_open;	
		i++;
	}
	if (single_open || double_open)
	{
		ft_putendl_fd("minishell: syntax error: unclosed quotes", 2);
		return (0);
	}
	return (1);
}

static void	handle_line(t_mini *mini)
{
	char	**parsed_argv;

	if (!mini->line || *mini->line == '\0')
		return ;

	if (!validate_line(mini->line))
		return ;
	if (ft_strchr(mini->line, '|'))
	{
		parsed_argv = parse_line(mini->line);
		if (!parsed_argv)
			return ;
		execute_pipex(count_items(parsed_argv), parsed_argv, mini->env);
		ft_free_wa(parsed_argv);
	}
	else
		handle_simple_commands(mini);
}
*/

void	add_arguments(char **cmd, char *token, int *cmd_index, int n_words)
{
	if (*cmd_index >= n_words)
		return ;
	cmd[*cmd_index] = ft_strdup(token);
	(*cmd_index)++;
	cmd[*cmd_index] = NULL;
}

static t_cmd	*create_node(char **tokens, t_token_info *t_info, int *i)
{
	t_cmd	*node;
	int		n_words;
	int		cmd_index;

	node = malloc(sizeof(t_cmd));
	
	// Inicializar la estructura
	node->cmd = NULL;
	node->infile = NULL;
	node->heredoc = 0;
	node->delimeter = NULL;
	node->outfile = NULL;
	node->append = 0;

	// Recorrer y asignar
	n_words = get_cmd_arr_size(tokens, t_info, *i);
	node->cmd = malloc((n_words + 1) * sizeof(char *));
	cmd_index = 0;
	
	while (tokens[*i])
	{
		if (t_info[*i].type_token == PIPE)
		{
			(*i)++;
			break ;
		}
		if (t_info[*i].type_token == WORD)
		{
			if (*i == 0 || !is_redir(t_info[*i - 1].type_token))
				add_arguments(node->cmd, tokens[*i], &cmd_index, n_words);
			else if (t_info[*i - 1].type_token == REDIR_IN)
				node->infile = ft_strdup(tokens[*i]);
			else if (t_info[*i - 1].type_token == REDIR_OUT)
				node->outfile = ft_strdup(tokens[*i]);
			else if (t_info[*i - 1].type_token == REDIR_APPEND)
			{
				node->append = 1;
				node->outfile = ft_strdup(tokens[*i]);
			}
			else if (t_info[*i - 1].type_token == HEREDOC)
			{
				node->heredoc = 1;
				node->delimeter = ft_strdup(tokens[*i]);
			}
		}
		(*i)++;
	}
	return (node);
}

static void	handle_line(t_mini *mini)
{
	char			**tokens;
	t_token_info	*t_info;
	t_list			*cmd_list;
	int				num_nodes;
	int				i;
	int				index;

	// Inicializar token_info
	t_info = malloc(count_tokens(mini->line) * sizeof(t_token_info));
	if (!t_info)
		return ;

	// Crear array de tokens
	tokens = split_tokens(mini->line, &t_info);
	if (!tokens)
		return ;

	// Crear los nodos
	cmd_list = NULL;
	num_nodes = get_num_nodes(mini->line, t_info);
	i = 0;
	index = 0;
	while (index < num_nodes)
	{
		ft_lstadd_back(&cmd_list, ft_lstnew(create_node(tokens, t_info, &i)));
		index++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	if (argc != 1)
		return (ft_putendl_fd("minishell: no args supported", 2), 1);
	(void)argv;
	mini.env = env;
	mini.exit_code = 0;
	mini.last_command = NULL;
	while (1)
	{
		mini.prompt = get_prompt(mini.env);
		mini.line = readline(mini.prompt);
		if (!mini.line)
			return (ft_printf("exit\n"), 0);
		add_history(mini.line);
		handle_line(&mini);
		free(mini.line);
	}
	free(mini.prompt);
	return (0);
}
