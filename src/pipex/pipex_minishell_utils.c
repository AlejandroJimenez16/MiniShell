#include "../../includes/pipex_bonus.h"

int get_limit(int argc, int mode)
{
    if (mode == 0)
	{
		return (argc);
	}
    else
        return (argc - 1);
}

void continue_redirect_io(t_context *context)
{
    if (context->order == 2 || (context->order == 3
			&& ft_strncmp(context->argv[1], "here_doc", 8) == 0))
	{
		if (ft_strncmp(context->argv[1], "here_doc", 8) == 0
			&& context->io[0] == -1)
			stderror_manager("Error: here_doc failed", 1, 1);
		if (access(context->argv[1], F_OK | R_OK) == -1
			&& ft_strncmp(context->argv[1], "here_doc", 8) != 0)
			stderror_manager(context->argv[1], 0, 1);
		dup2(context->io[0], STDIN_FILENO);
		dup2(context->pipe_io[1], STDOUT_FILENO);
	}
	else if (context->order == context->argc - 2)
	{
		if (access(context->argv[context->argc - 1], W_OK) == -1)
			stderror_manager(context->argv[context->argc - 1], 0, 1);
		if ((context->cmd_order) % 2 == 0)
			dup2(context->pipe2_io[0], STDIN_FILENO);
		else
			dup2(context->pipe_io[0], STDIN_FILENO);
		dup2(context->io[1], STDOUT_FILENO);
	}
	else
		redirect_pipe(context);
	close_all(context);
}
