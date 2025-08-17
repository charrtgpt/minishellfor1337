/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinss.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:05:33 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/17 21:05:36 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_b_type(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (2);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (3);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (4);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (5);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (6);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (7);
	return (0);
}

int	run_builttins(char **args, int *status, t_tofree *fr)
{
	int	type;

	type = get_b_type(args[0]);
	if (!type || !args)
		return (0);
	if (type == 1)
		*status = ft_echo(args, *status);
	else if (type == 2)
		*status = ft_cd(args, *fr->env);
	else if (type == 3)
		*status = ft_pwd();
	else if (type == 4)
		*status = ft_export(args, fr->env);
	else if (type == 5)
		*status = ft_unset(args, fr->env);
	else if (type == 6)
		*status = ft_env(fr->env);
	else if (type == 7)
		*status = ft_exit(args, *status, fr);
	else
		return (0);
	return (1);
}
