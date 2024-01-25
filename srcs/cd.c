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

	dir = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	if (!arg[1] || !ft_strcmp(arg[1], "~"))
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
	chdir(old_pwd->valor);
	aux = ft_strjoin("PWD=", old_pwd->valor);
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
	ft_add_mod_env(g_data, ft_strjoin("OLDPWD=", pwd));
	home = ft_env_search(g_data, "HOME");
	if (!home)
	{
		printf("cd: HOME not set\n");
		return (1);
	}
	ft_add_mod_env(g_data, ft_strjoin("PWD=", home->valor));
	chdir(home->valor);
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
