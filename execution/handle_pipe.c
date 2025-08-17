/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 20:51:53 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/17 20:51:56 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_child_args(t_child_args *args, t_pipeline *p,
				int idx, t_tofree *fr)
{
	args->cmd = p->cmds[idx];
	args->envp = p->envp;
	args->fr = fr;
	args->exit_status = p->exit_status;
}

static void	set_child_fds(t_child_args *args, int prev_fd, int pipefd[2])
{
	args->prev_fd = prev_fd;
	args->pipefd[0] = pipefd[0];
	args->pipefd[1] = pipefd[1];
}

static int	run_thepipe(t_pipeline *p, int idx, int prev_fd, t_tofree *fr)
{
	int				pipefd[2];
	pid_t			pid;
	t_child_args	args;

	if (setup_pipe(idx, p->n, pipefd) == -1)
		return (perror("minishell"), -1);
	pid = fork();
	if (pid < 0)
		return (perror("minishell"), -1);
	if (pid == 0)
	{
		init_child_args(&args, p, idx, fr);
		set_child_fds(&args, prev_fd, pipefd);
		child_execute(args);
	}
	if (prev_fd != -1)
		close(prev_fd);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	p->pids[idx] = pid;
	return (pipefd[0]);
}

static int	run_pipes(t_pipeline *p, t_tofree *fr)
{
	int	idx;
	int	prev_fd;

	prev_fd = -1;
	idx = 0;
	while (idx < p->n)
	{
		prev_fd = run_thepipe(p, idx, prev_fd, fr);
		idx++;
	}
	return (0);
}

void	execute_pipeline(char ***cmds, char **envp,
			t_tofree *fr, int *exit_status)
{
	t_pipeline	p;
	int			n;

	n = three_d_len(cmds);
	if (n <= 0)
		return ;
	p.n = n;
	p.cmds = cmds;
	p.envp = envp;
	p.pids = malloc(sizeof(pid_t) * n);
	if (!p.pids)
		return ;
	p.exit_status = exit_status;
	if (fr)
		fr->pids = p.pids;
	run_pipes(&p, fr);
	wait_childs(&p, n);
	free(p.pids);
}
