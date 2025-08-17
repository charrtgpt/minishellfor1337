/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 20:54:31 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/17 20:54:37 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	three_d_len(char ***arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	wait_childs(t_pipeline *p, int n)
{
	int	idx;
	int	tmp;

	idx = 0;
	while (idx < n)
	{
		handle_exit_status(p->pids[idx], &tmp);
		if (idx == n - 1 && p->exit_status)
			*(p->exit_status) = tmp;
		idx++;
	}
}

int	setup_pipe(int idx, int n, int pipefd[2])
{
	pipefd[0] = -1;
	pipefd[1] = -1;
	if (idx < n - 1)
	{
		if (pipe(pipefd) == -1)
			return (-1);
	}
	return (0);
}

void	child_execute(t_child_args args)
{
	if (args.prev_fd != -1)
	{
		dup2(args.prev_fd, STDIN_FILENO);
		close(args.prev_fd);
	}
	if (args.pipefd[1] != -1)
	{
		dup2(args.pipefd[1], STDOUT_FILENO);
		close(args.pipefd[0]);
		close(args.pipefd[1]);
	}
	execute_command_with_pipe(args.cmd, args.envp, args.fr, args.exit_status);
	exit(*(args.exit_status));
}
