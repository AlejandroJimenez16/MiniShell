#include "../../includes/pipex_bonus.h"

// static void	print_strarr(char **arr)
// {
// 	int	i = 0;

// 	if (!arr)
// 		return ;
// 	while (arr[i])
// 	{
// 		ft_putstr(arr[i]);
// 		ft_putchar('\n');
// 		i++;
// 	}
// }

// static char **ft_strarrdup(char **strarr, int n)
// {
// 	char	**copy;
// 	int		i;

// 	copy = malloc(sizeof(char *) * (n + 1));
// 	if (!copy)
// 		return (NULL);
// 	i = 0;
// 	while (i < n)
// 	{
// 		copy[i] = ft_strdup(strarr[i]);
// 		if (!copy[i])
// 		{
// 			ft_free_wa(copy);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	copy[i] = NULL;
// 	return (copy);
// }

//Añade al principio de un doble array hasta n elementos (n se tiene en cuenta sin contar first)
static char	**ft_strarradd_first(char *first, char **strarr, int n)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (n + 2));
	if (!copy)
		return (NULL);
	copy[0] = ft_strdup(first);
	if (!copy[0])
	{
		free(copy);
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		copy[i + 1] = ft_strdup(strarr[i]);
		if (!copy[i + 1])
		{
			ft_free_wa(copy);
			return (NULL);
		}
		i++;
	}
	copy[i + 1] = NULL;
	return (copy);
}

int execute_pipex(int argc, char **argv, char **env)
{
	int 	mode;
	int		result;
	char	**temp;

	mode = ft_atoi(argv[argc - 1]);
	temp = ft_strarradd_first("./pipex", argv, argc - 1);
	if (!temp)
		return (1);
	result = pipex(argc, temp, env, mode);
	ft_free_wa(temp);
	return (result);
}
