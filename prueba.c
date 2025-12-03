#include "includes/mini.h"

int	main(void)
{
	char *str = "cat <<EOF | grep \"foo\"";

	int	n = count_tokens(str);

	t_token_info	*t_info;
	t_info = malloc(n * sizeof(t_token_info));
	if (!t_info)
		return (1);

	char **arr = split_tokens(str, &t_info);
	if (!arr)
		return (1);

	for (int i = 0; i < n; i++)
	{
		printf("%s\n", arr[i]);

		if (t_info[i].type_token == WORD)
			printf("WORD\n");
		else if (t_info[i].type_token == PIPE)
			printf("PIPE\n");
		else if (t_info[i].type_token == REDIR_IN)
			printf("REDIR_IN\n");
		else if (t_info[i].type_token == REDIR_OUT)
			printf("REDIR_OUT\n");
		else if (t_info[i].type_token == REDIR_APPEND)
			printf("REDIR_APPEND\n");
		else if (t_info[i].type_token == HEREDOC)
			printf("HEREDOC\n");

		if (t_info[i].type_quote == NO_QUOTES)
			printf("NO_QUOTES\n");
		else if (t_info[i].type_quote == SINGLE_QUOTES)
			printf("SINGLE_QUOTES\n");
		else if (t_info[i].type_quote == DOUBLE_QUOTES)
			printf("DOUBLE_QUOTES\n");
		printf("-------------------------------\n");
	}
	return (0);
}