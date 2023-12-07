#include "minishell.h"

/**
 * @brief built-in cd
 * 
 * @param g_data general struct
 * @param arg route that to change
 */
void	ft_cd(t_general *g_data, char **arg)
{
	char	*dir;

	dir = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	if (!arg || !ft_strcmp(arg[0], "~"))
		ft_home(g_data);
	else if (!ft_strcmp(arg[0], "-"))
		ft_old_pwd(g_data);
	else
	{
		ft_add_mod_env(g_data, dir);
		free(dir);
		if (chdir(arg[0]) == -1)
		{
			printf("%s: Not a directory\n", arg[0]);
			return ;
		}
		dir = ft_strjoin("PWD=", getcwd(NULL, 0));
		ft_add_mod_env(g_data, dir);
	}
	free(dir);
}

/**
 * @brief Change to the route before
 * 
 * @param g_data general struct
 */
void	ft_old_pwd(t_general *g_data)
{
	char	*pwd;
	t_env	*old_pwd;
	char	*aux;

	pwd = getcwd(NULL, 0);
	old_pwd = ft_env_search(g_data, "OLDPWD");
	if (!old_pwd)
	{
		printf("cd: OLDPWD not set\n");
		return ;
	}
	chdir(old_pwd->valor);
	aux = ft_strjoin("PWD=", old_pwd->valor);
	ft_add_mod_env(g_data, ft_strjoin("OLDPWD=", pwd));
	ft_add_mod_env(g_data, aux);
	free(aux);
}

/**
 * @brief Change to root
 * 
 * @param g_data general struct
 */
void	ft_home(t_general *g_data)
{
	char	*pwd;
	t_env	*home;

	pwd = getcwd(NULL, 0);
	ft_add_mod_env(g_data, ft_strjoin("OLDPWD=", pwd));
	home = ft_env_search(g_data, "HOME");
	if (!home)
	{
		printf("cd: HOME not set\n");
		return ;
	}
	ft_add_mod_env(g_data, ft_strjoin("PWD=", home->valor));
	chdir(home->valor);
}
