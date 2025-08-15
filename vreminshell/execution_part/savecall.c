/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <mait-ijj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:43:33 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/05/16 22:24:03 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**call_f(char *str)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	return (cmd);
}

int	check_redirection_operator(char **args, int *position)
{
	int (type), i = 0;
	type = 0;
	if (!args)
		return (-1);
	while (args[i])
	{
		if (ft_strncmp(args[i], ">", 3) == 0 || ft_strncmp(args[i], ">>", 3) == 0)
		{
			if (ft_strncmp(args[i], ">", 3) == 0)
				type = 1;
			else
				type = 2;
			if (re_direction(args[i + 1], type) < 0)
				return (-1);
			*position = i;
		}
		else if (ft_strncmp(args[i], "<", 3) == 0)
		{
			if (re_direction(args[i + 1], 3) < 0)
				return (-1);
			*position = i;
		}
		i++;
	}
	return (0);
}

int	count_elment(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**copy_from(char **arg, int position)
{
	char	**copy;

	int (i), j = 0, lent = count_elment(arg);
	i = 0;
	if (!arg)
		return (NULL);
	copy = ft_calloc(sizeof(char *), lent - 1);
	if (!copy)
		return (NULL);
	while (arg[i])
	{
		if (i == position)
			i += 2;
		if (arg[i])
		{
			copy[j++] = ft_strdup(arg[i++]);
			if (!copy)
				return (NULL);
		}
	}
	copy[j] = NULL;
	return (copy);
}

void	execute_command_with_redirection(char **args, char **envp)
{
	char	*cmd_path;
	int		position;
	char	**copy;

	position = -2;
	copy = args;
	if (check_redirection_operator(args, &position) != 0)
	return ;
	else if (position != -2)
	copy = copy_from(args, position);
	// if (ft_strncmp(args[0], ">", 3) == 0 || ft_strncmp(args[0], ">>", 3) == 0
	// || ft_strncmp(args[0], "<", 3) == 0)
	// exit(0);
	cmd_path = get_command_path(args[0], envp);
	
	execute_command(cmd_path, copy, envp);
}
