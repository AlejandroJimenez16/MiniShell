#include "../includes/mini.h"

int	ft_cd(char *path)
{
	char	cwd[1024];

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
	printf("Directory changed to: %s\n", cwd); //test function, must erase
	return (0);
}
