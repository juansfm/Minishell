/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:33:28 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/11/16 14:58:06 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Los argumentos de esta funcion pueden cambiar segun evoluciona el programa
/**
 * @brief Execute the cmd if it's a built-in or go to no built-in function
 * 
 * @param g_data general struct
 * @param cmd command
 * @param arg arguments to the command in a string (can change to a matrix)
 */
void	ft_builtins(t_general *g_data, char *cmd, char **arg)
{
	int	i;

	i = -1;
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "ECHO"))
		ft_echo(g_data, arg);
	else if (!ft_strcmp(cmd, "cd"))
		ft_cd(g_data, arg);
	else if (!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "PWD"))
		ft_pwd(g_data);
	else if (!ft_strcmp(cmd, "export"))
		ft_export(g_data, arg);
	else if (!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "ENV"))
		ft_print_env(g_data);
	else if (!ft_strcmp(cmd, "unset"))
	{
		while (arg[++i])
			ft_delete_env(g_data, arg[i]);
	}
	else if (!ft_strcmp(cmd, "exit"))
		ft_exit(g_data, arg);
	else
		ft_other_cmd(g_data, cmd, arg);
}

int	ft_other_cmd(t_general *g_data, char *cmd, char **arg)
{
	char	**mtx;
	char	**env_mtx;
	int		pid;
	int		status;

	cmd = ft_path(g_data, cmd);
	if (!cmd)
	{
		printf("No such file or directory\n");
		return (0);
	}
	mtx = ft_union_cmd_arg(cmd, arg);
	env_mtx = ft_env_mtx(g_data);
	pid = fork();
	if (pid == 0)
	{
		status = execve(mtx[0], mtx, env_mtx);
		exit(status);
	}
	else
		waitpid(pid, &status, 0);
	ft_free(mtx, ft_mtxrow(mtx));
	ft_free(env_mtx, ft_mtxrow(env_mtx));
	return (WEXITSTATUS(status));
}

char	**ft_union_cmd_arg(char *cmd, char **arg)
{
	char	**mtx;
	int		i;

	i = ft_mtxrow(arg) + 2;
	printf("i=%i\n", i);
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

char	*ft_path(t_general *g_data, char *cmd)
{
	char	**paths;
	t_env	*temp;
	char	*aux;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	temp = ft_env_search(g_data, "PATH");
	if (!temp)
		return (NULL);
	paths = ft_split(temp->valor, ':');
	i = -1;
	while (paths[++i])
	{
		aux = ft_strjoin(paths[i], "/");
		aux = ft_strjoin(aux, cmd);
		if (access(aux, F_OK) == 0)
			break ;
		free(aux);
	}
	free(cmd);
	return (aux);
}
