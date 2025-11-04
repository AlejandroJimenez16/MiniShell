#include "../../includes/pipex_bonus.h"

static int	is_forbidden_token(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strncmp(arg, "|", 2) == 0)
		return (1);
	if (ft_strncmp(arg, ">>", 3) == 0)
		return (1);
	if (ft_strncmp(arg, "<<", 3) == 0)
		return (1);
	return (0);
}

static char	**remove_forbidden_tokens(char **argv)
{
	char	**new_argv;
	int		i;
	int		j;
	int		count;

	count = 0;
	i = -1;
	while (argv[++i])
		if (!is_forbidden_token(argv[i]))
			count++;
	new_argv = malloc(sizeof(char *) * (count + 1));
	if (!new_argv)
		return (NULL);
	i = -1;
	j = 0;
	while (argv[++i])
		if (!is_forbidden_token(argv[i]))
			new_argv[j++] = ft_strdup(argv[i]);
	new_argv[j] = NULL;
	free_tab(argv);
	return (new_argv);
}


int	ft_pipex_exec(char **argv, char **env)
{
	t_context	ctx;
	int			argc;

    argv = remove_forbidden_tokens(argv);
	if (!argv)
		return (stderror_manager("Error: malloc failed", 1, 1), 1);
	argc = ft_tablen(argv);
	if (argc <= 2 || argc == 3)
		return (free_tab(argv), stderror_manager("Error: Needed min 2 arguments or more than 3", 1, 1),
             1);
	io_manager(argc, argv, &ctx);
	ctx.env = env;
	ctx.argc = argc;
	ctx.argv = argv;
	ctx.cmd_order = 0;
	if (pipe(ctx.pipe_io) == -1 || pipe(ctx.pipe2_io) == -1)
		return (free_tab(argv),
            stderror_manager("Error: Pipe failed", 1, 1), 1);
	argc = ft_pipex_loop(&ctx);
	free_tab(argv);
	return (argc);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}
void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
