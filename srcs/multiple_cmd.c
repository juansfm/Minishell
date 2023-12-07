#include "minishell.h"

void	ft_multiple_cmd(t_general *g_data, t_cmd *cmd)
{
	int		fd[2];
	int		pid;
	char	**env_mtx;
	int		status;

	env_mtx = ft_env_mtx(g_data);
	cmd->cmd[0] = ft_path(g_data, cmd->cmd[0]);
	pipe(fd);
	pid = fork();
	if (pid == 1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		status = execve(cmd->cmd[0], cmd->cmd, env_mtx);
		// if (!ft_builtins(g_data, cmd->cmd))
		// ft_other_cmd(g_data, cmd->cmd);
		exit(0);
	}
	else if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		// if (cmd->next)
		// {
		// 	ft_free(env_mtx, ft_mtxrow(env_mtx));
		// 	ft_multiple_cmd(g_data, cmd->next);
		// }
		// else
		// {
			// if (!ft_builtins(g_data, cmd->cmd))
			// ft_other_cmd(g_data, cmd->cmd);
			cmd->next->cmd[0] = ft_path(g_data, cmd->next->cmd[0]);
			printf("hola, cmd->next->cmd[0]=%s\n", cmd->next->cmd[0]);
			status = execve(cmd->next->cmd[0], cmd->next->cmd, env_mtx);
		// }
		exit(0);
	}
}
