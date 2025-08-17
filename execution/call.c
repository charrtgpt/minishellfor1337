/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 06:23:54 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/03 06:23:56 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_r_type(const char *arg)
{
	if (!ft_strncmp(arg, ">>", 3))
		return (APPEND_R_IN);
	else if (!ft_strncmp(arg, ">", 2))
		return (R_OUT);
	else if (!ft_strncmp(arg, "<", 2))
		return (R_IN);
	else if (!ft_strncmp(arg, "<<", 3))
		return (HERDOC);
	return (0);
}

int	use_redirection(char **args)
{
	int	i;
	int	r_type;

	i = 0;
	while (args[i])
	{
		r_type = find_r_type(args[i]);
		if (r_type)
		{
			if (r_type == HERDOC)
			{
				if (heredoc_to_file(args[i + 1]) == -1)
					return (-1);
			}
			else if (re_direction(args[i + 1], r_type) == -1)
				return (-1);
			i += 2;
			continue ;
		}
		i++;
	}
	return (1);
}

char	**clean_arguments(char **args)
{
	int		i;
	int		j;
	char	**clean;
	int		count;

	count = 0;
	j = 0;
	i = 0;
	while (args[count])
		count++;
	clean = ft_calloc(count + 1, sizeof(char *));
	if (!clean)
		return (NULL);
	while (args[i])
	{
		if (find_r_type(args[i]) && args[i + 1])
		{
			i += 2;
			continue ;
		}
		clean[j++] = ft_strdup(args[i++]);
	}
	clean[j] = NULL;
	return (clean);
}

void	handle_exit_status(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = 128 + WTERMSIG(*status);
}
