#include "minishell.h"

void	ft_redir(t_general *g_data, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->heredoc != NULL && cmd->heredoc[++i] != NULL)
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

	input = ft_strdup("");
	dup2(g_data->og_in, STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	dup2(g_data->og_out, STDOUT_FILENO);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		input = ft_strjoin(input, line);
		input = ft_strjoin(input, "\n");
		free(line);
	}
	ft_heredoc_pipe(input);
	dup2(out, STDOUT_FILENO);
	close(out);
}
