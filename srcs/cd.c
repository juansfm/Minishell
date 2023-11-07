/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:16:53 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/11/07 16:27:42 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_general *g_data, char *arg)
{
	t_env	*temp;
	char	*dir;

	temp = ft_env_search(g_data, "PWD");
	dir = ft_strjoin("OLDPWD=", temp->valor);
	printf("%s\n", dir);
	if (!ft_strcmp(arg, "-"))
		ft_old_pwd(g_data);
	else if (!ft_strcmp(arg, "~") || !ft_strcmp(arg, ""))
		ft_home(g_data);
	else
	{
		printf("%s\n", dir);
		ft_add_mod_env(g_data, dir);
		free(dir);
		printf("%s\n", arg);
		if (chdir(arg) == -1)
		{
			printf("Error en cd");
			return ;
		}
		// dir = ft_strjoin("PWD=", getcwd(dir, 4096));
		// ft_add_mod_env(g_data, dir);
		// free(dir);
		// temp = ft_env_search(g_data, "PWD");
		// printf("%s\n", temp->valor);
	}
}

void	ft_old_pwd(t_general *g_data)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*aux;

	pwd = ft_env_search(g_data, "PWD");
	old_pwd = ft_env_search(g_data, "OLDPWD");
	aux = ft_strjoin("PWD=", old_pwd->valor);
	ft_add_mod_env(g_data, ft_strjoin("OLDPWD=", pwd->valor));
	ft_add_mod_env(g_data, aux);
	chdir(pwd->valor);
	free(aux);
}

void	ft_home(t_general *g_data)
{
	t_env	*pwd;
	t_env	*home;

	pwd = ft_env_search(g_data, "PWD");
	ft_add_mod_env(g_data, ft_strjoin("OLDPWD=", pwd->valor));
	home = ft_env_search(g_data, "HOME");
	ft_add_mod_env(g_data, ft_strjoin("PWD=", home->valor));
	chdir(pwd->valor);
}
