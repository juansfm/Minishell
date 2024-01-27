#include "minishell.h"

// Los argumentos de esta funcion pueden cambiar segun evoluciona el programa
/**
 * @brief Execute the cmd if it's a built-in or go to no built-in function
 * 
 * @param g_data general struct
 * @param cmd command
 * @param arg arguments to the command in a string (can change to a matrix)
 */
int	ft_builtins(t_general *g_data, char **arg)
{
	int	i;

	i = 0;
	if (access(".", R_OK | W_OK | X_OK) == -1)
		return (0);
	if (!ft_strcmp(arg[0], "echo") || !ft_strcmp(arg[0], "ECHO"))
		ft_echo(g_data, arg);
	else if (!ft_strcmp(arg[0], "cd"))
		g_data->status = ft_cd(g_data, arg);
	else if (!ft_strcmp(arg[0], "pwd") || !ft_strcmp(arg[0], "PWD"))
		ft_pwd(g_data);
	else if (!ft_strcmp(arg[0], "export"))
		ft_export(g_data, arg);
	else if (!ft_strcmp(arg[0], "env") || !ft_strcmp(arg[0], "ENV"))
		ft_print_env(g_data);
	else if (!ft_strcmp(arg[0], "unset"))
	{
		while (arg[++i])
			ft_delete_env(g_data, arg[i]);
	}
	else if (!ft_strcmp(arg[0], "exit"))
		ft_exit(g_data, arg);
	else
		return (0);
	return (1);
}

int	ft_other_cmd(t_general *g_data, char **arg)
{
	char	**env_mtx;
	int		pid;
	int		status;

	arg[0] = ft_path(g_data, arg[0]);
	if (!arg[0])
	{
		printf("No such file or directory\n");
		return (127);
	}
	env_mtx = ft_env_mtx(g_data);
	pid = fork();
	if (pid == 0)
	{
		status = execve(arg[0], arg, env_mtx);
		printf("%s: command not found\n", arg[0]);
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	ft_free(env_mtx, ft_mtxrow(env_mtx));
	return (WEXITSTATUS(status));
}

char	**ft_union_cmd_arg(char *cmd, char **arg)
{
	char	**mtx;
	int		i;

	i = ft_mtxrow(arg) + 2;
	mtx = ft_calloc(i, sizeof(char *));
	mtx[0] = ft_strdup(cmd);
	if (!arg)
		return (mtx);
	i = -1;
	while (arg[++i])
		mtx[i + 1] = ft_strdup(arg[i]);
	return (mtx);
}

char	**ft_env_mtx(t_general *g_data)
{
	t_env	*temp;
	char	**mtx;
	char	*aux;
	int		i;

	temp = g_data->env;
	mtx = ft_calloc(ft_env_len(g_data) + 1, sizeof(char *));
	i = 0;
	while (temp != NULL)
	{
		if (!temp->equal)
			mtx[i] = ft_strdup(temp->name);
		if (temp->equal)
		{
			aux = ft_strjoin(temp->name, "=");
			if (temp->valor)
				mtx[i] = ft_strjoin(aux, temp->valor);
			else
				mtx[i] = ft_strdup(aux);
			free(aux);
		}
		temp = temp->next;
		i++;
	}
	return (mtx);
}

char	**ft_get_paths(t_general *g_data, char *cmd)
{
	t_env	*temp;

	if (access(cmd, F_OK) == 0)
		return (NULL);
	temp = ft_env_search(g_data, "PATH");
	if (!temp)
		return (NULL);
	return (ft_split(temp->valor, ':'));
}

char	*ft_path(t_general *g_data, char *cmd)
{
	char	**paths;
	char	*aux;
	int		i;

	i = -1;
	aux = NULL;
	paths = ft_get_paths(g_data, cmd);
	if (!paths)
		return (cmd);
	while (paths[++i])
	{
		aux = ft_strjoin_free(ft_strjoin(paths[i], "/"), cmd);
		if (access(aux, F_OK) == 0)
			break ;
		free(aux);
		aux = NULL;
	}
	if (!aux)
		aux = ft_strdup(cmd);
	free(cmd);
	ft_free(paths, ft_mtxrow(paths));
	return (aux);
}
