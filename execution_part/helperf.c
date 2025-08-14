/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <mait-ijj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:26:45 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/14 05:41:26 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path(char *cmd, char **paths)
{
	int		i;
	char	*path;
	char	*fullfrm;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i++], "/");
		if (!path)
			return (NULL);
		fullfrm = ft_strjoin(path, cmd);
		free (path);
		if (!fullfrm)
			return (NULL);
		if (access(fullfrm, F_OK) == 0)
			return (fullfrm);
		free(fullfrm);
	}
	return (ft_strdup(cmd));
}

char	*get_right_path(char *cmd, char **envp, char **args)
{
	int		i;
	char	**paths;
	char	*fullfrm;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split((envp[i] + 5), ':');
	if (!paths)
		return (NULL);
	fullfrm = check_path(cmd, paths);
	free_str(paths);
	if (!fullfrm)
	{
		free_str(args);
		perror("minishell");
		exit(2);
	}
	return (fullfrm);
}

char	*get_command_path(char *cmd, char **envp, char **args)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1)
		{
			w_e_m(cmd, "minishell: ");
			free_str(args);
			perror(" ");
			exit(127);
		}
		return (ft_strdup(cmd));
	}
	return (get_right_path(cmd, envp, args));
}

void	execute_command(char *cmd_p, char **argv, char **envp)
{
	struct stat	st;

	if (ft_strchr(cmd_p, '/') == NULL)
	{
		w_e_m(": command not found\n", cmd_p);
		free(cmd_p);
		free_str(argv);
		exit(127);
	}
	if (stat(cmd_p, &st) == 0 && S_ISDIR(st.st_mode))
	{
		w_e_m(cmd_p, "minishell: ");
		write(2, ": Is a directory\n", 17);
		free(cmd_p);
		free_str(argv);
		exit(126);
	}
	execve(cmd_p, argv, envp);
	write(2, "minishell: ", 11);
	perror(cmd_p);
	free(cmd_p);
	free_str(argv);
	exit(126);
}
