/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 21:55:42 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/02 21:55:50 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_fd(int fd, char *f_name)
{
	if (fd < 0)
	{
		write(2, "minishell: ", 11);
		perror(f_name);
		return (-1);
	}
	return (0);
}

int	use_dup(int type, int fd)
{
	if (type == 3)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("minishell: redirection error");
			return (-1);
		}
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: redirection error");
			return (-1);
		}
	}
	return (0);
}

int	re_direction(char *f_name, int type)
{
	int	fd;

	if (type == 1)
		fd = open(f_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == 2)
		fd = open(f_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (type == 3)
		fd = open(f_name, O_RDONLY);
	else
		return (0);
	if (check_fd(fd, f_name) == -1)
		return (-1);
	if (use_dup(type, fd) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (1);
}
