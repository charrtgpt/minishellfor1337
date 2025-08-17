/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 06:59:09 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/03 06:59:12 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exitp(char **args, pid_t pid, int *status, t_tofree *fr)
{
	if (pid < 0)
	{
		(void)args;
		cleanup(fr, 1);
		perror("minishell");
		*status = 1;
	}
}

char	**call_f(char *str)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	return (cmd);
}

int	if_pipe(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_strncmp(args[i], "|", 2))
			return (1);
		i++;
	}
	return (0);
}

int	count_pipe_lines(char **args)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	while (args[i])
		if (!ft_strncmp(args[i++], "|", 2))
			n++;
	return (n);
}

char	**dup_pipe_lines(char **args, int start, int end)
{
	int		len;
	char	**pipe_line;
	int		i;

	len = end - start;
	i = 0;
	pipe_line = ft_calloc(len + 1, sizeof(char *));
	if (!pipe_line)
		return (NULL);
	while (i < len)
	{
		pipe_line[i] = ft_strdup(args[start + i]);
		i++;
	}
	pipe_line[i] = NULL;
	return (pipe_line);
}
