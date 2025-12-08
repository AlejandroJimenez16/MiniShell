#include "includes/mini.h"

static void	expand_cmd_list(t_list *cmd_list, t_mini *mini, t_token_info *t_info)
{
	t_list	*current;
	t_cmd	*node;

	current = cmd_list;
	while (current)
	{
		node = current->content;
		expand_vars(node->cmd, mini, t_info, node->index_start_cmd);
		current = current->next;
	}
}

static void	handle_line(t_mini *mini)
{
	char			**tokens;
	t_token_info	*t_info;
	t_list			*cmd_list;

	// Inicializar token_info
	t_info = malloc(count_tokens(mini->line) * sizeof(t_token_info));
	if (!t_info)
		return ;

	// Crear array de tokens
	tokens = split_tokens(mini->line, &t_info);
	if (!tokens)
		return ;

	cmd_list = create_cmd_list(mini->line, tokens, t_info);
	printf("PRE EXPANSION\n");
	print_cmd_list(cmd_list);
	expand_cmd_list(cmd_list, mini, t_info);
	printf("POST EXPANSION\n");
	print_cmd_list(cmd_list);
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