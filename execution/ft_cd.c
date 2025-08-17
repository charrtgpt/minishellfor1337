/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:17:06 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/17 21:17:14 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_var(t_env *env, char *name, char *new_val)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			if (new_val != NULL)
				tmp->value = ft_strdup(new_val);
			else
				tmp->value = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}

static void	update_pwd_env(t_env *env, char *oldpwd)
{
	char	*pwd;

	if (oldpwd)
		update_env_var(env, "OLDPWD", oldpwd);
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		update_env_var(env, "PWD", pwd);
		free(pwd);
	}
}

static int	cd_change_dir(char *path)
{
	if (chdir(path) != 0)
	{
		w_e_m(path, "minishell: cd: ");
		perror(" ");
		return (1);
	}
	return (0);
}

int	ft_cd(char **args, t_env *env)
{
	char	*oldpwd;
	int		ret;

	if (!args[1])
		return (write(2, "cd: missing argument\n", 21), 1);
	if (args[2])
		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
	oldpwd = getcwd(NULL, 0);
	ret = cd_change_dir(args[1]);
	if (ret == 0)
		update_pwd_env(env, oldpwd);
	if (oldpwd)
		free(oldpwd);
	return (ret);
}
