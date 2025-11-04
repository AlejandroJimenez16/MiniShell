#include "../../includes/pipex_bonus.h"

void	*ft_free_wa(char **word_arr)
{
	int	i;

	i = 0;
	while (word_arr[i])
	{
		free(word_arr[i++]);
	}
	free(word_arr);
	return ((void *)0);
}
