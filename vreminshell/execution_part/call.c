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
	return (0);
}

int	use_redirection(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (find_r_type(args[i]))
		{
			if (re_direction(args[i + 1], find_r_type(args[i])) == -1)
				return (-1);
			i += 2;
			continue ;
		}
		i++;
	}
	return (1);
}

static char	**clean_arguments(char **args)
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

void	create_file_only(char **args, char **clean, int *status)
{
	int	i;
	int	type;
	int	sv[2];

	i = 0;
	sv[0] = dup(STDIN_FILENO);
	sv[1] = dup(STDOUT_FILENO);
	while (args[i])
	{
		type = find_r_type(args[i]);
		if (type && args[i + 1])
		{
			if (re_direction(args[i + 1], type) == -1)
			{
				dup2(sv[0], STDIN_FILENO);
				dup2(sv[1], STDOUT_FILENO);
				close(sv[0]);
				close(sv[1]);
				free_str(clean);
				*status = 1;
				return ;
			}
			i += 2;
		}
		else
			i++;
	}
	dup2(sv[0], STDIN_FILENO);
	dup2(sv[1], STDOUT_FILENO);
	close(sv[0]);
	close(sv[1]);
	*status = 0;
	free_str(clean);
}

void	execute_command_with_redirection(char **args, char **envp)
{
	t_excr	varb;

	varb.clean = clean_arguments(args);
	if (!varb.clean[0])
	{
		create_file_only(args, varb.clean, &varb.status);
		printf("\n%d\n\n", varb.status);
		return ;
	}
	free_str(varb.clean);
	varb.pid = fork();
	free_and_exitp(args, varb.pid);
	if (varb.pid == 0)
	{
		varb.clean = clean_arguments(args);
		if (use_redirection(args) == -1)
		{
			free_str(varb.clean);
			free_str(args);
			exit(1);
		}
		free_str(args);
		varb.cmd_path = get_command_path(varb.clean[0], envp, varb.clean);
		execute_command(varb.cmd_path, varb.clean, envp);
	}
	else
		handle_exit_status(varb.pid, &varb.status);
	printf("\n%d\n\n", varb.status);
}

void handle_exit_status(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
    	*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
    	*status = 128 + WTERMSIG(*status);

}

void	execute_command_with_pipe(char **args, char **envp)
{
	t_excr	varb;

	varb.clean = clean_arguments(args);
	if (!varb.clean[0])
	{
		create_file_only(args, varb.clean, &varb.status);
		exit(0);
	}
	free_str(varb.clean);
	varb.clean = clean_arguments(args);
	if (use_redirection(args) == -1)
	{
		free_str(varb.clean);
		free_str(args);
		exit(1);
	}
	free_str(args);
	varb.cmd_path = get_command_path(varb.clean[0], envp, varb.clean);
	execute_command(varb.cmd_path, varb.clean, envp);
}
