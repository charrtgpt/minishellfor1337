/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:03:58 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/17 21:04:01 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>
#include <unistd.h>

static bool	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i] == 'n')
		i++;
	if (arg[i] != '\0')
		return (false);
	return (true);
}

static void	write_arg(char *arg, int status)
{
	int		i;
	char	*status_str;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] == '?')
		{
			status_str = ft_itoa(status);
			if (status_str)
			{
				write(1, status_str, ft_strlen(status_str));
				free(status_str);
			}
			i += 2;
		}
		else
			write(1, &arg[i++], 1);
	}
}

int	ft_echo(char **args, int status)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (args[i] && is_n_option(args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		write_arg(args[i], status);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}
