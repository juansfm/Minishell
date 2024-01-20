#include "minishell.h"

static void	ft_no_last_cmd(int *fd, t_general *g_data, t_cmd *cmd)
{
	char	**env_mtx;
	int		status;

	env_mtx = ft_env_mtx(g_data);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (cmd->outfile != -1)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	if (cmd->infile != -1)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (!ft_builtins(g_data, cmd->cmd))
	{
		cmd->cmd[0] = ft_path(g_data, cmd->cmd[0]);
		status = execve(cmd->cmd[0], cmd->cmd, env_mtx);
		printf("%s: command not found\n", cmd->cmd[0]);
		exit(status);
	}
	exit(0);
}

void	ft_multiple_cmd(t_general *g_data, t_cmd *cmd)
{
	int		fd[2];
	int		pid;
	t_cmd	*temp;

	pipe(fd);
	pid = fork();
	if (pid == 0)
		ft_no_last_cmd(fd, g_data, cmd);
	else if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		temp = cmd->next;
		if (temp->next != NULL)
			ft_multiple_cmd(g_data, temp);
		else
		{
			if (temp->outfile != -1)
			{
				dup2(temp->outfile, STDOUT_FILENO);
				close(temp->outfile);
			}
			if (temp->infile != -1)
			{
				dup2(temp->infile, STDIN_FILENO);
				close(temp->infile);
			}
			if (!ft_builtins(g_data, temp->cmd))
				ft_other_cmd(g_data, temp->cmd);
		}
	}
}