#include "../includes/mini.h"

int	ft_cd(t_mini *mini)
{
	char	cwd[1024];
	char	*path = mini->cmd[1];

	if (!path)
	{
		fprintf(stderr, "cd: missing argument\n");
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	return (0);
}
