/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agil-ord <agil-ord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:48:38 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/02/01 15:03:23 by agil-ord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief built-in cd
 * 
 * @param g_data general struct
 * @param arg route that to change
 */
int	ft_cd(t_general *g_data, char **arg)
{
	char	*dir;
	char	*aux;

	aux = getcwd(NULL, 0);
	if (aux)
		dir = ft_strjoin("OLDPWD=", aux);
	if (!arg[1] || !ft_strcmp(arg[1], "~") || !aux)
	{
		if (ft_home(g_data))
			return (1);
	}
	else if (!ft_strcmp(arg[1], "-"))
	{
		if (ft_old_pwd(g_data))
			return (1);
	}
	else
	{
		if (ft_other_cd(g_data, dir, arg))
			return (1);
	}
	free(dir);
	free(aux);
	return (0);
}

/**
 * @brief Change to the route before
 * 
 * @param g_data general struct
 */
int	ft_old_pwd(t_general *g_data)
{
	char	*pwd;
	t_env	*old_pwd;
	char	*aux;

	pwd = getcwd(NULL, 0);
	old_pwd = ft_env_search(g_data, "OLDPWD");
	if (!old_pwd)
	{
		printf("cd: OLDPWD not set\n");
		return (1);
	}
	chdir(old_pwd->value);
	aux = ft_strjoin("PWD=", old_pwd->value);
	ft_add_mod_env(g_data, ft_strjoin("OLDPWD=", pwd));
	ft_add_mod_env(g_data, aux);
	free(aux);
	return (0);
}

/**
 * @brief Change to root
 * 
 * @param g_data general struct
 */
int	ft_home(t_general *g_data)
{
	char	*pwd;
	t_env	*home;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	ft_add_mod_env(g_data, ft_strjoin("OLDPWD=", pwd));
	home = ft_env_search(g_data, "HOME");
	if (!home)
	{
		printf("cd: HOME not set\n");
		return (1);
	}
	ft_add_mod_env(g_data, ft_strjoin("PWD=", home->value));
	chdir(home->value);
	return (0);
}

int	ft_other_cd(t_general *g_data, char *dir, char **arg)
{
	ft_add_mod_env(g_data, dir);
	if (access(arg[1], F_OK) == -1)
	{
		printf("%s: No such file or directory\n", arg[1]);
		return (1);
	}
	if (access(arg[1], R_OK | W_OK) == -1)
	{
		printf("%s: Permission denied\n", arg[1]);
		return (1);
	}
	if (chdir(arg[1]) == -1)
	{
		printf("%s: Not a directory\n", arg[1]);
		return (1);
	}
	dir = ft_strjoin("PWD=", getcwd(NULL, 0));
	ft_add_mod_env(g_data, dir);
	free(dir);
	return (0);
}
