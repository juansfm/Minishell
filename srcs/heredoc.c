#include "minishell.h"

void	ft_redir(t_general *g_data, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->heredoc != NULL && cmd->heredoc[++i] != NULL && g_running != 0)
		ft_heredoc(g_data, cmd->heredoc[i]);
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
	if (cmd->cmd[0] != NULL)
	{
		ft_vamos_a_expandir(g_data);
		ft_restore_quotes(g_data->cmd->cmd);
		ft_quita_comillas(g_data);
	}
}

static void	ft_heredoc_pipe(char *input)
{
	int	pipefd[2];
	int	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		ft_putstr_fd(input, STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	ft_heredoc(t_general *g_data, char *delimiter)
{
	char	*input;
	char	*line;
	int		out;

	g_running = 2;
	input = ft_strdup("");
	line = ft_strdup("");
	dup2(g_data->og_in, STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	dup2(g_data->og_out, STDOUT_FILENO);
	line = readline("> ");
	while (g_running == 2 && (line && ft_strcmp(line, delimiter)))
	{
		input = ft_strjoin_free(input, line);
		input = ft_strjoin_free(input, "\n");
		free(line);
		line = readline("> ");
	}
	ft_heredoc_pipe(input);
	dup2(out, STDOUT_FILENO);
	close(out);
	free(input);
	free(line);
	if (g_running == 2 && g_data->cmd->next == NULL)
		g_running = 1;
	else if (g_running == 2 && g_data->cmd->next != NULL)
		g_running = 3;
}
