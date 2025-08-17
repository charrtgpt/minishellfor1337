/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:40:46 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/17 21:40:48 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_tmp_name(void)
{
	static int	i;
	char		*name;
	char		*num;
	int			j;

	j = 2147483645;
	while (j)
	{
		num = ft_itoa(i);
		if (!num)
			return (NULL);
		name = ft_strjoin("/tmp/minishell_tmp", num);
		free(num);
		if (!name)
			return (NULL);
		if (access(name, F_OK) != 0)
			break ;
		free(name);
		i++;
		j--;
	}
	if (j == 0)
		return (NULL);
	return (name);
}

int	heredoc_to_file(char *content)
{
	char	*f_name;
	int		fd;

	f_name = create_tmp_name();
	if (!f_name)
		return (-1);
	fd = open(f_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (check_fd(fd, f_name) == -1)
		return (-1);
	write(fd, content, ft_strlen(content));
	close(fd);
	if (re_direction(f_name, 3) == -1)
	{
		free(f_name);
		return (-1);
	}
	free(f_name);
	return (1);
}
