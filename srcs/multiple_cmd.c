#include "minishell.h"

static void	ft_no_last_cmd(int *fd, t_general *g_data, t_cmd *cmd)
{
	char	**env_mtx;
	int		status;

	env_mtx = ft_env_mtx(g_data);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	ft_redir(g_data, cmd);
	if (!ft_builtins(g_data, cmd->cmd))
	{
		cmd->cmd[0] = ft_path(g_data, cmd->cmd[0]);
		status = execve(cmd->cmd[0], cmd->cmd, env_mtx);
		printf("%s: command not found\n", cmd->cmd[0]);
		exit(127);
	}
	ft_free(env_mtx, ft_mtxrow(env_mtx));
	exit(0);
}

static void	ft_parent_process(t_general *g_data, int *fd, int pid, t_cmd *cmd)
{
	t_cmd	*temp;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, NULL, 0);
	temp = cmd->next;
	if (temp->next != NULL)
		ft_multiple_cmd(g_data, temp);
	else
	{
		ft_redir(g_data, temp);
		if (temp->cmd[0] != NULL)
		{
			if (!ft_builtins(g_data, temp->cmd))
				ft_other_cmd(g_data, temp->cmd);
		}
	}
}

void	ft_multiple_cmd(t_general *g_data, t_cmd *cmd)
{
	int		fd[2];
	int		pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
		ft_no_last_cmd(fd, g_data, cmd);
	else if (pid > 0)
		ft_parent_process(g_data, fd, pid, cmd);
}
