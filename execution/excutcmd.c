/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 02:14:30 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/16 02:14:33 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_command(char **args, char **envp, t_excr varb, t_tofree *fr)
{
	varb.clean = clean_arguments(args);
	if (use_redirection(args) == -1)
	{
		free_str(varb.clean);
		child_exit(fr, varb.status, 1);
	}
	if (!envp)
		handle_env_error(varb.clean[0], varb.clean, fr);
	varb.cmd_path = get_command_path(varb.clean[0], envp, varb.clean, fr);
	if (!varb.cmd_path)
		handle_env_error(varb.clean[0], varb.clean, fr);
	execute_command(varb.cmd_path, varb.clean, envp, fr);
}

void	run_cmd_built(char **args, int *status, t_excr varb, t_tofree *fr)
{
	int	sv[2];

	varb.clean = clean_arguments(args);
	sv[0] = dup(STDIN_FILENO);
	sv[1] = dup(STDOUT_FILENO);
	if (use_redirection(args) == -1)
	{
		close(sv[0]);
		close(sv[1]);
		*status = 1;
		free_str(varb.clean);
		return ;
	}
	run_builttins(varb.clean, status, fr);
	dup2(sv[0], STDIN_FILENO);
	dup2(sv[1], STDOUT_FILENO);
	close(sv[0]);
	close(sv[1]);
	free_str(varb.clean);
}

void	execute_command_with_redirection(char **args, char **envp,
			int *status, t_tofree *fr)
{
	t_excr	varb;

	varb = (t_excr){0};
	varb.status = *status;
	varb.clean = clean_arguments(args);
	if (!varb.clean[0])
	{
		create_file_only(args, varb.clean, status);
		return ;
	}
	free_str(varb.clean);
	if (get_b_type(args[0]))
	{
		run_cmd_built(args, status, varb, fr);
		return ;
	}
	varb.pid = fork();
	free_and_exitp(args, varb.pid, status, fr);
	if (varb.pid == 0)
		run_command(args, envp, varb, fr);
	else
		handle_exit_status(varb.pid, status);
}

void	child_exit(t_tofree *fr, int status, int i)
{
	if (fr)
		cleanup(fr, i);
	exit(status);
}

void	execute_command_with_pipe(char **args, char **envp, t_tofree *fr,
			int *exit_status)
{
	t_excr	varb;

	varb = (t_excr){0};
	varb.status = *exit_status;
	varb.clean = clean_arguments(args);
	if (!varb.clean[0])
	{
		create_file_only(args, varb.clean, &varb.status);
		child_exit(fr, varb.status, 1);
	}
	free_str(varb.clean);
	if (get_b_type(args[0]))
	{
		run_cmd_built(args, exit_status, varb, fr);
		child_exit(fr, *exit_status, 1);
	}
	run_command(args, envp, varb, fr);
}
